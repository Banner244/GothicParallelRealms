#pragma once

#include <iostream>
#include <unordered_map>
#include <mutex>

#include "../Models/Npc.h"
#include "../Wrapper/zCModel.h"
#include "../Wrapper/zCEventManager.h"
#include "../Network/Client.h"
#include "../../common/src/Network/Packets.h"
#include "../../common/src/Network/PackagingSystem.h"
#include "../../common/src/Async/AsyncUnorderedMap.h"
#include "../../common/src/Async/Async.h"

#include "../Models/WeaponMode.h"

class Client;
/**
 * @class MessageHandler
 * @brief Handles incoming messages from the server and processes them accordingly.
 *
 * The MessageHandler class is responsible for managing network packets received
 * from the server, interpreting them, and updating the relevant game entities.
 */
class MessageHandler
{
public:
    /**
     * @brief Constructs a MessageHandler instance.
     * @param pClients Pointer to a map storing connected NPCs, indexed by their unique identifier.
     * @param client Reference to the Client instance responsible for network communication.
     */
    MessageHandler(AsyncUnorderedMap<std::string, Npc *> *pClients, Client &client);
    /**
     * @brief Processes an incoming packet string.
     * @param stringPacket The raw packet data received from the server.
     *
     * This function determines the type of packet and calls the appropriate handler method.
     */
    void managePacket(std::string stringPacket);

private:
    AsyncUnorderedMap<std::string, Npc *> *pClients; ///< Pointer to the map storing NPCs currently in the game.
    Client *pClient;                                 ///< Pointer to the Client instance for sending and receiving messages.
    
    //bool isClientRegistered(udp::endpoint &clientEndpoint);

    void handleServerHandshakeAccept(std::string &buffer);
    void handleServerNewClientConnected(std::string &buffer);
    void handleServerRequestsHeartbeat(std::string &buffer);
    void handleServerDistributePosition(std::string &buffer);
    void handleServerDistributeAnimations(std::string &buffer);
    void handleServerDistributeWeaponMode(std::string &buffer);
    void handleServerDistributeEquip(std::string &buffer);
    void handleServerDistributeRotations(std::string &buffer);
    void handleServerRemoveClient(std::string &buffer);
};