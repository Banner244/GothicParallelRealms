#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>

#include "NpcInformation.h"

class ImGuiData {

    private:
        bool guiVisible = true;

    public:
        ImGuiData();

        void toggleGuiVisibility();
        bool isGuiVisible();

        //std::vector<NpcInformation*> npcs;
        std::unordered_map<std::string, Npc*> clients;
};

