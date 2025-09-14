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
            int serverPort = 18080;
            std::string secret = "my_secret_key";
        };
        static constexpr const char * CONFIG_FILE = "config.ini";  

        class Item
        {
            public:
                static constexpr const char * GENERAL_SERVER_IP = "General.server_ip"; 
                static constexpr const char * GENERAL_SERVER_PORT = "General.server_port";
                static constexpr const char * GENERAL_SERVER_HEADER_SECRET = "General.header_secret"; 
        };

        static Ini LoadIni()
        {
            Ini retIni;
            retIni.serverIp = IniManager::GetItem(CONFIG_FILE, Item::GENERAL_SERVER_IP);
            retIni.serverPort = std::stoi(IniManager::GetItem(IniData::CONFIG_FILE, Item::GENERAL_SERVER_PORT));
            retIni.secret = IniManager::GetItem(CONFIG_FILE, Item::GENERAL_SERVER_HEADER_SECRET);
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
            out << "server_ip =" << tempIni.serverIp << "\n";
            out << "server_port = " << std::to_string(tempIni.serverPort).c_str() << "\n";
            out << "header_secret = " << tempIni.secret << "\n\n";
        }

};