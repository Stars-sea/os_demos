#include "rpc_client.hpp"
#include "rpc_demo.grpc.pb.h"

#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/support/status.h>
#include <memory>
#include <string>
#include <chrono>

using namespace std::chrono_literals;

class RpcDemoClient::Impl {
public:
    Impl(const std::string& target) {
        _channel = grpc::CreateChannel(target, grpc::InsecureChannelCredentials());
        _stub    = rpc_demo::RpcDemo::NewStub(_channel);
    }

    std::string Greet(const std::string &name) const {
        rpc_demo::GreetingRequest req;
        req.set_name(name);

        rpc_demo::GreetingResponse resp;
        grpc::ClientContext ctx;

        ctx.set_deadline(std::chrono::system_clock::now() + 5s);

        grpc::Status status = _stub->Greet(&ctx, req, &resp);
        if (status.ok()) {
            return resp.message();
        }

        return "RPC Failed: " + status.error_message();
    }

private:
    std::shared_ptr<grpc::Channel> _channel;
    std::unique_ptr<rpc_demo::RpcDemo::Stub> _stub;
};

RpcDemoClient::RpcDemoClient(const std::string &target)
    : _impl(std::make_unique<RpcDemoClient::Impl>(std::move(target))) {}

RpcDemoClient::~RpcDemoClient()=default;

std::string RpcDemoClient::Greet(const std::string &name) const {
    return _impl->Greet(name);
}
