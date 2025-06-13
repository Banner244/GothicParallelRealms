#include "IniManager.h"
#include <filesystem>
#include <fstream>

std::string IniManager::GetItem(const char * file, std::string item) // STATIC
{
    std::map<std::string, std::string> config;
    if (ini_parse(file, handler, &config) < 0) {
        std::cerr << "Can not load config.ini\n";
        return "ERROR";
    }

    return config[item];
}

int IniManager::handler(void *user, const char *section, const char *name, const char *value) // STATIC
{
    std::map<std::string, std::string> *config = reinterpret_cast<std::map<std::string, std::string> *>(user);
    std::string key = std::string(section) + "." + name;
    (*config)[key] = value;
    return 1;
}

bool IniManager::CreateConfigIfMissing(const std::string& path) // STATIC
{
    writeConfig(path);

    if (std::filesystem::exists(path))
        return true;
    
    return false;
}

void IniManager::writeConfig(const std::string& path) // STATIC
{
    if (std::filesystem::exists(path))
        return;
    
    std::ofstream out(path);
    out << "[General]\n";
    out << "username = Player1\n";
    out << "server_ip = 127.0.0.1\n";
    out << "server_port = 12345\n";
}