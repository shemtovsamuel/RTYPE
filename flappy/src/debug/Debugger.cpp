#include <vector>
#include <cstring>

#include <imgui.h>
#include <imgui-SFML.h>

#include <engine/ecs/Components.hpp>

#include "debug/Debugger.hpp"
#include "Game.hpp"
#include "config/EcsConfig.hpp"
#include "Components.hpp"

bool rtype::debug::Debugger::getShowHitbox() const
{
    return _showHitbox;
}

bool rtype::debug::Debugger::hasComponents(rtype::Game &game, int id)
{
    if (game.getEntityManager().hasComponent<engine::ecs::components::Transform>(id))
        return true;
    else if (game.getEntityManager().hasComponent<engine::ecs::components::Velocity>(id))
        return true;
    else if (game.getEntityManager().hasComponent<rtype::ecs::components::Sprite>(id))
        return true;
    else if (game.getEntityManager().hasComponent<rtype::ecs::components::SpriteAnimation>(id))
        return true;
    else if (game.getEntityManager().hasComponent<engine::ecs::components::Hitbox>(id))
        return true;
    else if (game.getEntityManager().hasComponent<rtype::ecs::components::MoveComponent>(id))
        return true;
    else if (game.getEntityManager().hasComponent<rtype::ecs::components::PlayerShoot>(id))
        return true;
    else if (game.getEntityManager().hasComponent<rtype::ecs::components::Health>(id))
        return true;
    else if (game.getEntityManager().hasComponent<rtype::ecs::components::State>(id))
        return true;
    else if (game.getEntityManager().hasComponent<rtype::ecs::components::Parallax>(id))
        return true;
    else if (game.getEntityManager().hasComponent<rtype::ecs::components::DebugTag>(id))
        return true;

    return false;
}

void rtype::debug::Debugger::calculateNumberOfActiveEntities(rtype::Game &game)
{
    _numberOfActiveEntities = 0;
    for (int i = 0; i < rtype::config::EntitiesCount; ++i)
    {
        if (this->hasComponents(game, i) == false)
        {
            continue;
        }
        ++_numberOfActiveEntities;
    }
}

void rtype::debug::Debugger::update(rtype::Game &game)
{
    calculateNumberOfActiveEntities(game);
}

void rtype::debug::Debugger::draw(rtype::Game &game)
{
    ImGui::Begin("Debug");

    ImGui::Text("%s", std::string("Fps : ").append(std::to_string(game.getFps())).c_str());

    ImGui::Separator();

    ImGui::Text("Active entities : %d/%d", _numberOfActiveEntities, rtype::config::EntitiesCount);

    ImGui::Checkbox("Show entity window", &_showEntityWindow);

    ImGui::Checkbox("Show hitbox", &_showHitbox);

    ImGui::End();

    if (_showEntityWindow)
    {
        drawEntityWindow(game);
    }
}

