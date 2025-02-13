#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <boost/asio.hpp>

#include "ServerManager.h"

#include "MessageHandler.h"

using boost::asio::ip::udp;

int main()
{
    try
    {
        boost::asio::io_context io_context;
        boost::asio::io_context processing_context;
        boost::asio::executor_work_guard<boost::asio::io_context::executor_type> work_guard(processing_context.get_executor());

        ServerManager serverManager(io_context, processing_context);

        const size_t thread_count = std::max(1u, std::thread::hardware_concurrency() / 2);
        std::cout << "Using " << thread_count << " network threads.\n";

        std::vector<std::thread> threads;
        for (size_t i = 0; i < thread_count; ++i)
        {
            threads.emplace_back([&io_context]()
                                 { io_context.run(); });
        }

        const size_t processing_threads = std::max(1u, std::thread::hardware_concurrency() / 2);
        std::cout << "Using " << processing_threads << " processing threads.\n";
        for (size_t i = 0; i < processing_threads; ++i)
        {
            threads.emplace_back([&processing_context]() { processing_context.run(); });
        }

        // waiting for the end of all threads
        for (auto &thread : threads)
        {
            thread.join();
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Fehler: " << e.what() << std::endl;
    }
    return 0;
}