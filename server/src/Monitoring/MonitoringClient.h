#pragma once

#include "../CommonStructures.h"
#include "../../../common/src/Async/AsyncUnorderedMap.h"
class MonitoringClient {

    public:
        MonitoringClient(AsyncUnorderedMap<std::string, CommonStructures::ClientInfo> *clients);

    private:
        AsyncUnorderedMap<std::string, CommonStructures::ClientInfo> *pClients;

        void startingMonitoringClient();
};