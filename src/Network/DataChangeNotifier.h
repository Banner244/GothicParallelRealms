#pragma once

#include <iostream>
#include <vector>

#include "../Models/DataStructures.h"
#include "Client.h"

#include <functional>
/**
 * @class DataChangeNotifier
 * @brief Monitors player state changes and notifies the server.
 *
 * The DataChangeNotifier class tracks changes in the player's information. When a change is detected, it sends the updated data to the server
 * through the associated Client instance.
 */
class DataChangeNotifier
{

public:
    /**
     * @brief Constructs a DataChangeNotifier instance.
     * @param client Pointer to the Client instance for communication with the server.
     */
    DataChangeNotifier(Client *client);
    /**
     * @brief Sends any detected changes in the player's state to the server.
     *
     * This method compares the current player state with the last known values
     * and sends updates only if changes are detected.
     */
    void sendChanges();

private:
    /**
     * @brief Initializes the list of player state monitoring functions.
     *
     * This method sets up function pointers that track changes in the player's
     * position, animation, and rotation.
     */
    void initListValues();

    std::vector<std::function<void()>> playerState; ///< List of functions that check for changes in player state.

    Client *pClient;
    Npc *pMainPlayer;

    DataStructures::LastPosition playerLastPos;
    DataStructures::LastAnimation playerLastAnim;
    DataStructures::LastRotation playerLastRotation;
};