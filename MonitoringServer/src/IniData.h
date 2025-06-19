#pragma once

#include <iostream>
#include <filesystem>
#include <fstream>

class IniData {
    public:
        static constexpr char * CONFIG_FILE = "config.ini";  

        class Item
        {
            public:
                static constexpr char * GENERAL_SERVER_IP = "General.server_ip"; 
                static constexpr char * GENERAL_SERVER_PORT = "General.server_port"; 
        };

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
            
            std::ofstream out(path);
            out << "[General]\n";
            out << "server_ip = 127.0.0.1\n";
            out << "server_port = 18080\n\n";
        }

};