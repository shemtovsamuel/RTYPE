#include <asio/ip/udp.hpp>
#include <asio/io_service.hpp>
#include <iostream>
#include "ClientGame.hpp"

#pragma once

namespace client {
    /**
     * @brief Return the package contained in a buffer (doesn't handle error)
     * @param buffer Buffer containing the package
     * @return Event (NetworkEvent) contained in the buffer
     */
    rtype::NetworkEvent getPackage(std::array<char, 1024> &buffer);

    /**
     * @brief Instance of the client containing a game
     */
    class clientInstance {
        public:
            /**
             * Create a window which is waiting for the user to enter the server ip adress
             */
            clientInstance();

            /**
             * @brief Handle the life cycle of the client
             */
            void lifeCycle();

        private:
            /**
             * @brief Send a package via a socket
             * @param event Package to send
             * @param target Target to send to
             */
            void send(rtype::NetworkEvent event, const asio::ip::udp::endpoint &target);

            /**
             * @brief Start listening for package to come
             */
            void listen();

            /**
             * @brief Handle what to do with each package
             * @param package Package to handle
             * @param gameConcerned Specifies if the package concern the game and the network or juste the network
             */
            void handlePackage(rtype::NetworkEvent package, bool gameConcerned);

            /**
             * @bried Handle package that are about a connection
             * @param package Package to handle
             */
            void connect(rtype::NetworkEvent &package);

            /**
             * @brief Send the package filled by the game itself
             */
            void clearGameQueue();

            rtype::NetworkEvent _event;
            asio::io_context _context;
            asio::ip::udp::socket _socket;
            rtype::ClientGame _game;
            asio::ip::udp::endpoint _endpoint;
            asio::ip::udp::endpoint _sender;
    };
}