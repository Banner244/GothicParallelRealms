#pragma once

#include <boost/asio.hpp>
using boost::asio::ip::udp;

namespace CommonStructures {

    struct ClientInfo {
        udp::endpoint endpoint;
        //std::time_t lastResponse;
        std::chrono::steady_clock::time_point lastResponse;
    };

}