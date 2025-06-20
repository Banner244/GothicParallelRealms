#pragma once

#include "../CommonStructures.h"
#include "../../../common/src/Async/AsyncUnorderedMap.h"
#include "../../../common/lib/cpp-httplib/httplib.h"

//TODO: Add .ini file for IP:Port and ask if monitoring is active

class MonitoringClient {

    public:
        MonitoringClient(std::string ip, int port, AsyncUnorderedMap<std::string, CommonStructures::ClientInfo> *clients, bool &serverRunning);
        MonitoringClient();
        void startingMonitoringClient();
    private:
        AsyncUnorderedMap<std::string, CommonStructures::ClientInfo> *pClients;
        bool *pServerRunning;
        
        std::string ip = "127.0.0.1";
        int port = 18080;
};