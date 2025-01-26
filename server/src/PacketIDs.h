#pragma once

enum ServerPacket {
    serverHandshakeAccept = 100,
    serverDistributePosition,

    //serverSendHeartbeatRequest = 200

};

enum ClientPacket {
    clientHandshakeRequest = 100,
    clientSharePosition,

    //clientSendHeartbeat = 200
};

/*namespace ServerPacket {

}*/