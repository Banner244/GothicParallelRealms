#pragma once

#include <iostream>
#include <vector>
#include <string>

class PackagingSystem {
    public:
        PackagingSystem(int packetId);
        ~PackagingSystem();
        void setPacketId(int packetId);

        void addInt(int value);
        void addString(std::string value);
        void addFloatPointNumber(double value);
        void addFloatPointNumber(double value, int decimalPlaces);

        std::string serializePacket();

        static int ReadPacketId(std::string &packet);
        template<typename T>
        static T ReadItem(std::string &packet);

    private:
        std::string mPacket;
        char * mPacketBufferPtr = nullptr;

        int mPacketId = 0;

        template<typename T>
        void addItem(T t);
        void manageItem(std::string item);
        static int VerifyPacket(std::string &packet);

        void addItemAtBeginning(std::string item);
};