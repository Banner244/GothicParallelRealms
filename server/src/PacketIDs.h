#pragma once

enum ServerPacket {
    serverHandshakeAccept = 100,
    serverDistributePosition,
    serverDistributeAnimations,
    serverDistributeRotation
    //serverSendHeartbeatRequest = 200
};

enum ClientPacket {
    clientHandshakeRequest = 100,
    clientSharePosition,
    clientShareAnimations,
    clientShareRotation
    //clientSendHeartbeat = 200
};