#pragma once

#include <cassert>
#include <iostream>
#include <string>
#include <set>

#include <asio.hpp>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <sol/sol.hpp>

#include <engine/ecs/Component.hpp>
#include <engine/debug/Logger.hpp>
#include <engine/ecs/Components.hpp>
#include <engine/ecs/EntityManager.hpp>

#include "config/EcsConfig.hpp"

#include "systems/transformSystem.hpp"
#include "systems/cubeSpriteSystem.hpp"
#include "systems/movementSystem.hpp"
#include "systems/SpriteSystem.hpp"
#include "systems/SpriteAnimationSystem.hpp"
#include "systems/PlayerShootSystem.hpp"
#include "systems/CollisionSystem.hpp"
#include "systems/HealthSystem.hpp"
#include "systems/CleanEntitySystem.hpp"
#include "systems/ParallaxSystem.hpp"

#include "events/inputEvent.hpp"

#include "AssetManager.hpp"
#include "EntityTemplate.hpp"

namespace rtype
{
    enum NetworkEventType
    {
        CONNECT = 1,
        NEWPLAYER,
        MOVE,
        FIRE,
        DIE,
    };

    struct NetworkEvent
    {
        int type;
        int id;
        int data;
    };

	class Game
	{
	public:
        Game(asio::io_context& io_context);
        ~Game();

        template<typename T>
        void send(const T& event)
        {
            _socket.send_to(asio::buffer(&event, sizeof event), _endpoint);
        }

        void receive();

        void handleEvent();

        void gameLoop();

        void gameEvent();

        void gameUpdate();

        void gameUi();

        void gameDraw();

    private:
        asio::io_context &_context;
        asio::ip::udp::socket _socket;
        asio::ip::udp::endpoint _endpoint;
        asio::ip::udp::endpoint _sender_endpoint;
        NetworkEvent _event;
        bool _isPlayerConnected;
        int _playerId;

        sf::RenderWindow _window;
        sol::state _lua;
        engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> _entityManager;
        rtype::AssetManager &_assetManager;
        rtype::EntityTemplate _entityTemplate;

        std::set<int> _keysToCheck = {sf::Keyboard::Space, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down};
        std::set<int> _keysPressed;
        std::set<int> _networkKeysPressed;
        sf::Clock _dtClock;
        sf::Time _dt;
        float _fps;
        char _inputServerIp[CHAR_MAX];
        std::string _serverIp;
        bool _sentInactive;
	};
}