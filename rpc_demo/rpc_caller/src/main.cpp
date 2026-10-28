#include <iostream>
#include <string>

#include "rpc_client.hpp"

int main(int argc, char* argv[]) {
    std::string target = "localhost:50051";
    if (argc > 1) {
        target = argv[1];
    }

    std::cout << "[gRPC Client] Connecting to " << target << std::endl;

    RpcDemoClient client{target};

    std::string input;
    while (!std::cin.eof()) {
        std::cout << "[gRPC Client] <- ";
        std::getline(std::cin, input);

        std::cout << "[gRPC Server] -> " << client.Greet(input) << std::endl;
    }
}
