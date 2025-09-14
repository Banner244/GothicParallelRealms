#include "Async.h"

std::mutex Async::mtxPrint;

void Async::PrintLn(const std::string &str) // STATIC
{
    std::lock_guard<std::mutex> lock(mtxPrint);
    std::cout << str << "\n";
}

void Async::Print(const std::string &str) // STATIC
{
    std::lock_guard<std::mutex> lock(mtxPrint);
    std::cout << str << "\n";
}

void Async::Cerr(const std::string &str) // STATIC
{
    std::lock_guard<std::mutex> lock(mtxPrint);
    std::cerr << str << "\n";
}