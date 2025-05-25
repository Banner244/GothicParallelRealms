#pragma once

#include <iostream>
#include <mutex>

class Async {

    public:
        static void PrintLn(std::string str);
        static void Print(std::string str);
        static void Cerr(std::string str) ;

    private:
        static std::mutex mtxPrint;

};