#include <engine/ecs/Components.hpp>

#include "ScoreManager.hpp"
#include "Components.hpp"

rtype::ScoreManager::ScoreManager(engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &entityManager) :
    _entityManager(entityManager), _score(0)
{
}

void rtype::ScoreManager::displayScore(sf::RenderWindow& window)
{
    sf::Font font;

    if (!font.loadFromFile("./assets/fonts/DePixelBreit.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }
    sf::Text scoreText;

    scoreText.setFont(font);
    scoreText.setString("Score: " + std::to_string(_score));
    scoreText.setCharacterSize(28);
    scoreText.setPosition(15, 15);
    scoreText.setFillColor(sf::Color::White);
    window.draw(scoreText);
}

int rtype::ScoreManager::getScore() const
{
    return _score;
}

void rtype::ScoreManager::updateScore(int score)
{
    _score += score;
}