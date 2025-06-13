#pragma once

#include <boost/asio.hpp>
using boost::asio::ip::udp;

namespace CommonStructures {
    struct ClientInfo {
        udp::endpoint endpoint;
        std::chrono::steady_clock::time_point lastResponse;
        std::string username;
    };
}