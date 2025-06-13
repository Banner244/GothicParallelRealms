#pragma once

namespace Packets {
    enum ServerPacket {
        serverHandshakeAccept = 100,
        serverNewClientConnected,
        serverRequestHeartbeat,
        serverDistributePosition,
        serverDistributeAnimations,
        serverRemoveClient

    };
    
    enum ClientPacket {
        clientHandshakeRequest = 100,
        clientResponseHeartbeat,
        clientSharePosition,
        clientShareAnimations
        
    };
}