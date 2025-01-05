#pragma once

#include <windows.h>

#include <iostream>

#include "../Models/Addresses.h"
#include "../Models/Player.h"
#include "../Models/GlobalFunctions.h"

#include "../Models/ImGuiData.h"

#include "../Wrapper/ZCVob.h"
#include "../Wrapper/ZCOLOR.h"
#include "../Wrapper/ZCView.h"
#include "../Wrapper/zSTRING.h"
#include "../Wrapper/ZVec3.h"
#include "../Wrapper/OCSpawnManager.h"


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
