#pragma once

#include <iostream>

#include <string>

#include <windows.h>

#include "../../imGui/imgui.h"
#include "../../imGui/backends/imgui_impl_win32.h"
#include "../../imGui/backends/imgui_impl_dx11.h"

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#include "../Models/Player.h"
#include "../Models/ImGuiData.h"

class ImGuiManager {
    private:
        ID3D11Device* p_device;
        ID3D11DeviceContext* p_context;

        Player *player = new Player();

        bool showGui = true;
    public:
        ImGuiManager(ID3D11Device* p_device, ID3D11DeviceContext* p_context, HWND &window);
        
        void startOfMainLoop();

        void showContent(ImGuiData imGuiData);

        void endOfMainLoop();

        void shutDown();
};