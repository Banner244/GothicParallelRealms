#pragma once
#include <cstdint>


constexpr uintptr_t ADDR_PLAYERBASE = 0x8DBBB0;

constexpr uintptr_t OFFSET_Level = 0x1EC;
constexpr uintptr_t OFFSET_ExperienceNextLevel = 0x31C;
constexpr uintptr_t OFFSET_CurrentExperience = 0x320;

constexpr uintptr_t OFFSET_MaxHealth = 0x188;
constexpr uintptr_t OFFSET_CurrentHealth = 0x184;

constexpr uintptr_t OFFSET_MaxMana = 0x190;
constexpr uintptr_t OFFSET_CurrentMana = 0x18C;

constexpr uintptr_t OFFSET_Strength = 0x194;
constexpr uintptr_t OFFSET_Expertise = 0x198;

constexpr uintptr_t OFFSET_PosX = 0x48;
constexpr uintptr_t OFFSET_PosY = 0x68;
constexpr uintptr_t OFFSET_PosZ = 0x58;


// Base Addresses
/*#define ADDR_PLAYERBASE 0x8DBBB0

//Player Offset
#define OFFSET_Level 0x1EC
#define OFFSET_CurrentExperience 0x31C
#define OFFSET_ExperienceNextLevel 0x320

#define OFFSET_MaxHealth 0x188
#define OFFSET_CurrentHealth 0x184

#define OFFSET_MaxMana 0x190  
#define OFFSET_CurrentMana 0x18C

#define OFFSET_Strength 0x194
#define OFFSET_Expertise 0x198

#define OFFSET_PosX 0x48
#define OFFSET_PosY 0x68
#define OFFSET_PosZ 0x58*/
