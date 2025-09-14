#pragma once

#include "OCNpc.h"

class OCNpc;
class oCItem;

class oCObjectFactory {

    public:
        static OCNpc * CreateNpc();

        /// @brief Creates an Item depending on the Id
        /// @param scriptId if you just want an Item instance use -1 else use itemId    
        /// @return new Item Instance
        static oCItem * CreateItem(int scriptId);
    private:
        static void * getOCObjectFactoryAddress();
        //void *pThis = *(void **)0x82c114;
};