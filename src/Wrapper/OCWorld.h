#pragma once

#include "OCGame.h"

class OCWorld {

    public:
        static void insertInLists(void * vob);
        static void vobAddedToWorld(void * vob);
        static void addVob(void * vob);
        static void removeVob(void * vob);
        static void * getOCWorldAddress();

};