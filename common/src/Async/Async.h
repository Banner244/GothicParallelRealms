#pragma once

#include <iostream>
#include <mutex>

class Async {

    public:
        static void PrintLn(const std::string &str);
        static void Print(const std::string &str);
        static void Cerr(const std::string &str) ;

    private:
        static std::mutex mtxPrint;

};