void rtype::debug::Debugger::drawEntityWindow(rtype::Game &game)
{
    ImGui::Begin("Entity");

    ImGui::Columns(3);

    ImGui::BeginChild("Column 1", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
    _numberOfActiveEntities = 0;
    for (int i = 0; i < rtype::config::EntitiesCount; ++i)
    {
        if (this->hasComponents(game, i) == false)
        {
            continue;
        }
        ++_numberOfActiveEntities;

        std::string name = std::to_string(i);
        if (game.getEntityManager().hasComponent<rtype::ecs::components::DebugTag>(i))
        {
            name = name + " : " + game.getEntityManager().getComponent<rtype::ecs::components::DebugTag>(i).tag;
        }

        if (ImGui::Selectable(name.c_str(), _selectedEntity == i))
        {
            _selectedEntity = i;
        }
    }
    ImGui::EndChild();

    ImGui::NextColumn();

    ImGui::BeginChild("Column 2", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
    if (_selectedEntity != -1)
    {
        if (game.getEntityManager().hasComponent<engine::ecs::components::Transform>(_selectedEntity))
        {
            if (ImGui::Selectable("Transform", _selectedComponent == (int)engine::ecs::components::ComponentType::Transform))
            {
                _selectedComponent = (int)engine::ecs::components::ComponentType::Transform;
            }
        }
        if (game.getEntityManager().hasComponent<engine::ecs::components::Velocity>(_selectedEntity))
        {
            if (ImGui::Selectable("Velocity", _selectedComponent == (int)engine::ecs::components::ComponentType::Velocity))
            {
                _selectedComponent = (int)engine::ecs::components::ComponentType::Velocity;
            }
        }
        if (game.getEntityManager().hasComponent<rtype::ecs::components::Sprite>(_selectedEntity))
        {
            if (ImGui::Selectable("Sprite", _selectedComponent == (int)rtype::ecs::components::ComponentType::Sprite))
            {
                _selectedComponent = (int)rtype::ecs::components::ComponentType::Sprite;
            }
        }
        if (game.getEntityManager().hasComponent<rtype::ecs::components::SpriteAnimation>(_selectedEntity))
        {
            if (ImGui::Selectable("SpriteAnimation", _selectedComponent == (int)rtype::ecs::components::ComponentType::SpriteAnimation))
            {
                _selectedComponent = (int)rtype::ecs::components::ComponentType::SpriteAnimation;
            }
        }
        if (game.getEntityManager().hasComponent<engine::ecs::components::Hitbox>(_selectedEntity))
        {
            if (ImGui::Selectable("Hitbox", _selectedComponent == (int)engine::ecs::components::ComponentType::Hitbox))
            {
                _selectedComponent = (int)engine::ecs::components::ComponentType::Hitbox;
            }
        }
        if (game.getEntityManager().hasComponent<rtype::ecs::components::MoveComponent>(_selectedEntity))
        {
            if (ImGui::Selectable("MoveComponent", _selectedComponent == (int)rtype::ecs::components::ComponentType::MoveComponent))
            {
                _selectedComponent = (int)rtype::ecs::components::ComponentType::MoveComponent;
            }
        }
        if (game.getEntityManager().hasComponent<rtype::ecs::components::PlayerShoot>(_selectedEntity))
        {
            if (ImGui::Selectable("PlayerShoot", _selectedComponent == (int)rtype::ecs::components::ComponentType::PlayerShoot))
            {
                _selectedComponent = (int)rtype::ecs::components::ComponentType::PlayerShoot;
            }
        }

        if (game.getEntityManager().hasComponent<rtype::ecs::components::Health>(_selectedEntity))
        {
            if (ImGui::Selectable("Health", _selectedComponent == (int)rtype::ecs::components::ComponentType::Health))
            {
                _selectedComponent = (int)rtype::ecs::components::ComponentType::Health;
            }
        }
        if (game.getEntityManager().hasComponent<rtype::ecs::components::State>(_selectedEntity))
        {
            if (ImGui::Selectable("State", _selectedComponent == (int)rtype::ecs::components::ComponentType::State))
            {
                _selectedComponent = (int)rtype::ecs::components::ComponentType::State;
            }
        }
        if (game.getEntityManager().hasComponent<rtype::ecs::components::Parallax>(_selectedEntity))
        {
            if (ImGui::Selectable("Parallax", _selectedComponent == (int)rtype::ecs::components::ComponentType::Parallax))
            {
                _selectedComponent = (int)rtype::ecs::components::ComponentType::Parallax;
            }
        }
        if (game.getEntityManager().hasComponent<rtype::ecs::components::DebugTag>(_selectedEntity))
        {
            if (ImGui::Selectable("Debug tag", _selectedComponent == (int)rtype::ecs::components::ComponentType::DebugTag))
            {
                _selectedComponent = (int)rtype::ecs::components::ComponentType::DebugTag;
            }
        }
    }
    ImGui::EndChild();

    ImGui::NextColumn();

    ImGui::BeginChild("Column 3", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
    if (_selectedComponent != -1)
    {
        if (_selectedComponent == (int)engine::ecs::components::ComponentType::Transform)
        {
            auto &component = game.getEntityManager().getComponent<engine::ecs::components::Transform>(_selectedEntity);

            ImGui::InputFloat("X", &component.x);
            ImGui::InputFloat("Y", &component.y);
        }
        if (_selectedComponent == (int)engine::ecs::components::ComponentType::Velocity)
        {
            auto &component = game.getEntityManager().getComponent<engine::ecs::components::Velocity>(_selectedEntity);

            ImGui::SliderFloat("X", &component.x, -1000.0f, 1000.0f);
            ImGui::SliderFloat("Y", &component.y, -1000.0f, 1000.0f);
        }
        if (_selectedComponent == (int)rtype::ecs::components::ComponentType::Sprite)
        {
            auto &component = game.getEntityManager().getComponent<rtype::ecs::components::Sprite>(_selectedEntity);

            ImGui::InputInt("Layer", &component.layer);
        }
        if (_selectedComponent == (int)rtype::ecs::components::ComponentType::SpriteAnimation)
        {
            auto &component = game.getEntityManager().getComponent<rtype::ecs::components::SpriteAnimation>(_selectedEntity);

            ImGui::InputInt("Current frame", &component.currentFrame);
            ImGui::InputFloat("Time per frame", &component.timePerFrame);
            ImGui::InputFloat("Accumulated time", &component.accumulatedTime);
        }
        if (_selectedComponent == (int)engine::ecs::components::ComponentType::Hitbox)
        {
            auto &component = game.getEntityManager().getComponent<engine::ecs::components::Hitbox>(_selectedEntity);

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
        if (_selectedComponent == (int)rtype::ecs::components::ComponentType::Health)
        {
            auto &component = game.getEntityManager().getComponent<rtype::ecs::components::Health>(_selectedEntity);

            ImGui::InputInt("Hp", &component.hp);

            char bufferTag[256];
            memset(bufferTag, 0, sizeof(bufferTag));
            strcpy(bufferTag, component.tag.c_str());
            ImGui::InputText("Tag", bufferTag, sizeof(bufferTag));
            component.tag = bufferTag;
        }
        if (_selectedComponent == (int)rtype::ecs::components::ComponentType::DebugTag)
        {
            auto &component = game.getEntityManager().getComponent<rtype::ecs::components::DebugTag>(_selectedEntity);

            char bufferTag[256];
            memset(bufferTag, 0, sizeof(bufferTag));
            strcpy(bufferTag, component.tag.c_str());
            ImGui::InputText("Tag", bufferTag, sizeof(bufferTag));
            component.tag = bufferTag;
        }
    }
    ImGui::EndChild();

    ImGui::End();
}