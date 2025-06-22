#pragma once

#include <iostream>

#include "basic_string.h"
#include "oCObjectFactory.h"

class oCItem {

    public:
        static oCItem * CreateoCItem(int itemId = -1); 

        void initByScript(int id, int ka);
        int setByScriptInstance(const char * name);
        void setName(std::string name);
        std::string getName();

        zSTRING * getInstanceName();
        
        void setFlag(int flag);

    private:


};