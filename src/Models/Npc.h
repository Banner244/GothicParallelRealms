#pragma once

#include <iostream>
#include <string>

#include "DataStructures.h"
#include "../Wrapper/OCNpc.h"
#include "../Wrapper/zCModel.h"
#include "../Wrapper/zMAT4.h"

class Npc
{
	private:
		bool isPlayerLoaded();

	public:
		Npc();
		Npc(uintptr_t npcAddress);

		OCNpc *oCNpc;
		
		void setName(std::string name);
		std::string getName();

		void healPlayerBy(int HP);
		void tpToOldCamp();
		void superJump();

		std::string getCoordinates();
		void setPlayerPosition(float x, float y, float z);

		int getCurrentLevel ();
		int getExperienceNextLevel ();
		int getCurrentExperience ();

		int getMaxHealth ();
		void setMaxHealth (int maxHealth);

		int getCurrentHealth ();
		void setCurrentHealth (int currentHealth);
		
		int getMaxMana ();
		int getCurrentMana ();
		int getStrength ();
		int getExpertise ();

		float getX();
		void setX(float x);

		float getY();
		void setY(float y);
		
		float getZ();
		void setZ(float z);

		void setInterpolatePosition(float x, float z, float y);

		DataStructures::LastPosition getLastPosition();
		DataStructures::LastAnimation getLastAnimation();
		DataStructures::LastRotation getLastRotation();
};