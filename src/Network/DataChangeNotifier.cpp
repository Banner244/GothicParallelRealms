#include "DataChangeNotifier.h"

DataChangeNotifier::DataChangeNotifier(Client *client) : pClient(client){
    pMainPlayer = client->getMainPlayer();

    initListValues();
}

void DataChangeNotifier::initListValues() {
    playerState.push_back( [this]() { 
        DataStructures::LastPosition retLastPos = pMainPlayer->getLastPosition();
        if(!playerLastPos.isSame(retLastPos)) {
            pClient->sendPlayerPosition();
        }
    });

    playerState.push_back( [this]() { 
        DataStructures::LastAnimation retLastAnim = pMainPlayer->getLastAnimation();
        if(!playerLastAnim.isSame(retLastAnim)) {
            pClient->sendPlayerAnimation();
        }
    });

    playerState.push_back( [this]() { 
        DataStructures::LastEquip retLastEquip = pMainPlayer->getLastEquip();
        if(!playerLastEquip.isSame(retLastEquip)) {
            pClient->sendPlayerEquip();
        }
    });
    /*playerState.push_back( [this]() { 
        DataStructures::LastRotation retLastRot = pMainPlayer->getLastRotation();
        if(!playerLastRotation.isSame(retLastRot)) {
            pClient->sendPlayerRotation();
        }
    });*/
}

void DataChangeNotifier::sendChanges() {
    for (const auto& states : playerState) {
        states();  
    }
}