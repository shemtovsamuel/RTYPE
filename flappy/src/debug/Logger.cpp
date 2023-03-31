#include <imgui.h>
#include <imgui-SFML.h>
#include <algorithm>

#include "debug/Logger.hpp"

void rtype::debug::Logger::DrawLogWindow() {
    if (logs.size() >= 500) {
        logs.clear();
    }

    ImGui::Begin("Logs");
    if (ImGui::Button("Clear")) logs.clear();
    ImGui::BeginChild("ScrollingRegion", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
    for (auto it = logs.rbegin(); it != logs.rend(); ++it) {
        ImGui::Text("%s", (*it).c_str());
    }
    ImGui::EndChild();
    ImGui::SetScrollY(0.0f);
    ImGui::End();
}