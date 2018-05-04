#pragma once

#include <string>
#include <map>

#include "../../external/zmq.hpp"

namespace usd_zmq
{

    constexpr auto TANK_PREFIX = "tank://";
    constexpr auto TANK_PREFIX_SHORT = "tank:";

    constexpr auto ZMQ_SERVER = "localhost";
    constexpr auto ZMQ_PORT = "5555";

    const double ZMQ_TIMEOUT = 100.0;

    struct zmqQueryCache {
        std::string resolved_path;
        std::time_t timestamp;
    };

    class zmqDispatch {
        public:
            zmqDispatch();
            ~zmqDispatch();

            std::string resolve_name(const std::string& a_path);
            bool resolve_exists(const std::string& a_path);
            bool matches_schema(const std::string& a_path);
        
        protected:
            std::string parse_query(const std::string& a_query);

        protected:
            

            //<Tank_Query, Cache_Result>
            std::map<std::string, zmqQueryCache> m_cachedQueries;
    };
}