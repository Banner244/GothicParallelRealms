#include "Npc.h"


Npc::Npc(){
	oCNpc = OCNpc::CreateNewNpc();//new OCNpc();
	//npcBaseAddress = oCNpc->getAddress2();
}

Npc::Npc(uintptr_t npcAddress/*, bool toPointer*/){
	/*if(toPointer)*/{
		oCNpc = OCNpc::CreateFromPointer(*(void**)npcAddress); //new OCNpc(*(void**)npcAddress);
		//this->npcBaseAddress = oCNpc->getAddress2();
	}
	/*oCNpc = new OCNpc(*(void**)npcAddress);

	std::cout << "Addr of player: " << npcAddress<< std::endl;*/
}

bool Npc::isPlayerLoaded()
{
	if (oCNpc == nullptr)
		return false;
	return true;
}

std::string Npc::getCoordinates()
{
	if (!isPlayerLoaded())
		return "NULL";

	float x = oCNpc->callVariable<float>(OCNpc::Offset::POS_X);
	float z = oCNpc->callVariable<float>(OCNpc::Offset::POS_Z);
	float y = oCNpc->callVariable<float>(OCNpc::Offset::POS_Y);

	return "X: " + std::to_string(x) + " Z: " + std::to_string(z) + " Y: " + std::to_string(y);
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

	return oCNpc->callVariable<int>(OCNpc::Offset::LEVEL);
}

int Npc::getExperienceNextLevel()
{
	if (!isPlayerLoaded())
		return 0;

	return oCNpc->callVariable<int>(OCNpc::Offset::EXPERIENCE_NEXT_LEVEL);
}

int Npc::getCurrentExperience()
{
	if (!isPlayerLoaded())
		return 0;

	return oCNpc->callVariable<int>(OCNpc::Offset::CURRENT_EXPERIENCE);
}

int Npc::getMaxHealth()
{
	if (!isPlayerLoaded())
		return 0;

	return oCNpc->callVariable<int>(OCNpc::Offset::MAX_HEALTH);
}

void Npc::setMaxHealth(int maxHealth)
{
	if (!isPlayerLoaded())
		return;

	oCNpc->callVariable<int>(OCNpc::Offset::MAX_HEALTH) = maxHealth;
}

int Npc::getCurrentHealth()
{
	if (!isPlayerLoaded())
		return 0;
	return oCNpc->callVariable<int>(OCNpc::Offset::CURRENT_HEALTH);
}

void Npc::setCurrentHealth(int currentHealth)
{
	if (!isPlayerLoaded())
		return;

	oCNpc->callVariable<int>(OCNpc::Offset::CURRENT_HEALTH) = currentHealth;
}

int Npc::getMaxMana()
{
	if (!isPlayerLoaded())
		return 0;

	return oCNpc->callVariable<int>(OCNpc::Offset::MAX_MANA);
}

int Npc::getCurrentMana()
{
	if (!isPlayerLoaded())
		return 0;

	return oCNpc->callVariable<int>(OCNpc::Offset::CURRENT_MANA);
}

int Npc::getStrength()
{
	if (!isPlayerLoaded())
		return 0;

	return oCNpc->callVariable<int>(OCNpc::Offset::STRENGTH);
}

int Npc::getExpertise()
{
	if (!isPlayerLoaded())
		return 0;

	return oCNpc->callVariable<int>(OCNpc::Offset::EXPERTISE);
}

float Npc::getX()
{
	if (!isPlayerLoaded())
		return 0;

	return oCNpc->callVariable<float>(OCNpc::Offset::POS_X);
}

void Npc::setX(float posX)
{
	if (!isPlayerLoaded())
		return;

	oCNpc->callVariable<float>(OCNpc::Offset::POS_X) = posX;
}

float Npc::getY()
{
	if (!isPlayerLoaded())
		return 0;

	return oCNpc->callVariable<float>(OCNpc::Offset::POS_Y);
}

void Npc::setY(float posY)
{
	if (!isPlayerLoaded())
		return;

	oCNpc->callVariable<float>(OCNpc::Offset::POS_Y) = posY;
}

float Npc::getZ()
{
	if (!isPlayerLoaded())
		return 0;

	return oCNpc->callVariable<float>(OCNpc::Offset::POS_Z);
}

void Npc::setZ(float posZ)
{
	if (!isPlayerLoaded())
		return;

	oCNpc->callVariable<float>(OCNpc::Offset::POS_Z) = posZ;
}

void Npc::setInterpolatePosition(float x, float z, float y){
	ZVec3 currentPos;
	ZVec3 targetPos;
	float factor = 0.5;

	targetPos.initialize(x, z, y);
	oCNpc->getPositionWorld(&currentPos);

	ZVec3 newPos = currentPos + (targetPos - currentPos) * factor;

	setX(newPos.getPosX());
	setZ(newPos.getPosZ());
	setY(newPos.getPosY());
}

DataStructures::LastPosition Npc::getLastPosition() {
	DataStructures::LastPosition retLastPos;
	retLastPos.x = getX();
	retLastPos.z = getZ();
	retLastPos.y = getY();

	DataStructures::LastRotation lastRot = getLastRotation();
	retLastPos.yaw = lastRot.yaw;
	retLastPos.pitch = lastRot.pitch;
	retLastPos.roll = lastRot.roll;
	return retLastPos;
}

DataStructures::LastAnimation Npc::getLastAnimation() {
	DataStructures::LastAnimation retLastAnim;
	zCModel *npcModel = new zCModel(oCNpc->getModel());

	int animCount = *reinterpret_cast<int *>(reinterpret_cast<uintptr_t>(npcModel->getAddress()) + 0x34);
	retLastAnim.animationCount = animCount;
	
	for(int i = 0; i < animCount; i++) {
		uintptr_t addr = reinterpret_cast<uintptr_t>(npcModel->getAddress())+ 0x38 + (i * 4) ;
		void * pp = reinterpret_cast<void*> (addr);

		uintptr_t addr2 = *reinterpret_cast<uintptr_t*>(pp);
		void * pp2 = reinterpret_cast<void*> (addr2);

		uintptr_t addr3 = *reinterpret_cast<uintptr_t*>(pp2);
		addr3 += 0x4c;
		int * pp3 = reinterpret_cast<int*> (addr3);
		retLastAnim.animationIds.push_back(*pp3);
	}

	return retLastAnim;
}

DataStructures::LastRotation Npc::getLastRotation(){
	DataStructures::LastRotation retLastRot;

	zMAT4 matrix;
	oCNpc->getTrafoModelNodeToWorld(&matrix, 0);
	
	// get Rotation
    retLastRot.yaw = atan2(matrix[0][2], matrix[0][0]);
    retLastRot.pitch = asin(-matrix[0][1]);
    retLastRot.roll = atan2(matrix[1][2], matrix[2][2]);

	return retLastRot;
}