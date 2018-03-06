#pragma once

#include <string>

namespace usd_zmq
{

    constexpr auto TANK_PREFIX = "tank://";
    constexpr auto TANK_PREFIX_SHORT = "tank:";

    class zmqClient {
        public:
            zmqClient();
            ~zmqClient();

            std::string resolve_name(const std::string& a_path);
            bool matches_schema(const std::string& a_path);
    };
}