#pragma once

#include <iostream>
#include <string>

#include "Addresses.h"

class Player
{
	private:
		uintptr_t playerBase();

		template<typename T>
		T* getPointer(uintptr_t offset);

		bool isPlayerLoaded();

	public:
		Player();
		void healPlayerBy(int HP);
		void tpToOldCamp();
		void superJump();

		std::string getCoordinates();
		void setPlayerPosition(float x, float y, float z);

		int getCurrentLevel ();
		int getExperienceNextLevel ();
		int getCurrentExperience ();
		int getMaxHealth ();
		int getCurrentHealth ();
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
};

/*constexpr uintptr_t ADDR_PLAYERBASE = 0x8DBBB0; // Dummy-Wert, ersetze mit deinem Wert

constexpr uintptr_t OFFSET_Level = 0x1EC;
constexpr uintptr_t OFFSET_ExperienceNextLevel = 0x31C;
constexpr uintptr_t OFFSET_CurrentExperience = 0x320;

constexpr uintptr_t OFFSET_MaxHealth = 0x188;
constexpr uintptr_t OFFSET_CurrentHealth = 0x184;

constexpr uintptr_t OFFSET_MaxMana = 0x190;
constexpr uintptr_t OFFSET_CurrentMana = 0x18C;

constexpr uintptr_t OFFSET_Strength = 0x194;
constexpr uintptr_t OFFSET_Expertise = 0x198;*/