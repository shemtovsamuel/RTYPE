#include "serverInstance.hpp"
#include "../game/include/QueueManager.hpp"

rtype::NetworkEvent server::getPackage(std::array<char, 1024> &buffer)
{
    rtype::NetworkEvent tmp{};
    std::memcpy(&tmp, &buffer, sizeof(tmp));
    return tmp;
}

server::serverInstance::serverInstance() : _nextPlayerId(0), _refreshTimer(
        std::chrono::steady_clock::now()), _buffer({}), _service(), _resolver(
        _service), _socket{_service}, _game(
        rtype::ServerGame())
{
    srand(time(0));
    asio::ip::udp::resolver::query query(asio::ip::udp::v4(), "google.com", "");
    _endpoint = *(_resolver.resolve(query));
    _socket.connect(_endpoint);
    _addr = _socket.local_endpoint().address();
    std::cout << "My IP according to google is: " << _addr.to_string()
              << std::endl;
    _socket.close();
    asio::error_code err;
    _socket.open(asio::ip::udp::v4());
    _socket.bind(asio::ip::udp::endpoint(_addr, 2001), err);
    listen();
}

void server::serverInstance::runFor(std::size_t microsecond)
{
    _service.run_for(std::chrono::duration<int, std::micro>(microsecond));
}

void server::serverInstance::send(rtype::NetworkEvent event, const asio::ip::udp::endpoint &target)
{
    _socket.async_send_to(asio::buffer(&event, sizeof event), target,
            [this, target, event](const asio::system_error &error, size_t bytes_transferred) {
                if (error.code().operator bool()) {
                    std::cerr << "Send failed: " << error.what() << std::endl;
                    return;
                }
            });
}

void server::serverInstance::listen()
{
    _socket.async_receive_from(asio::buffer(_buffer), _sender,
            [this](const asio::system_error &error, size_t bytes_transferred) {
                if (error.code().operator bool()) {
                    std::cerr << "Receive failed: " << error.what()
                              << std::endl;
                    return;
                }
                handlePackage(server::getPackage(_buffer));
                listen();
            });
}

void server::serverInstance::connect(rtype::NetworkEvent &package)
{
    int newPlayerId = _nextPlayerId++;
    package.id = newPlayerId;
    package.objectType = rtype::PLAYER;
    package.pos = std::make_pair(100.f, rand() % 900);
    _players[package.id] = _sender;
    _playersTimer[package.id] = std::chrono::steady_clock::now();

    send(package, _sender);

    _game.handleEvent(package);
    sendGameObjects();
}

void server::serverInstance::move(rtype::NetworkEvent package)
{
    _game.handleEvent(package);
    _players[package.id] = _sender;
    _playersTimer[package.id] = std::chrono::steady_clock::now();

    for (const auto &[id, endpoint]: _players) {
        if (id == package.id || !endpoint.address().is_v4())
            continue;
        send(package, endpoint);
    }
}

void server::serverInstance::handlePackage(rtype::NetworkEvent package)
{
    switch (package.type) {
        case rtype::UNDEFINED:
            break;
        case rtype::CONNECT:
            connect(package);
            break;
        case rtype::INPUT:
            move(package);
            break;
        case rtype::DIE:
            die(package.id);
            break;
    }
}

void server::serverInstance::lifeCycle()
{
    while (!_game.isOver()) {
        _game.gameLoop();
        clearGameQueue();
        checkClientPresence();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now() - _refreshTimer).count() >
                2500) {
            sendGameObjects();
            _refreshTimer = std::chrono::steady_clock::now();
        }
        runFor(10);
    }
}

void server::serverInstance::sendGameObjects()
{
    auto &entityManager = _game.getEntityManager();
    sendAll((rtype::NetworkEvent({rtype::UNDEFINED, -1, -1, std::make_pair(-1, -1), rtype::NONE})));
    for (int i = 0; i < rtype::config::EntitiesCount; i++) {
        if (entityManager.hasComponent<engine::ecs::components::Transform>(i)) {
            auto transform = entityManager.getComponent<engine::ecs::components::Transform>(
                    i);
            rtype::NetworkEvent package = {rtype::OBJECT, -1, -1,
                    std::make_pair(transform.x, transform.y), rtype::NONE};
            if (entityManager.hasComponent<rtype::ecs::components::ParralaxId>(
                    i)) {
                package.id = entityManager.getComponent<rtype::ecs::components::ParralaxId>(
                        i).id;
                package.objectType = rtype::PARRALAX_LAYER;
            } else if (entityManager.hasComponent<rtype::ecs::components::PlayerId>(
                    i)) {
                package.id = entityManager.getComponent<rtype::ecs::components::PlayerId>(
                        i).id;
                package.objectType = rtype::PLAYER;
            } else if (entityManager.hasComponent<rtype::ecs::components::EnemyCrabId>(
                    i)) {
                package.id = entityManager.getComponent<rtype::ecs::components::EnemyCrabId>(
                        i).id;
                package.objectType = rtype::ENEMY_CRAB;
            } else if (entityManager.hasComponent<rtype::ecs::components::EnemyBeetleId>(
                    i)) {
                package.id = entityManager.getComponent<rtype::ecs::components::EnemyBeetleId>(
                        i).id;
                package.objectType = rtype::ENEMY_BEETLE;
            } else if (entityManager.hasComponent<rtype::ecs::components::EnnemiId>(
                    i)) {
                if (entityManager.hasComponent<rtype::ecs::components::BossAlien>(
                        i)) {
                    package.id = entityManager.getComponent<rtype::ecs::components::EnnemiId>(
                            i).id;
                    package.objectType = rtype::BOSS_ALIEN;
                } else if (entityManager.hasComponent<rtype::ecs::components::BossHive>(
                        i)) {
                    package.id = entityManager.getComponent<rtype::ecs::components::EnnemiId>(
                            i).id;
                    package.objectType = rtype::BOSS_HIVE;
                }
            } else if (entityManager.hasComponent<rtype::ecs::components::HealthBonusId>(
                    i)) {
                package.id = entityManager.getComponent<rtype::ecs::components::HealthBonusId>(
                        i).id;
                package.objectType = rtype::HEALTH_BONUS;
            } else if (entityManager.hasComponent<rtype::ecs::components::ShootBonusId>(
                    i)) {
                package.id = entityManager.getComponent<rtype::ecs::components::ShootBonusId>(
                        i).id;
                package.objectType = rtype::SHOOT_BONUS;
            } else {
                continue;
            }
            sendAll(package);
        }
    }
}

void server::serverInstance::sendAll(rtype::NetworkEvent event)
{
    for (auto &player: _players) {
        send(event, player.second);
    }
}

void server::serverInstance::checkClientPresence()
{
    auto timeNow = std::chrono::steady_clock::now();

    for (auto player: _playersTimer) {
        if (std::chrono::duration_cast<std::chrono::milliseconds>(
                timeNow - player.second).count() > 60000) {
            die(player.first);
            return;
        }
    }
}

void server::serverInstance::die(int id)
{
    rtype::NetworkEvent package = {rtype::DIE, id, -1, std::make_pair(0, 0),
            rtype::NONE};
    _game.handleEvent(package);
    sendAll(package);
    if (_players.find(id) != _players.end()) {
        _players.erase(id);
        _playersTimer.erase(id);
    }
}

void server::serverInstance::clearGameQueue()
{
    auto &queueManager = rtype::QueueManager::getInstance();

    while (!queueManager.isEmpty()) {
        sendAll(queueManager.popEvent());
    }
}
