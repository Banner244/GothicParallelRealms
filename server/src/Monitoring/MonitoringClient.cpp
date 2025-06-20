#include "MonitoringClient.h"

MonitoringClient::MonitoringClient(std::string ip, int port, AsyncUnorderedMap<std::string, CommonStructures::ClientInfo> *clients, bool &serverRunning) 
    : ip(ip), port(port), pClients(clients), pServerRunning(&serverRunning)
{
    startingMonitoringClient();
}

void MonitoringClient::startingMonitoringClient(){
    httplib::Client cli(this->ip, this->port);

    while(*pServerRunning){
        std::string status= "online";
        int count = this->pClients->getUnorderedMap()->size();

        std::string body = 
        "{"
        "\"status\": \"" + status + "\", "
        "\"playerCount\": " + std::to_string(count) +
        "}";

        auto put_res = cli.Put("/status", body, "application/json");
        if (put_res && put_res->status == 200) {
            //std::cout << "Status updated successfully\n";
        } else {
            std::cerr << "PUT failed\n";
        }

        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}