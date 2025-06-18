#pragma once

#include <boost/asio.hpp>
using boost::asio::ip::udp;

namespace CommonStructures {
    struct PlayerEquipment {
        std::string meleeWeaponInstanceName;
        std::string rangedWeaponInstanceName;
        std::string armorInstanceName;
    };

    struct PlayerPosition {
        float posX;
        float posZ;
        float posY;
    };

    struct PlayerRotaion {
        float yaw;
        float pitch;
        float roll;
    };

    struct ClientInfo {
        udp::endpoint endpoint;
        std::chrono::steady_clock::time_point lastResponse;
        std::string username;

        PlayerPosition position;
        PlayerRotaion rotation;
        PlayerEquipment equip;
    };
}