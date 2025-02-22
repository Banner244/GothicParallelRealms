#pragma once

namespace Packets {
    enum ServerPacket {
        serverHandshakeAccept = 100,
        serverRequestHeartbeat,
        serverDistributePosition,
        serverDistributeAnimations,
    
        //serverSendHeartbeatRequest = 200
    
    };
    
    enum ClientPacket {
        clientHandshakeRequest = 100,
        clientResponseHeartbeat,
        clientSharePosition,
        clientShareAnimations
        //clientSendHeartbeat = 200
    };
}


/*namespace ServerPacket {

}*/