#pragma once

#include <iostream>
#include <vector>
#include <string>

/**
 * @class PackagingSystem
 * @brief Provides functionality for packing and serializing data into packets for network transmission.
 *
 * The PackagingSystem class is used to create packets by adding various types of data (e.g., integers, strings, floats),
 * serializing them into a format suitable for transmission over a network, and reading the contents of incoming packets.
 */
class PackagingSystem
{
public:
    /**
     * @brief Constructs a PackagingSystem with a specific packet ID.
     * @param packetId The unique identifier for the packet.
     */
    PackagingSystem(int packetId);
    ~PackagingSystem();
    /**
     * @brief Sets the packet ID for the current packet.
     * @param packetId The new packet ID.
     */
    void setPacketId(int packetId);

    /**
     * @brief Adds an integer value to the packet.
     * @param value The integer value to add to the packet.
     */
    void addInt(int value);
    /**
     * @brief Adds a string value to the packet.
     * @param value The string value to add to the packet.
     */
    void addString(std::string value);

    /**
     * @brief Adds a floating-point number to the packet.
     * @param value The floating-point number to add to the packet.
     */
    void addFloatPointNumber(double value);

    /**
     * @brief Adds a floating-point number to the packet with a specified number of decimal places.
     * @param value The floating-point number to add to the packet.
     * @param decimalPlaces The number of decimal places to preserve.
     */
    void addFloatPointNumber(double value, int decimalPlaces);

    /**
     * @brief Serializes the current packet data into a string format suitable for transmission.
     * @return A string representing the serialized packet.
     */
    std::string serializePacket();
    /**
     * @brief Reads the packet ID from a given packet string.
     * @param packet The packet string.
     * @return The packet ID read from the packet.
     */
    static int ReadPacketId(std::string &packet);
    /**
     * @brief Reads an item of type T from the given packet string, returns it and removes it from buffer.
     * @tparam T The type of the item to read.
     * @param packet The packet string containing the item data.
     * @return The item of type T extracted from the packet.
     */
    template <typename T>
    static T ReadItem(std::string &packet);

private:
    std::string mPacket; ///< The internal string storing the packet data.
    char *mPacketBufferPtr = nullptr;

    int mPacketId = 0;
    /**
     * @brief Adds an item of type T to the packet.
     * @tparam T The type of the item to add.
     * @param t The item to add to the packet.
     */
    template <typename T>
    void addItem(T t);
    void manageItem(std::string item);
    /**
     * @brief Verifies the integrity of a given packet.
     * @param packet The packet string to verify.
     * @return returns -1 if not right. 
     */
    static int VerifyPacket(std::string &packet);

    void addItemAtBeginning(std::string item);
};