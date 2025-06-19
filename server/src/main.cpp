#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <boost/asio.hpp>

#include "ServerManager.h"
#include "IniData.h"

#include "MessageHandler.h"
//#include "../../common/src/IniManager.h"

using boost::asio::ip::udp;


std::string ascii = R"(
  ____                 _ _      _   ____            _               
 |  _ \ __ _ _ __ __ _| | | ___| | |  _ \ ___  __ _| |_ __ ___  ___ 
 | |_) / _` | '__/ _` | | |/ _ \ | | |_) / _ \/ _` | | '_ ` _ \/ __|
 |  __/ (_| | | | (_| | | |  __/ | |  _ <  __/ (_| | | | | | | \__ \
 |_|   \__,_|_|  \__,_|_|_|\___|_| |_| \_\___|\__,_|_|_| |_| |_|___/
)";


CommonStructures::Ini getConfigData() {
    CommonStructures::Ini ret;
    // #### LOADIN INI ####
    IniManager manager;
    if(!IniData::CreateConfigIfMissing(IniData::CONFIG_FILE))
        return ret;
    else 
        std::cout << "-- Config loaded --" << "\n";

    ret.serverIp = manager.GetItem(IniData::CONFIG_FILE, IniData::Item::GENERAL_SERVER_IP);
    ret.serverPort = std::stoi(manager.GetItem(IniData::CONFIG_FILE, IniData::Item::GENERAL_SERVER_PORT));

    std::string active = manager.GetItem(IniData::CONFIG_FILE, IniData::Item::MONITORING_ACTIVE);
    if(active == "true")
        ret.monitoringActive = true;
    ret.monitoringIp = manager.GetItem(IniData::CONFIG_FILE, IniData::Item::MONITORING_IP);
    ret.monitoringPort = std::stoi(manager.GetItem(IniData::CONFIG_FILE, IniData::Item::MONITORING_PORT));

    return ret;
}

int main()
{
    std::cout << ascii << "\n\n";
    try
    {
        CommonStructures::Ini configData = getConfigData();

        boost::asio::io_context io_context;
        boost::asio::io_context processing_context;
        boost::asio::executor_work_guard<boost::asio::io_context::executor_type> work_guard(processing_context.get_executor());

        ServerManager serverManager(io_context, processing_context, configData);

        const size_t thread_count = std::max(1u, std::thread::hardware_concurrency() / 2);
        std::cout << "Using " << thread_count << " network threads.\n";

        std::vector<std::thread> threads;
        for (size_t i = 0; i < thread_count; ++i)
        {
            threads.emplace_back([&io_context]()
                                 { io_context.run(); });
        }

        const size_t processing_threads = std::max(1u, std::thread::hardware_concurrency() / 2);
        std::cout << "Using " << processing_threads << " processing threads.\n";
        for (size_t i = 0; i < processing_threads; ++i)
        {
            threads.emplace_back([&processing_context]() { processing_context.run(); });
        }

        //serverManager.watchingHeartbeat();

        // waiting for the end of all threads
        for (auto &thread : threads)
        {
            thread.join();
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Fehler: " << e.what() << std::endl;
    }
    return 0;
}