#pragma once

#include <iostream>
#include <string> 

#include "basic_string.h"

class zSTRING {
private:
    void* vftable;
    basic_string basicStr;

    static void Assign(zSTRING* str, char* text);
public:
    static zSTRING* CreateNewzSTRING(char* str);
    
    zSTRING& operator=(char* str) {
        Assign(this, str);
        return *this;
    }

    const char* c_str() const {
        return basicStr.data ? basicStr.data : "";
    }

    const std::string stdString() const {
        return basicStr.data ? basicStr.data : "";
    }

    const uint32_t length() const {
        return basicStr.length;
    }
};