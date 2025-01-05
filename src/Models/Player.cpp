#include "Player.h"

Player::Player() {

}

uintptr_t Player::playerBase(){
	return *reinterpret_cast<uintptr_t *>(ADDR_PLAYERBASE);
}

template <typename T>
T *Player::getPointer(uintptr_t offset)
{
	if (playerBase() == 0)
		return NULL; // Keine gültige Basisadresse

	return reinterpret_cast<T *>(playerBase() + offset);
}

bool Player::isPlayerLoaded()
{
	if (playerBase() == 0)
		return false;
	return true;
}

std::string Player::getCoordinates()
{
	if (!isPlayerLoaded())
		return "NULL";

	float *x = getPointer<float>(OFFSET_PosX);
	float *y = getPointer<float>(OFFSET_PosY);
	float *z = getPointer<float>(OFFSET_PosZ);

	return "X: " + std::to_string(*x) + " Y: " + std::to_string(*y) + " Z: " + std::to_string(*z);
}

void Player::setPlayerPosition(float x, float y, float z)
{
	setX(x);
	setY(y);
	setZ(z);
	/**pos.x = x;
	*pos.y = y;
	*pos.z = z;*/

}

void Player::tpToOldCamp()
{
	// this->setPlayerPosition(-8334.085f, 11636.9f, -1185.910f);
}

void Player::superJump()
{
	//*pos.z += 50;
}

void Player::healPlayerBy(int HP)
{
	//*PlayerCurrentHealth += HP;
}

int Player::getCurrentLevel()
{
	if (!isPlayerLoaded())
		return 0;
	return *getPointer<int>(OFFSET_Level);
}

int Player::getExperienceNextLevel()
{
	if (!isPlayerLoaded())
		return 0;

	return *getPointer<int>(OFFSET_ExperienceNextLevel);
}

int Player::getCurrentExperience()
{
	if (!isPlayerLoaded())
		return 0;

	return *getPointer<int>(OFFSET_CurrentExperience);
}

int Player::getMaxHealth()
{
	if (!isPlayerLoaded())
		return 0;

	return *getPointer<int>(OFFSET_MaxHealth);
}

int Player::getCurrentHealth()
{
	if (!isPlayerLoaded())
		return 0;

	return *getPointer<int>(OFFSET_CurrentHealth);
}

int Player::getMaxMana()
{
	if (!isPlayerLoaded())
		return 0;

	return *getPointer<int>(OFFSET_MaxMana);
}

int Player::getCurrentMana()
{
	if (!isPlayerLoaded())
		return 0;

	return *getPointer<int>(OFFSET_CurrentMana);
}

int Player::getStrength()
{
	if (!isPlayerLoaded())
		return 0;

	return *getPointer<int>(OFFSET_Strength);
}

int Player::getExpertise()
{
	if (!isPlayerLoaded())
		return 0;

	return *getPointer<int>(OFFSET_Expertise);
}

float Player::getX()
{
	if (!isPlayerLoaded())
		return 0;

	return *getPointer<float>(OFFSET_PosX);
}

void Player::setX(float posX)
{
	if (!isPlayerLoaded())
		return;

	float *tempPosX =getPointer<float>(OFFSET_PosX);
	*tempPosX = posX;
}

float Player::getY()
{
	if (!isPlayerLoaded())
		return 0;

	return *getPointer<float>(OFFSET_PosY);
}

void Player::setY(float posY)
{
	if (!isPlayerLoaded())
		return;

	float *tempPosY =getPointer<float>(OFFSET_PosY);
	*tempPosY = posY;
}

float Player::getZ()
{
	if (!isPlayerLoaded())
		return 0;

	return *getPointer<float>(OFFSET_PosZ);
}

void Player::setZ(float posZ)
{
	if (!isPlayerLoaded())
		return;
	float *tempPosZ =getPointer<float>(OFFSET_PosZ);
	*tempPosZ = posZ;
}