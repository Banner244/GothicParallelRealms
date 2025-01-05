#pragma once

#include <iostream>
#include <string> 

class ZCView {
    private:
        int field_30 = 0;
        int field_34 = 0;
        int field_2c = 0;
        int field_84 = 0;
        int field_80 = 0;
        std::string field_cc;

    public:
        // Wrapper für den ursprünglichen Konstruktor
        void initialize();

        std::string getValues();

};