#include "PackagingSystem.h"

PackagingSystem::PackagingSystem(int packetId) {
    this->mPacketId = packetId;
}

template<typename T>
void PackagingSystem::addItem(T t) {
    std::string itemAsString = std::to_string(t);
    manageItem(itemAsString);
}

void PackagingSystem::manageItem(std::string itemAsString) {
    std::string sizeAsString = std::to_string(itemAsString.length());
    std::string completeItem = sizeAsString + "|" + itemAsString;
    this->mPacket += completeItem;
}

void PackagingSystem::setPacketId(int packetId) {
    this->mPacketId = packetId;
}

void PackagingSystem::addInt(int value) {
    addItem(value);
}

void PackagingSystem::addString(std::string value) {
    manageItem(value);
}

void PackagingSystem::addFloatPointNumber(double value) {
    addItem(value);
}

void PackagingSystem::addFloatPointNumber(double value, int decimalPlaces) {
    std::string packetValue = std::to_string(value);
    std::string valueToManage = "";
    int count = 0;
    bool gotPoint = false;

    for(char &c : packetValue){
        if(gotPoint) {
            if(count == decimalPlaces) {
                break;
            }
            count++;
        }
        if(c == '.'){
            gotPoint = true;
        }
        valueToManage += c;
    }
    
    manageItem(valueToManage);
}

int PackagingSystem::ReadPacketId(std::string &packet) { // STATIC
    if(VerifyPacket(packet) == -1) return -1;

    std::string packetId = "";

    while(packetId.length() < 3) {
        packetId += packet.at(0);
        packet.erase(packet.begin());
    }

    return std::stoi(packetId);
}

int PackagingSystem::VerifyPacket(std::string &packet){ // STATIC PRIVATE
    if (packet.empty()) return -1;
    
    int sizeReceived = packet.length();

    std::string size = "";

    while(packet.at(0) != '|') {
        size += packet.at(0);
        packet.erase(packet.begin());
    }
    packet.erase(packet.begin());

    int sizeOfPacket = std::stoi(size);
    if(sizeReceived != sizeOfPacket) {
        std::cout << "\n\tERROR -- SIZE MISMATCH RECEIVED: "<< sizeReceived <<" CONTAINING: " << sizeOfPacket << "\n";
        return -1;
    }
        
    return sizeOfPacket;
}
template<typename T>
T PackagingSystem::ReadItem(std::string &packet) { // STATIC
    if(packet.empty()) return 0;

    std::string item = "";
    std::string itemSizeStr = "";

    while(packet.at(0) != '|') {
        itemSizeStr += packet.at(0);
        packet.erase(packet.begin());
    }

    packet.erase(packet.begin());

    int itemSize = std::stoi(itemSizeStr);
    while(itemSize > 0) {
        item += packet.at(0);
        packet.erase(packet.begin());
        itemSize--;
    }

    if constexpr (std::is_same<T, int>::value) 
        return std::stoi(item);
    else if constexpr (std::is_same<T, double>::value) 
        return std::stod(item);
    else if constexpr (std::is_same<T, float>::value) 
        return std::stof(item);
    else 
        return item; 
    
    return 0;
}

std::string PackagingSystem::serializePacket() {
    addItemAtBeginning(std::to_string(this->mPacketId));
    addItemAtBeginning("|");

    size_t size = mPacket.length();
    size += std::to_string(size).length();

    if(size < (mPacket.length() + std::to_string(size).length()))
        size++;

    addItemAtBeginning(std::to_string(size));
    std::string s = "";

    return mPacket;
}

void PackagingSystem::addItemAtBeginning(std::string item) {
    std::string temp = item;
    item += mPacket;
    mPacket = item;
}

PackagingSystem::~PackagingSystem() {
    delete[] mPacketBufferPtr;
}

template int PackagingSystem::ReadItem<int>(std::string&);
template float PackagingSystem::ReadItem<float>(std::string&);
template double PackagingSystem::ReadItem<double>(std::string&);
template std::string PackagingSystem::ReadItem<std::string>(std::string&);