#pragma once

#include <iostream>
#include <string> 

class zSTRING {
    private:
        unsigned int length;
        unsigned int capacity;
        char* data;

    public:
        zSTRING();

        // Wrapper für den ursprünglichen Konstruktor
        void initialize(char* str);

        std::string getStr();

        void setString(char * str);

};