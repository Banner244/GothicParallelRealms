#pragma once

#include <iostream>

#include "ZVec3.h"
#include "zSTRING.h"
#include "zMAT4.h"
#include "oCObjectFactory.h"
#include "oCItem.h"
#include "oCMsgWeapon.h"

class oCItem;
/**
 * @brief Base memory address for the main player's NPC instance.
 *
 * This address points to the main player character in memory.
 */
constexpr uintptr_t ADDR_PLAYERBASE = 0x8DBBB0;

/** 
 * @class OCNpc
 * @brief Wrapper Class of OCNpc in the game.
 *
 * This class provides various methods to manipulate an NPC, including position control,
 * health management, movement, and interactions with the game world.
 */
class OCNpc
{
private:
public:
    /**
     * @struct Offset
     * @brief Contains memory offsets for various NPC attributes.
     *
     * These offsets are used to access NPC properties such as health, mana, position,
     * and experience directly in memory.
     */
    class Offset
    {
    public:
        // float
        static constexpr uintptr_t POS_X = 0x48; 
        // float
        static constexpr uintptr_t POS_Z = 0x58; 
        // float
        static constexpr uintptr_t POS_Y = 0x68;

        // int
        static constexpr uintptr_t CURRENT_HEALTH = 0x184; 
        // int
        static constexpr uintptr_t MAX_HEALTH = 0x188;

        // int
        static constexpr uintptr_t MAX_MANA = 0x190;     
        // int
        static constexpr uintptr_t CURRENT_MANA = 0x18C; 

        // int
        static constexpr uintptr_t STRENGTH = 0x194;  
        // int
        static constexpr uintptr_t DEXTERITY = 0x198; 

        // int
        static constexpr uintptr_t LEVEL = 0x1EC; 
        // int                
        static constexpr uintptr_t EXPERIENCE_NEXT_LEVEL = 0x31C; 
        // int
        static constexpr uintptr_t CURRENT_EXPERIENCE = 0x320;    
    };
    
    /**
     * @brief Creates a new NPC instance.
     * @return Pointer to the newly created NPC.
     */
    static OCNpc *CreateNewNpc();
    /**
     * @brief Creates an NPC instance from an existing memory address.
     * @param address Pointer to an existing NPC structure in memory.
     * @return Pointer to the NPC instance.
     */
    static OCNpc *CreateFromPointer(void *address);

    /**
     * @brief Reads a variable from the NPC memory using an offset.
     * @tparam T Type of the variable to be read.
     * @param offset Memory offset of the variable.
     * @return Reference to the requested variable.
     */
    template <typename T>
    T &callVariable(uintptr_t offset)
    {
        return *reinterpret_cast<T *>(reinterpret_cast<uintptr_t>(this) + offset);
    }

    void setVisualWithString(const char *visual);

    void setAdditionalVisuals(const char *textureBody, int param2, int param3, const char *textureHead, int param5, int param6, int param7);

    void setVobName(const char *vobName);

    void setByScriptInstance(const char *name, int param2);

    void enable(ZVec3 *pos);

    void enableWithdCoords(float x, float z, float y);

    void setPosition(const ZVec3 *position);

    // Beispielmethode, um den NPC zu manipulieren
    void getPositionWorld(ZVec3 *position);

    void beginMovement();

    zMAT4 *getTrafoModelNodeToWorld(zMAT4 *matrix, int param2);

    void setTrafo(zMAT4 *matrix);

    void setVobInMovement(int param);
    void move(float x, float z, float y);

    void *getModel();

    void *getHomeWorld();

    float getDistanceToVob(void *vob);
    void insertInVobList(void *vob);

    zSTRING *getSectorNameVobIsIn();

    void addVobToWorld_CorrectParentDependencies();

    oCItem * getEquippedArmor();
    oCItem * getEquippedMeleeWeapon();
    oCItem * getEquippedRangedWeapon();

    void equipArmor(oCItem * armor);
    void equipItem(oCItem * item);
    void equipWeapon(oCItem * weapon); 
    void equipFarWeapon(oCItem * weapon); 
    void equip(oCItem * item);
    void equipBestWeapon(int param1);

    void unequipItem(oCItem * item);

    oCItem * putInInv(oCItem * item);

    int EV_DrawWeapon1(oCMsgWeapon * msgWeapon);

    oCItem * getWeapon();

    int useItem(oCItem * item);

    void setTalentValue(int talentIndex, int value);
    //zSTRING *getName2();

    /*int applyOverlay(char * animName);

    void setBodyState(int param1);

    void initHumanAI();

    void setSleepingMode(int param1);
    void setSleeping(int param1);

    void addRefVobSubtree(void * zCTree);

    void setStaticVob(int param);

    void setVobPresentName(char * name);

    zSTRING * getVobPresentName();

    */
};
