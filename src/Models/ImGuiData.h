#pragma once

#include <iostream>
#include <vector>

#include "NpcInformation.h"

class ImGuiData {

    private:
        bool guiVisible = true;

    public:
        ImGuiData();

        void toggleGuiVisibility();
        bool isGuiVisible();

        std::vector<NpcInformation*> npcs;

};

