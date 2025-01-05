#include "ImGuiData.h"

ImGuiData::ImGuiData() {


}

void ImGuiData::toggleGuiVisibility() {
    this->guiVisible = !this->guiVisible;
}

bool ImGuiData::isGuiVisible() {
    return this->guiVisible;
}

