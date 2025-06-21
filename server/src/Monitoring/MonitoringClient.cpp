#include "MonitoringClient.h"

MonitoringClient::MonitoringClient(IniData::Ini config, AsyncUnorderedMap<std::string, CommonStructures::ClientInfo> *clients, bool &serverRunning) 
    : configData(config), pClients(clients), pServerRunning(&serverRunning)
{
    startingMonitoringClient();
}

void MonitoringClient::startingMonitoringClient(){
    httplib::Client cli(this->configData.monitoringIp, this->configData.monitoringPort);

    while(*pServerRunning){
        std::string status= "online";
        int count = this->pClients->getUnorderedMap()->size();

        httplib::Headers headers = {
            {"X-Auth-Token", this->configData.monitoringSecret}
        };

        std::string body = 
        "{"
        "\"status\": \"" + status + "\", "
        "\"playerCount\": " + std::to_string(count) +
        "}";


        auto put_res = cli.Put("/status", headers, body, "application/json");
        //put_res.value().set_header("/status", "Ma key");
        
        if (put_res && put_res->status == 200) {
            //std::cout << "Status updated successfully\n";
        } else {
            std::cerr << "PUT failed\n";
        }

        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}