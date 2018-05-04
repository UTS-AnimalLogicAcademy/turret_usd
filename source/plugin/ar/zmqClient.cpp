#include "zmqClient.h"

#include <iostream>
#include <map>
#include <ctime>
#include <string>

#include "../../external/zmq.hpp"

namespace {

    struct Cache {
        std::string resolved_path;
        std::time_t timestamp;
    };

    //<Tank_Query, Cache_Result>
    std::map<std::string, Cache> cached_queries;

    std::string parse_path(const std::string& a_path)
    {
        // Search for cached result
        //const auto cached_result = cached_queries.find(a_path);

        /*if (cached_result != cached_queries.end()) {
            //std::cout << "Current time: " << std::time(0) << "\n";
            //std::cout << "Cache time: " << cached_result->second.timestamp << "\n";
            // If cache is still fresh
            //if(std::time(0) - cached_result->second.timestamp <= usd_zmq::ZMQ_TIMEOUT)
            std::cout << "Received Cached response: " << cached_result->second.resolved_path << "\n\n\n";
                return cached_result->second.resolved_path;
        }*/

        // Create zmq connection
        zmq::context_t context(1);
        zmq::socket_t socket(context, ZMQ_REQ);

        const char* env_p = std::getenv("ALA_USD_RESOLVER_LOG_LEVEL");
        const std::string env_s = std::string(env_p);
        if(env_s == "1"){
            std::cout << "ALA USD Resolver - connecting to local zmq server..." << "\n\n";
        }

        socket.connect("tcp://" + std::string(usd_zmq::ZMQ_SERVER) + ":" + std::string(usd_zmq::ZMQ_PORT));

        socket.setsockopt(ZMQ_LINGER, 5000);
        socket.setsockopt(ZMQ_RCVTIMEO, 5000);
        
        // Create zmq request
        zmq::message_t request(a_path.length());

        memcpy(request.data(), a_path.c_str(), a_path.length());

        //std::cout << "Sending request: " << a_path << "\n";

        // Send zmq request
        socket.send(request, ZMQ_NOBLOCK);

        // Wait for the reply
        zmq::message_t reply;
        socket.recv(&reply);        

        // Store the reply
        std::string realPath = std::string((char *)reply.data());

        if(env_s == "1"){
            std::cout << "ALA USD Resolver - received real response: " << realPath << "\n\n";
        }

        // Cache reply
        //Cache cache = {realPath, std::time(0)};
        //cached_queries.insert(std::make_pair(a_path, cache));

        return realPath;
    }
}

namespace usd_zmq
{
    zmqClient::zmqClient()
    {

    }

    zmqClient::~zmqClient()
    {

    }

    std::string zmqClient::resolve_name(const std::string& a_path)
    {
        const char* env_p = std::getenv("ALA_USD_RESOLVER_LOG_LEVEL");
        const std::string env_s = std::string(env_p);
        if(env_s == "1"){
            std::cout << "ALA USD Resolver - resolving name: " << a_path << "\n\n";
        }

        const auto parsed_path = parse_path(a_path);
        return parsed_path;
    }

    // Returns if path matches tank query schema
    bool zmqClient::matches_schema(const std::string& a_path)
    {
        return a_path.find(TANK_PREFIX_SHORT) == 0;
    }
}