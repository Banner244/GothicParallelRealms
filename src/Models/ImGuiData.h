#pragma once

class ImGuiData {

    private:
        bool guiVisible = true;
    public:
        ImGuiData();

        void toggleGuiVisibility();
        bool isGuiVisible();

};

