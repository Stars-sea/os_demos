fn main() {
    tonic_prost_build::configure()
        .build_client(false)
        .compile_protos(&["../proto/rpc_demo.proto"], &["../proto"])
        .unwrap();

    println!("cargo:rerun-if-changed=build.rs");
    println!("cargo:rerun-if-changed=../proto/rpc_demo.proto");
}
