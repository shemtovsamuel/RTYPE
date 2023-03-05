#include <iostream>
#include <asio.hpp>
#include <unordered_map>
#include <vector>

enum NetworkEventType {
    CONNECT = 1,
    NEWPLAYER,
    MOVE,
    FIRE,
    DIE,
};

struct NetworkEvent {
    int type;
    int id;
    int data;
};

int main() {
    asio::io_context ioc;
    asio::ip::udp::socket socket(ioc);
    socket.open(asio::ip::udp::v4());
    socket.bind(asio::ip::udp::endpoint(asio::ip::udp::v4(), 2001));

    std::unordered_map<int, asio::ip::udp::endpoint> players;

    int next_id = 0;

    std::cout << "Server started" << std::endl;

    while (true) {
        asio::ip::udp::endpoint sender_endpoint;
        NetworkEvent event;
        size_t len = socket.receive_from(asio::buffer(&event, sizeof event), sender_endpoint);
        if (len != sizeof(NetworkEvent)) {
            std::cerr << "Received data size does not match the size of Event structure." << std::endl;
            continue;
        }

        switch (event.type) {
        case CONNECT: {
            // Assign a new ID to the player
            int newPlayerId = next_id++;
            event.id = newPlayerId;
            players[event.id] = sender_endpoint;

            // Send the ID back to the player
            socket.send_to(asio::buffer(&event, sizeof event), sender_endpoint);

            std::cout << "New player" << std::endl;

            // Broadcast the event to all other players
            event.type = NEWPLAYER;
            for (const auto& [id, endpoint] : players) {
                if (id == event.id) continue;
                event.id = id;
                socket.send_to(asio::buffer(&event, sizeof event), sender_endpoint);
                event.id = newPlayerId;
            }
            for (const auto& [id, endpoint] : players) {
                if (id == event.id) continue;
                socket.send_to(asio::buffer(&event, sizeof event), endpoint);
            }


            break;
        }

        case MOVE: {
            // Update the player's position
            players[event.id] = sender_endpoint;

            // Broadcast the event to all other players
            for (const auto& [id, endpoint] : players) {
                if (id == event.id) continue;
                socket.send_to(asio::buffer(&event, sizeof event), endpoint);
            }
            break;
        }
        }
    }

    return 0;
}
