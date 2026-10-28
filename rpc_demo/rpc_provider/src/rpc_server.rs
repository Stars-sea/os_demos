mod proto {
    tonic::include_proto!("rpc_demo");
}

use proto::rpc_demo_server::RpcDemo;
use tonic::{Request, Response, Status};

pub use proto::rpc_demo_server::RpcDemoServer;
#[allow(unused)]
pub use proto::{GreetingRequest, GreetingResponse};

#[derive(Default)]
pub struct RpcDemoImpl;

#[tonic::async_trait]
impl RpcDemo for RpcDemoImpl {
    async fn greet(
        &self,
        request: Request<GreetingRequest>,
    ) -> Result<Response<GreetingResponse>, Status> {
        let GreetingRequest { name } = request.into_inner();

        let resp = GreetingResponse {
            message: format!("Hello {name}! This is Rust RPC provider!"),
        };
        Ok(Response::new(resp))
    }
}
