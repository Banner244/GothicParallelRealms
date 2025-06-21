#pragma once

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include "../../common/src/IniManager.h"


class IniData {
    public:
        struct Ini {
            std::string serverIp = "127.0.0.1";
            int serverPort = 12345;

            bool monitoringActive = false;
            std::string monitoringIp = "127.0.0.1";
            int monitoringPort = 18080;
            std::string monitoringSecret = "my_secret_key";
        };

        static constexpr const char * CONFIG_FILE = "config.ini";  

        class Item
        {
            public:
                static constexpr const char * GENERAL_SERVER_IP = "General.server_ip"; 
                static constexpr const char * GENERAL_SERVER_PORT = "General.server_port"; 

                static constexpr const char * MONITORING_ACTIVE = "Monitoring.active"; 
                static constexpr const char * MONITORING_IP = "Monitoring.server_ip";
                static constexpr const char * MONITORING_PORT = "Monitoring.server_port";
                static constexpr const char * MONITORING_HEADER_SECRET = "Monitoring.header_secret";
        };

        static Ini LoadIni()
        {
            Ini retIni;
            retIni.serverIp = IniManager::GetItem(CONFIG_FILE, Item::GENERAL_SERVER_IP);
            retIni.serverPort = std::stoi(IniManager::GetItem(CONFIG_FILE, Item::GENERAL_SERVER_PORT));

            std::string active = IniManager::GetItem(CONFIG_FILE, Item::MONITORING_ACTIVE);
            if(active == "true")
                retIni.monitoringActive = true;
            retIni.monitoringIp = IniManager::GetItem(CONFIG_FILE, Item::MONITORING_IP);
            retIni.monitoringPort = std::stoi(IniManager::GetItem(CONFIG_FILE, Item::MONITORING_PORT));
            retIni.monitoringSecret = IniManager::GetItem(CONFIG_FILE, Item::MONITORING_HEADER_SECRET);
            return retIni;
        }

        static bool CreateConfigIfMissing(const std::string& path) // STATIC
        {
            writeConfig(path);

            if (std::filesystem::exists(path))
                return true;
            
            return false;
        }

    private:
        static void writeConfig(const std::string& path)
        {
            if (std::filesystem::exists(path))
                return;
            
            Ini tempIni;
            std::ofstream out(path);
            out << "[General]\n";
            out << "server_ip = " << tempIni.serverIp << "\n";
            out << "server_port = " << std::to_string(tempIni.serverPort) << "\n\n";

            out << "[Monitoring]\n";
            out << "active = false\n";
            out << "server_ip = " << tempIni.monitoringIp << "\n";
            out << "server_port = " << std::to_string(tempIni.monitoringPort) << "\n";
            out << "header_secret = " << tempIni.monitoringSecret << "\n";
        }

};