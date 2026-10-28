#pragma once

#include <memory>
#include <string>

class RpcDemoClient {
public:
    explicit RpcDemoClient(const std::string& target);
    ~RpcDemoClient();

    std::string Greet(const std::string& name) const;

private:
    // pimpl
    class Impl;
    std::unique_ptr<Impl> _impl;
};
