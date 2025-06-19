#pragma once

#include <iostream>
#include <map>

#include "../lib/inih/ini.h"

/**
 * @class IniManager
 * @brief Manages reading and writing of configuration files in INI format.
 * 
 * This class uses the INIH library to parse INI files and provides utility functions
 * to read specific configuration values or create a default configuration if one doesn't exist.
 */
class IniManager {
    public:    
        /**
         * @brief Retrieves a specific configuration item from an INI file.
         * 
         * @param file Path to the INI file.
         * @param item Key in the format "Section.Key" (e.g., "General.username").
         * @return The corresponding value as a string, or an empty string if not found.
         */
        static std::string GetItem(const char * file, std::string item);
    private:    
        /**
         * @brief Internal handler used as a callback for the INIH parser.
         * 
         * @param user Pointer to user-defined data (e.g., a std::map).
         * @param section Section name from the INI file (e.g., "General").
         * @param name Key name within the section.
         * @param value Corresponding value.
         * @return 1 on success, 0 on failure.
         */
        static int handler(void* user, const char* section, const char* name, const char* value);
};