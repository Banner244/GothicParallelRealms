#pragma once

#include <iostream>
#include <filesystem>
#include <fstream>

class IniData {
    public:
        struct Ini {
            std::string username = "Player";
            std::string serverIp = "127.0.0.1";
            std::string serverPort = "12345";
        };
        /**
         * @brief Default filename for the client configuration file.
         */
        static constexpr const char * CLIENT_CONFIG_FILE = "gpr_config.ini";   

        /**
         * @class Item
         * @brief Contains predefined keys for accessing configuration values.
         */
        class Item
        {
            public:
                static constexpr const char * GENERAL_USERNAME = "General.username"; 
                static constexpr const char * GENERAL_SERVER_IP = "General.server_ip"; 
                static constexpr const char * GENERAL_SERVER_PORT = "General.server_port"; 
        };

        static Ini LoadIni()
        {
            Ini retIni;
            retIni.username = IniManager::GetItem(CLIENT_CONFIG_FILE, Item::GENERAL_USERNAME);
            retIni.serverIp = IniManager::GetItem(CLIENT_CONFIG_FILE, Item::GENERAL_SERVER_IP);
            retIni.serverPort = IniManager::GetItem(CLIENT_CONFIG_FILE, Item::GENERAL_SERVER_PORT);
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
            out << "username = " << tempIni.username << "\n";
            out << "server_ip = " << tempIni.serverIp << "\n";
            out << "server_port = " << tempIni.serverPort << "\n\n";
        }

};