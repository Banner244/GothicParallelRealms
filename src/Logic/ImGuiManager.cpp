#include "ImGuiManager.h"

ImGuiManager::ImGuiManager(ID3D11Device *p_device, ID3D11DeviceContext *p_context, HWND &window)
{
    this->p_device = p_device;
    this->p_context = p_context;

    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    // io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
    // io.MouseDrawCursor = true;
    // ShowCursor(true); // win32

    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(p_device, p_context);
}

void ImGuiManager::showContent(ImGuiData imGuiData)
{
    if (!imGuiData.isGuiVisible())
        return;

    ImGui::Begin("Stats", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    // Füge Text zum Fenster hinzu
    std::string coords = "Coords.:" + player->getCoordinates();

    std::string level = "Level:" + std::to_string(player->getCurrentLevel());
    ImGui::Text(coords.c_str());
    ImGui::Text(level.c_str());

    ImGui::Text("\nPlayers");
    if (!imGuiData.clients.empty())
    {
        auto it = imGuiData.clients.begin();
        if (it != imGuiData.clients.end())
        {
            std::string valueKey = it->first;
            Npc *valueNpc = it->second; // Zeiger auf den Wert

            std::string posX = std::to_string(valueNpc->getX());
            std::string posZ = std::to_string(valueNpc->getZ());
            std::string posY = std::to_string(valueNpc->getY());

            ImGui::Text(valueKey.c_str());
            ImGui::Text(("\t" + posX).c_str());
            ImGui::Text(("\t" + posZ).c_str());
            ImGui::Text(("\t" + posY).c_str());
        }
    }
    else
    {
        ImGui::Text("No other Players...");
    }
    ImGui::End();
}

void ImGuiManager::startOfMainLoop()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();

    ImGui::NewFrame();
}

void ImGuiManager::endOfMainLoop()
{
    ImGui::EndFrame();
    ImGui::Render();
}

void ImGuiManager::shutDown()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}