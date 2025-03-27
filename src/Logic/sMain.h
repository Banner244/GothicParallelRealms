#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <iostream>
#include <unordered_map>

#include "../Network/Client.h"

#include "../Models/Npc.h"
#include "../Models/GlobalFunctions.h"

#include "../Models/ImGuiData.h"

#include "../Wrapper/ZCVob.h"
#include "../Wrapper/ZCOLOR.h"
#include "../Wrapper/ZCView.h"
#include "../Wrapper/zSTRING.h"
#include "../Wrapper/ZVec3.h"
#include "../Wrapper/OCSpawnManager.h"
#include "../Wrapper/OCNpc.h"

class sMain
{
	private:
		//~sMain();
		void InitTrainer();

		void setPositions();
	public:
		sMain();
		void listenToKeys(ImGuiData &imGuiData);

		std::unordered_map<std::string, Npc*> *clients;
};
