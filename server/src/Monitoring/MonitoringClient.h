#pragma once

#include "../IniData.h"

#include "../CommonStructures.h"
#include "../../../common/src/Async/AsyncUnorderedMap.h"
#include "../../../common/lib/cpp-httplib/httplib.h"

//TODO: Add .ini file for IP:Port and ask if monitoring is active

class MonitoringClient {

    public:
        MonitoringClient(IniData::Ini config, AsyncUnorderedMap<std::string, CommonStructures::ClientInfo> *clients, bool &serverRunning);
        void startingMonitoringClient();
    private:
        AsyncUnorderedMap<std::string, CommonStructures::ClientInfo> *pClients;
        bool *pServerRunning;
        
        IniData::Ini configData;
};