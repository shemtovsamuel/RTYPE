#include <vector>
#include <cstring>

#include <imgui.h>
#include <imgui-SFML.h>

#include <engine/ecs/Components.hpp>

#include "debug/Debugger.hpp"
#include "GameState.hpp"
#include "GameConfig.hpp"
#include "Components.hpp"

factorio::debug::Debugger::Debugger(factorio::GameState &gameState) : _gameState(gameState)
{
}

factorio::debug::Debugger::~Debugger()
{
}

bool factorio::debug::Debugger::getShowHitbox() const
{
    return _showHitbox;
}

bool factorio::debug::Debugger::hasComponents(int id)
{
    if (_gameState.getEntityManager().hasComponent<engine::ecs::components::Transform>(id))
        return true;
    else if (_gameState.getEntityManager().hasComponent<engine::ecs::components::Velocity>(id))
        return true;
    else if (_gameState.getEntityManager().hasComponent<factorio::ecs::components::Sprite>(id))
        return true;
    else if (_gameState.getEntityManager().hasComponent<factorio::ecs::components::SpriteAnimation>(id))
        return true;
    else if (_gameState.getEntityManager().hasComponent<engine::ecs::components::Hitbox>(id))
        return true;

    return false;
}

void factorio::debug::Debugger::calculateNumberOfActiveEntities()
{
    _numberOfActiveEntities = 0;
    for (int i = 0; i < factorio::config::EntitiesCount; ++i) {
        if (this->hasComponents(i) == false) {
            continue;
        }
        ++_numberOfActiveEntities;
    }
}

void factorio::debug::Debugger::update()
{
    calculateNumberOfActiveEntities();
}

void factorio::debug::Debugger::draw()
{
	ImGui::Begin("Debug");

	ImGui::Text("%s", std::string("Fps : ").append(std::to_string(_gameState.getGameLoop().getFps())).c_str());

    ImGui::Separator();

    ImGui::Text("Active entities : %d/%d", _numberOfActiveEntities, factorio::config::EntitiesCount);

    ImGui::Checkbox("Show entity window", &_showEntityWindow);

    ImGui::Checkbox("Show hitbox", &_showHitbox);

    ImGui::Checkbox("Show map window", &_showMapWindow);

	ImGui::End();

    if (_showEntityWindow) {
        drawEntityWindow();
    }

    if (_showMapWindow) {
        drawMapWindow();
    }
}

