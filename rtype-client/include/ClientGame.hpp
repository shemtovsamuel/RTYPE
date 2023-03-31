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
#include <engine/ecs/Components.hpp>
#include <engine/ecs/EntityManager.hpp>

#include "debug/Logger.hpp"
#include "config/EcsConfig.hpp"

#include "graphical/GraphicalWindow.hpp"

#include "../../game/include/systems/TransformSystem.hpp"
#include "../../game/include/systems/MovementSystem.hpp"
#include "systems/SpriteSystem.hpp"
#include "systems/SpriteAnimationSystem.hpp"
#include "systems/PlayerShootSystem.hpp"
#include "../../game/include/systems/CollisionSystem.hpp"
#include "systems/HealthSystem.hpp"
#include "../../game/include/systems/CleanEntitySystem.hpp"
#include "../../game/include/systems/ParallaxSystem.hpp"
#include "../../game/include/systems/LevelSystem.hpp"
#include "systems/ScoreSystem.hpp"
#include "systems/EnemyShootSystem.hpp"
#include "systems/BossHiveShootSystem.hpp"
#include "systems/BossAlienShootSystem.hpp"
#include "systems/ParticleSystem.hpp"
#include "systems/LifeTimeSystem.hpp"

#include "events/InputEvent.hpp"

#include "AssetManager.hpp"
#include "EntityTemplate.hpp"
#include "LevelManager.hpp"
#include "ScoreManager.hpp"

#include "../../game/include/Game.hpp"

namespace rtype {
    class ClientGame : public Game {
        public:
            /**
             * @brief Construct a new ClientGame object
             *
             * @param io_context
             */
            ClientGame();

            /**
             * Destroy the game and add a dying event to the queue
             */
            ~ClientGame();

            /**
             * @brief Get the Fps of the game
             *
             * @return float
             */
            float getFps() const;

            /**
             * @brief Handle the event received from the server
             *
             */
            void handleEvent(NetworkEvent package);

            /**
             * @brief ClientGame event
             *
             */
            void gameEvent() override;

            /**
             * @brief ClientGame update
             *
             */
            void gameUpdate() override;

            /**
             * @brief ClientGame ui for the debug menu
             *
             */
            void gameUi();

            /**
             * @brief ClientGame draw
             *
             */
            void gameDraw();

            /**
             * @brief Game loop to repeat at each frame
             */
            void gameLoop() override;

            /**
             * @brief Says whether the game is over or not
             * @return The state of the game
             */
            bool isOver() override;

            /**
             * @brief Gets the IP address of the server enter at the beginning
             * @return IP address of the running server
             */
            std::string getIp();

            /**
             * @brief Gets the id of the player
             * @return An int containing the player ID
             */
            int getPlayerID();

        private:
            void handleReceivedObject(NetworkEvent package);
            void die(NetworkEvent package);
            bool _isPlayerConnected;
            int _playerId;
            rtype::graphical::GraphicalWindow _graphicalWindow;
            sol::state _lua;
            rtype::AssetManager &_assetManager;
            rtype::EntityTemplate _entityTemplate;
            rtype::ScoreManager _scoreManager;
            std::set<int> _keysToCheck = {sf::Keyboard::Space,
                    sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up,
                    sf::Keyboard::Down};
            std::set<int> _keysPressed;
            std::set<int> _networkKeysPressed;
            float _fps;
            bool _sentInactive;
            char _inputServerIp[CHAR_MAX];
            std::string _serverIp;
            const std::vector<std::string> _layersTexture;
            const std::vector<float> _layersSpeed;
    };
}