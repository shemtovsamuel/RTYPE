#include "clientInstance.hpp"
#include "../../game/include/QueueManager.hpp"

rtype::NetworkEvent client::getPackage(std::array<char, 1024> &buffer)
{
    rtype::NetworkEvent tmp{};
    std::memcpy(&tmp, &buffer, sizeof(tmp));
    return tmp;
}

client::clientInstance::clientInstance() : _event(), _context(), _socket{_context}, _game(rtype::ClientGame())
{
}

void client::clientInstance::send(rtype::NetworkEvent event, const asio::ip::udp::endpoint &target)
{
    _socket.async_send_to(asio::buffer(&event, sizeof event), target,
            [this](const asio::system_error &error, size_t bytes_transferred) {
                if (error.code().operator bool()) {
                    std::cerr << "Send failed: " << error.what() << std::endl;
                    return;
                }
            });
}

void client::clientInstance::listen()
{
    _socket.async_receive_from(asio::buffer(&_event, sizeof _event), _sender,
            [this](const asio::system_error &error, size_t bytes_transferred) {
                if (error.code().operator bool()) {
                    std::cerr << "Receive failed: " << error.what()
                              << std::endl;
                    return;
                }
                handlePackage(_event, true);
                listen();
            });
}

void client::clientInstance::connect(rtype::NetworkEvent &package)
{
    try {
        _endpoint = asio::ip::udp::endpoint(
                asio::ip::address::from_string(_game.getIp()), 2001);
    } catch (std::system_error &err) {
        std::cerr << "Couldn't create endpoint at " << _game.getIp() << ": " << err.what() << std::endl;
        return;
    }
    if (!_socket.is_open()) {
        _socket.open(asio::ip::udp::v4());
    }
    _context.restart();
    listen();
}

void client::clientInstance::handlePackage(rtype::NetworkEvent package, bool gameConcerned)
{
    switch (package.type) {
        case rtype::UNDEFINED:
            break;
        case rtype::CONNECT:
            if (gameConcerned) {
                _game.handleEvent(package);
            }
            connect(package);
            break;
        case rtype::INPUT:
            if (gameConcerned)
                _game.handleEvent(package);
            break;
        case rtype::OBJECT:
            if (gameConcerned)
                _game.handleEvent(package);
            break;
        case rtype::DIE:
            if (gameConcerned)
                _game.handleEvent(package);
            break;
    }
}

void client::clientInstance::lifeCycle()
{
    while (!_game.isOver()) {
        _context.poll();
        _game.gameLoop();
        clearGameQueue();
    }
    rtype::NetworkEvent event = {rtype::DIE, _game.getPlayerID(), -1, std::make_pair(-1, -1), rtype::NONE};
    send(event, _endpoint);
}

void client::clientInstance::clearGameQueue()
{
    auto &queueManager = rtype::QueueManager::getInstance();
    rtype::NetworkEvent package = {};
    while (!queueManager.isEmpty()) {
        package = queueManager.popEvent();
        handlePackage(package, false);
        send(package, _endpoint);
    }
}