void factorio::debug::Debugger::drawEntityWindow()
{
    ImGui::Begin("Entity");

    ImGui::Columns(3);

    ImGui::BeginChild("Column 1", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
    _numberOfActiveEntities = 0;
    for (int i = 0; i < factorio::config::EntitiesCount; ++i) {
        if (this->hasComponents(i) == false) {
            continue;
        }
        ++_numberOfActiveEntities;

        std::string name = std::to_string(i);

        if (ImGui::Selectable(name.c_str(), _selectedEntity == i))
        {
            _selectedEntity = i;
        }
    }
    ImGui::EndChild();

    ImGui::NextColumn();

    ImGui::BeginChild("Column 2", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
    if (_selectedEntity != -1) {
        if (_gameState.getEntityManager().hasComponent<engine::ecs::components::Transform>(_selectedEntity)) {
            if (ImGui::Selectable("Transform", _selectedComponent == (int)engine::ecs::components::ComponentType::Transform))
            {
                _selectedComponent = (int)engine::ecs::components::ComponentType::Transform;
            }
        }
        if (_gameState.getEntityManager().hasComponent<engine::ecs::components::Velocity>(_selectedEntity)) {
            if (ImGui::Selectable("Velocity", _selectedComponent == (int)engine::ecs::components::ComponentType::Velocity))
            {
                _selectedComponent = (int)engine::ecs::components::ComponentType::Velocity;
            }
        }
        if (_gameState.getEntityManager().hasComponent<factorio::ecs::components::Sprite>(_selectedEntity)) {
            if (ImGui::Selectable("Sprite", _selectedComponent == (int)factorio::ecs::components::ComponentType::Sprite))
            {
                _selectedComponent = (int)factorio::ecs::components::ComponentType::Sprite;
            }
        }
        if (_gameState.getEntityManager().hasComponent<factorio::ecs::components::SpriteAnimation>(_selectedEntity)) {
            if (ImGui::Selectable("SpriteAnimation", _selectedComponent == (int)factorio::ecs::components::ComponentType::SpriteAnimation))
            {
                _selectedComponent = (int)factorio::ecs::components::ComponentType::SpriteAnimation;
            }
        }
        if (_gameState.getEntityManager().hasComponent<engine::ecs::components::Hitbox>(_selectedEntity)) {
            if (ImGui::Selectable("Hitbox", _selectedComponent == (int)engine::ecs::components::ComponentType::Hitbox))
            {
                _selectedComponent = (int)engine::ecs::components::ComponentType::Hitbox;
            }
        }
    }
    ImGui::EndChild();

    ImGui::NextColumn();

    ImGui::BeginChild("Column 3", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
    if (_selectedComponent != -1) {
        if (_selectedComponent == (int)engine::ecs::components::ComponentType::Transform) {
            auto& component = _gameState.getEntityManager().getComponent<engine::ecs::components::Transform>(_selectedEntity);

            ImGui::InputFloat("X", &component.x);
            ImGui::InputFloat("Y", &component.y);
        }
        if (_selectedComponent == (int)engine::ecs::components::ComponentType::Velocity) {
            auto& component = _gameState.getEntityManager().getComponent<engine::ecs::components::Velocity>(_selectedEntity);

            ImGui::SliderFloat("X", &component.x, -1000.0f, 1000.0f);
            ImGui::SliderFloat("Y", &component.y, -1000.0f, 1000.0f);
        }
        if (_selectedComponent == (int)factorio::ecs::components::ComponentType::Sprite) {
            auto& component = _gameState.getEntityManager().getComponent<factorio::ecs::components::Sprite>(_selectedEntity);

            ImGui::InputInt("Layer", &component.layer);
        }
        if (_selectedComponent == (int)factorio::ecs::components::ComponentType::SpriteAnimation) {
            auto& component = _gameState.getEntityManager().getComponent<factorio::ecs::components::SpriteAnimation>(_selectedEntity);

            ImGui::InputInt("Current frame", &component.currentFrame);
            ImGui::InputFloat("Time per frame", &component.timePerFrame);
            ImGui::InputFloat("Accumulated time", &component.accumulatedTime);
        }
        if (_selectedComponent == (int)engine::ecs::components::ComponentType::Hitbox) {
            auto& component = _gameState.getEntityManager().getComponent<engine::ecs::components::Hitbox>(_selectedEntity);

            ImGui::InputFloat("Width", &component.width);
            ImGui::InputFloat("Height", &component.height);
            ImGui::Checkbox("Collided", &component.collided);
            ImGui::Checkbox("Is trigger", &component.isTrigger);

            char bufferTag[256];
            memset(bufferTag, 0, sizeof(bufferTag));
            strcpy(bufferTag, component.tag.c_str());
            ImGui::InputText("Tag", bufferTag, sizeof(bufferTag));
            component.tag = bufferTag;

            char bufferTriggerTags[256];
            memset(bufferTriggerTags, 0, sizeof(bufferTriggerTags));
            strcpy(bufferTriggerTags, component.triggerTags.c_str());
            ImGui::InputText("Trigger tags", bufferTriggerTags, sizeof(bufferTriggerTags));
            component.triggerTags = bufferTriggerTags;
        }
    }
    ImGui::EndChild();

    ImGui::End();
}

void factorio::debug::Debugger::drawMapWindow()
{
    ImGui::Begin("Map");

    auto& mapGenerator = _gameState.getGameRenderer().getMapGenerator();

    ImGui::InputInt("Width", &mapGenerator.width);
    ImGui::InputInt("Height", &mapGenerator.height);
    ImGui::InputInt("Octabes", &mapGenerator.octaves);
    ImGui::InputFloat("Lacunarity", &mapGenerator.lacunarity);
    ImGui::InputFloat("Amplitude", &mapGenerator.amplitude);
    ImGui::InputFloat("Bias", &mapGenerator.bias);

    if (ImGui::Button("Generate")) {
        mapGenerator.world = mapGenerator.generateMap();
    }

	ImGui::End();
}