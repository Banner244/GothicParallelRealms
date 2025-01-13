#pragma once

#include <windows.h>

#include <iostream>

#include "../Models/Addresses.h"
#include "../Models/Player.h"
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
	
		Player *player;

	public:
		sMain();

		void listenToKeys(ImGuiData &imGuiData);
};
