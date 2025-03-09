#pragma once

#include "OCGame.h"

class OCWorld {

    public:
        static int ShouldAddThisVobToBsp(void * vob);
        static void EnableVob(void * vob1, void * vob2);
        static void InsertInLists(void * vob);
        static void VobAddedToWorld(void * vob);
        static void AddVob(void * vob);
        static void RemoveVob(void * vob);
        static void * GetOCWorldAddress();

};