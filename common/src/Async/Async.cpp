#include "Async.h"

std::mutex Async::mtxPrint;

void Async::PrintLn(std::string str) // STATIC
{
    std::lock_guard<std::mutex> lock(mtxPrint);
    std::cout << str << "\n";
}

void Async::Print(std::string str) // STATIC
{
    std::lock_guard<std::mutex> lock(mtxPrint);
    std::cout << str << "\n";
}

void Async::Cerr(std::string str) // STATIC
{
    std::lock_guard<std::mutex> lock(mtxPrint);
    std::cerr << str << "\n";
}