#include "Npc.h"


Npc::Npc(){
	oCNpc = new OCNpc();
	npcBaseAddress = oCNpc->getAddress2();
}

Npc::Npc(uintptr_t npcAddress/*, bool toPointer*/){

	/*if(toPointer)*/{
		oCNpc = new OCNpc(*(void**)npcAddress);
		this->npcBaseAddress = oCNpc->getAddress2();
	}
	/*oCNpc = new OCNpc(*(void**)npcAddress);

	std::cout << "Addr of player: " << npcAddress<< std::endl;*/
}

template <typename T>
T *Npc::getPointer(uintptr_t offset)
{
	if (npcBaseAddress == 0)
		return NULL; // Keine gültige Basisadresse

	return reinterpret_cast<T *>(npcBaseAddress + offset);
}

bool Npc::isPlayerLoaded()
{
	if (npcBaseAddress == 0)
		return false;
	return true;
}

std::string Npc::getCoordinates()
{
	if (!isPlayerLoaded())
		return "NULL";

	float *x = getPointer<float>(OFFSET_PosX);
	float *y = getPointer<float>(OFFSET_PosY);
	float *z = getPointer<float>(OFFSET_PosZ);

	return "X: " + std::to_string(*x) + " Y: " + std::to_string(*y) + " Z: " + std::to_string(*z);
}

void Npc::setPlayerPosition(float x, float y, float z)
{
	setX(x);
	setY(y);
	setZ(z);
}

void Npc::tpToOldCamp()
{
	// this->setPlayerPosition(-8334.085f, 11636.9f, -1185.910f);
}

void Npc::superJump()
{
	//*pos.z += 50;
}

void Npc::healPlayerBy(int HP)
{
	//*PlayerCurrentHealth += HP;
}

int Npc::getCurrentLevel()
{
	if (!isPlayerLoaded())
		return 0;
	return *getPointer<int>(OFFSET_Level);
}

int Npc::getExperienceNextLevel()
{
	if (!isPlayerLoaded())
		return 0;

	return *getPointer<int>(OFFSET_ExperienceNextLevel);
}

int Npc::getCurrentExperience()
{
	if (!isPlayerLoaded())
		return 0;

	return *getPointer<int>(OFFSET_CurrentExperience);
}

int Npc::getMaxHealth()
{
	if (!isPlayerLoaded())
		return 0;

	return *getPointer<int>(OFFSET_MaxHealth);
}

void Npc::setMaxHealth(int maxHealth)
{
	if (!isPlayerLoaded())
		return;

	int *tempMaxHealth =getPointer<int>(OFFSET_MaxHealth);
	*tempMaxHealth = maxHealth;
}

int Npc::getCurrentHealth()
{
	if (!isPlayerLoaded())
		return 0;

	return *getPointer<int>(OFFSET_CurrentHealth);
}

void Npc::setCurrentHealth(int currentHealth)
{
	if (!isPlayerLoaded())
		return;

	int *tempCurrentHealth =getPointer<int>(OFFSET_CurrentHealth);
	*tempCurrentHealth = currentHealth;
}

int Npc::getMaxMana()
{
	if (!isPlayerLoaded())
		return 0;

	return *getPointer<int>(OFFSET_MaxMana);
}

int Npc::getCurrentMana()
{
	if (!isPlayerLoaded())
		return 0;

	return *getPointer<int>(OFFSET_CurrentMana);
}

int Npc::getStrength()
{
	if (!isPlayerLoaded())
		return 0;

	return *getPointer<int>(OFFSET_Strength);
}

int Npc::getExpertise()
{
	if (!isPlayerLoaded())
		return 0;

	return *getPointer<int>(OFFSET_Expertise);
}

float Npc::getX()
{
	if (!isPlayerLoaded())
		return 0;

	return *getPointer<float>(OFFSET_PosX);
}

void Npc::setX(float posX)
{
	if (!isPlayerLoaded())
		return;

	float *tempPosX =getPointer<float>(OFFSET_PosX);
	*tempPosX = posX;
}

float Npc::getY()
{
	if (!isPlayerLoaded())
		return 0;

	return *getPointer<float>(OFFSET_PosY);
}

void Npc::setY(float posY)
{
	if (!isPlayerLoaded())
		return;

	float *tempPosY =getPointer<float>(OFFSET_PosY);
	*tempPosY = posY;
}

float Npc::getZ()
{
	if (!isPlayerLoaded())
		return 0;

	return *getPointer<float>(OFFSET_PosZ);
}

void Npc::setZ(float posZ)
{
	if (!isPlayerLoaded())
		return;
	float *tempPosZ =getPointer<float>(OFFSET_PosZ);
	*tempPosZ = posZ;
}