use tonic::transport::Server;

mod rpc_server;

#[tokio::main]
async fn main() -> anyhow::Result<()> {
    let addr = "[::1]:50051".parse()?;
    let greeter = rpc_server::RpcDemoImpl::default();

    println!("RpcDemoServer listening on {addr}");

    Server::builder()
        .add_service(rpc_server::RpcDemoServer::new(greeter))
        .serve(addr)
        .await?;

    Ok(())
}
