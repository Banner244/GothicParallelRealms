#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>

#include "MinHook.h"

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#include "Logic/GameThreadWorker.h"
#include "Models/ImGuiData.h"
#include "Logic/ImGuiManager.h"
#include "Logic/sMain.h"
#include "Network/DataChangeNotifier.h"

// Globals
HINSTANCE dll_handle;

typedef long(__stdcall *present)(IDXGISwapChain *, UINT, UINT);
present p_present;
present p_present_target;
bool get_present_pointer()
{
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = GetForegroundWindow();
	sd.SampleDesc.Count = 1;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	IDXGISwapChain *swap_chain;
	ID3D11Device *device;

	const D3D_FEATURE_LEVEL feature_levels[] = {
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_0,
	};
	if (D3D11CreateDeviceAndSwapChain(
			NULL,
			D3D_DRIVER_TYPE_HARDWARE,
			NULL,
			0,
			feature_levels,
			2,
			D3D11_SDK_VERSION,
			&sd,
			&swap_chain,
			&device,
			nullptr,
			nullptr) == S_OK)
	{
		void **p_vtable = *reinterpret_cast<void ***>(swap_chain);
		swap_chain->Release();
		device->Release();
		// context->Release();
		p_present_target = (present)p_vtable[8];
		return true;
	}
	return false;
}

WNDPROC oWndProc;
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

ImGuiData imGuiData;
ImGuiManager *guiManager;
sMain *mainLoop = new sMain();
GameThreadWorker *gameThreadWorker = new GameThreadWorker();

bool visibleGui = true;

bool init = false;
HWND window = NULL;
ID3D11Device *p_device = NULL;
ID3D11DeviceContext *p_context = NULL;
ID3D11RenderTargetView *mainRenderTargetView = NULL;
HRESULT __stdcall detour_present(IDXGISwapChain *p_swap_chain, UINT sync_interval, UINT flags)
{
	if (!init)
	{
		if (SUCCEEDED(p_swap_chain->GetDevice(__uuidof(ID3D11Device), (void **)&p_device)))
		{
			p_device->GetImmediateContext(&p_context);
			DXGI_SWAP_CHAIN_DESC sd;
			p_swap_chain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D *pBackBuffer;
			p_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID *)&pBackBuffer);
			p_device->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);

			// init gui
			guiManager = new ImGuiManager(p_device, p_context, window);
			std::cout << "Starting GUI: SUCCESS" << std::endl;

			init = true;
		}
		else
			return p_present(p_swap_chain, sync_interval, flags);
	}

	// Handling Tasks from Server 
	gameThreadWorker->processMessages();
	
	// Handling Game things, like Rendering of NPCs
	gameThreadWorker->checkGameState();

	guiManager->startOfMainLoop();
	guiManager->showContent(imGuiData);
	guiManager->endOfMainLoop();

	p_context->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return p_present(p_swap_chain, sync_interval, flags);
}

DWORD __stdcall EjectThread(LPVOID lpParameter)
{
	Sleep(100);
	FreeLibraryAndExitThread(dll_handle, 0);
	Sleep(100);
	return 0;
}

void SetupConsole()
{
	AllocConsole();
	// Standardausgabe (std::cout) mit der Konsole verbinden
	FILE *stream;
	freopen_s(&stream, "CONOUT$", "w", stdout);

	// Standardfehlerausgabe (std::cerr) mit der Konsole verbinden
	freopen_s(&stream, "CONOUT$", "w", stderr);

	// Standardeingabe (std::cin) mit der Konsole verbinden
	freopen_s(&stream, "CONIN$", "r", stdin);
}

//"main" loop
DWORD WINAPI MainThread()
{
	SetupConsole();

	std::cout << "Starting MAIN...\n"
			  << std::endl;

	if (!get_present_pointer())
		return 1;

	MH_STATUS status = MH_Initialize();
	if (status != MH_OK)
		return 1;

	if (MH_CreateHook(reinterpret_cast<void **>(p_present_target), &detour_present, reinterpret_cast<void **>(&p_present)) != MH_OK)
		return 1;
	std::cout << "MH_CreateHook: SUCCESS" << std::endl;

	if (MH_EnableHook(p_present_target) != MH_OK)
		return 1;
	std::cout << "MH_EnableHook: SUCCESS" << std::endl;

	// WAITING ... 
	Sleep(200);
	// ################## START ############################
	std::cout << "Press RControl to connect...\n";
	while (!GetAsyncKeyState(VK_RCONTROL) & 1)
	{
		Sleep(100);
	}

	boost::asio::io_context io_context;
	// create Client
	Client client(io_context, "127.0.0.1", "12345", gameThreadWorker);
	// mainloop for receiving messages
	std::thread io_thread([&io_context]()
						  { io_context.run(); });

	
	DataChangeNotifier notifier(&client);
	while (!GetAsyncKeyState(VK_END) & 1)
	{
		/*if (GetAsyncKeyState(VK_DOWN) < 0)*/{
			notifier.sendChanges();
		}
		//notifier.sendChanges();

		// give imGui the players Information
		//imGuiData.clients = *gameThreadManager->clients;
		Sleep(80);
	}
	io_thread.join();

	// ################## END ############################

	// Cleanup
	if (MH_DisableHook(MH_ALL_HOOKS) != MH_OK)
	{
		return 1;
	}
	if (MH_Uninitialize() != MH_OK)
	{
		return 1;
	}

	guiManager->shutDown();

	if (mainRenderTargetView)
	{
		mainRenderTargetView->Release();
		mainRenderTargetView = NULL;
	}
	if (p_context)
	{
		p_context->Release();
		p_context = NULL;
	}
	if (p_device)
	{
		p_device->Release();
		p_device = NULL;
	}
	SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)(oWndProc));

	FreeConsole();
	CreateThread(0, 0, EjectThread, 0, 0, 0);

	return 0;
}

BOOL __stdcall DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		dll_handle = hModule;
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MainThread, NULL, 0, NULL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
	}

	return TRUE;
}