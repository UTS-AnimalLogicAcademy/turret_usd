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

    const auto ZMQ_TIMEOUT = 60000;    
    //const auto ZMQ_TIMEOUT = 120;

    const bool ZMQ_CACHE_QUERIES = false;
    const auto ZMQ_CACHE_TIMEOUT = 100.0;

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

            void SetUseCache(bool a_shouldUseCache) { m_useCache = a_shouldUseCache; }
        
        protected:
            std::string parse_query(const std::string& a_query);

        protected:
            bool m_useCache;

            //<Tank_Query, Cache_Result>
            std::map<std::string, zmqQueryCache> m_cachedQueries;
    };
}