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