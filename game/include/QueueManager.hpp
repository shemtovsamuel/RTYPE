#pragma once

#include <vector>
#include <utility>

namespace rtype {
    /**
     * @brief Types possible for the packages
     */
    enum NetworkEventType {
        UNDEFINED = -1, CONNECT = 1, INPUT = 2, DIE = 3, OBJECT = 4, ENEMY_SHOOT = 5, HIVE_SHOOT = 6, ALIEN_SHOOT = 7
    };

    /**
     * @brief Type possible for the object contained in teh package
     */
    enum ObjectType {
        NONE = -1, PLAYER = 1, ENEMY_BEETLE = 2, PARRALAX_LAYER = 3, BOSS_ALIEN = 4, BOSS_HIVE = 5, HEALTH_BONUS = 6, SHOOT_BONUS = 7, ENEMY_CRAB = 8, ASTEROID = 9
    };

    /**
     * @brief Package structure
     */
    struct NetworkEvent {
        /**
         * Specifies how the package is to be treated
         */
        NetworkEventType type;
        /**
         * Specifies the ID of the entity concerned
         */
        int id;
        /**
         * Specifies if a key (of the keyboard) has been touched
         */
        int key;
        /**
         * Position of the object (if one)
         */
        std::pair<float, float> pos;
        /**
         * Type of the object concerned (if one)
         */
        ObjectType objectType;
    };

    class QueueManager {
        public:
            static QueueManager &getInstance()
            {
                static QueueManager instance;
                return instance;
            }

            void pushInQueue(NetworkEvent event)
            {
                _queue.push_back(event);
            }

            NetworkEvent popEvent()
            {
                if (_queue.empty())
                    return {UNDEFINED, -1, -1, std::make_pair(-1, -1), NONE};
                NetworkEvent event = _queue[0];
                _queue.erase(_queue.begin());
                return event;
            }

            bool isEmpty()
            {
                return _queue.empty();
            }

        private:
            QueueManager() = default;
            QueueManager(const QueueManager &) = delete;
            QueueManager &operator=(const QueueManager &) = delete;

            std::vector<rtype::NetworkEvent> _queue;
    };
}