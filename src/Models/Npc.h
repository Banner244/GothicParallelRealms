#pragma once

#include <iostream>
#include <string>

#include "Addresses.h"

#include "../Wrapper/OCNpc.h"

class Npc
{
	private:
		template<typename T>
		T* getPointer(uintptr_t offset);

		bool isPlayerLoaded();
		uintptr_t npcBaseAddress;

	public:
		Npc();
		Npc(uintptr_t npcAddress);

		OCNpc *oCNpc;

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
};