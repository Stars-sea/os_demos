use tonic::transport::Server;

mod rpc_server;

#[tokio::main]
async fn main() -> anyhow::Result<()> {
    env_logger::init();

    let addr = "[::1]:50051".parse()?;
    let greeter = rpc_server::RpcDemoImpl::default();

    log::info!("RpcDemoServer listening on {addr}");

    Server::builder()
        .add_service(rpc_server::RpcDemoServer::new(greeter))
        .serve(addr)
        .await?;

    Ok(())
}
