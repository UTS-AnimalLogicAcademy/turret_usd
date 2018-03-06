#include "zmqClient.h"

#include <iostream>
#include "../../external/zmq.hpp"

namespace {
    std::string parse_path(const std::string& a_path)
    {
        zmq::context_t context(1);
        zmq::socket_t socket(context, ZMQ_REQ);

        std::cout << "Connecting to local zmq server..." << "\n";

        socket.connect("tcp://localhost:5555");

        std::string req = a_path;

        zmq::message_t request(req.length());

        memcpy(request.data(), req.c_str(), req.length());

        std::cout << "Sending request: " << req << "\n";

        socket.send(request);


        // Get the reply

        zmq::message_t reply;
        socket.recv(&reply);

        std::string realPath = std::string((char *)reply.data());

        std::cout << "Received response: " << realPath << "\n\n\n";

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
        const auto parsed_path = parse_path(a_path);
        return parsed_path;
    }

    // Returns if path matches tank query schema
    bool zmqClient::matches_schema(const std::string& a_path)
    {
        return a_path.find(TANK_PREFIX_SHORT) == 0;
    }
}