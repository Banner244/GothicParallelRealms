#pragma once

enum ServerPacket {
    serverHandshakeAccept = 100,
    serverDistributePosition,
    serverDistributeAnimations,

    //serverSendHeartbeatRequest = 200

};

enum ClientPacket {
    clientHandshakeRequest = 100,
    clientSharePosition,
    clientShareAnimations
    //clientSendHeartbeat = 200
};

/*namespace ServerPacket {

}*/