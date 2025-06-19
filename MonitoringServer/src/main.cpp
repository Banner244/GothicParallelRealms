#include <iostream>
#include <mutex>

#include "../../common/src/IniManager.h"

#include "IniData.h"

#include "crow.h"
//#include "crow_all.h"

class IniManager;

std::string ascii = R"(
  ____  _____ ____ _____   __  __             _ _             
 |  _ \| ____/ ___|_   _| |  \/  | ___  _ __ (_) |_ ___  _ __ 
 | |_) |  _| \___ \ | |   | |\/| |/ _ \| '_ \| | __/ _ \| '__|
 |  _ <| |___ ___) || |   | |  | | (_) | | | | | || (_) | |   
 |_| \_\_____|____/ |_|   |_|  |_|\___/|_| |_|_|\__\___/|_|
)";

std::mutex mtx_serverData;

struct Ini {
    std::string serverIp = "127.0.0.1";
    int serverPort = 18080;
} config;

struct GothicServerData {
    std::string status = "offline";
    int playerCount = 0;

} serverData;

Ini getConfigData();


/*This RestAPI receives every 5 Seconds a Message from the GothicServer, if there is no answer for more than 7 Seconds,
this RestAPI-Sever answers with an Offline-Status.
*/
int main()
{
    std::cout << ascii << "\n\n";
    Ini configData = getConfigData();

    crow::SimpleApp app; //define your crow application

    auto lastResponse = std::chrono::high_resolution_clock::now();

    // GET /status
    CROW_ROUTE(app, "/status").methods("GET"_method)([&lastResponse] {
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = currentTime - lastResponse;
        int durrationInSec = static_cast<int>(elapsed.count()/1000);

        crow::json::wvalue res;
        if(durrationInSec > 7) {
            res["status"] = "offline";
            res["playerCount"] = "0";
        } else {
            std::lock_guard<std::mutex> lock(mtx_serverData);

            res["status"] = serverData.status;
            res["playerCount"] = std::to_string(serverData.playerCount);
        }
        return res;
    });

    // PUT /status
    CROW_ROUTE(app, "/status").methods("PUT"_method)([&lastResponse](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body || !body.has("status")) {
            return crow::response(400, "Missing 'status' field");
        }
        lastResponse = std::chrono::high_resolution_clock::now();
        std::lock_guard<std::mutex> lock(mtx_serverData);
        serverData.status = body["status"].s();
        serverData.playerCount = body["playerCount"].i();

        return crow::response(200, "Updated");
    });

    app.port(18080).multithreaded().run();
}

Ini getConfigData() {
    Ini ret;
    // #### LOADIN INI ####
    IniManager manager;
    if(!IniData::CreateConfigIfMissing(IniData::CONFIG_FILE))
        return ret;
    else 
        std::cout << "-- Config loaded --" << "\n";

    ret.serverIp = manager.GetItem(IniData::CONFIG_FILE, IniData::Item::GENERAL_SERVER_IP);
    ret.serverPort = std::stoi(manager.GetItem(IniData::CONFIG_FILE, IniData::Item::GENERAL_SERVER_PORT));
    return ret;
}