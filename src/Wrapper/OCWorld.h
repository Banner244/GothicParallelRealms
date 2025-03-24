#pragma once

#include "OCGame.h"
#include "OCNpc.h"

class OCWorld {

    public:
        /* ############ Custom Calls ############ */
        static void InserIntoGlobalVobTree(void * vob);

        /* ############ END Custom Calls ############ */

        


        static void PrintStatus();

        static void PrintGlobalVobTree(void * zCTree, int param2);

        static void * GetOwnerSession(); // Strange, this works...

        static unsigned long GetVobHashIndex(void * vob);
        static void InsertVobHashTable(void * vob);
        static int ShouldAddThisVobToBsp(void * vob);
        static void EnableVob(void * vob1, void * vob2);
        static void InsertInLists(void * vob);
        static void VobAddedToWorld(void * vob);
        static void * AddVob(void * vob);
        static void RemoveVob(void * vob);
        
        static void * GetOCWorldAddress();
        static void * GetOCWorldGlobalVobTree();

};