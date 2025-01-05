#pragma once

#include <iostream>
#include <string> 

#include <fstream>
#include <exception>
#include <windows.h>

class Debugging {
    public:
        static void LogError(const std::string& message) {
            std::ofstream logFile("error_log.txt", std::ios::app);
            if (logFile.is_open()) {
                SYSTEMTIME time;
                GetLocalTime(&time);
                logFile << "[" << time.wYear << "-" 
                        << time.wMonth << "-" 
                        << time.wDay << " "
                        << time.wHour << ":" 
                        << time.wMinute << ":" 
                        << time.wSecond << "] "
                        << message << std::endl;
                logFile.close();
            }
        }

        static void showMessageBox(std::string str) {
            LPCSTR lpText = str.c_str();
            MessageBoxA(NULL, lpText, "Loading the Functions...", MB_OK);
        }
};