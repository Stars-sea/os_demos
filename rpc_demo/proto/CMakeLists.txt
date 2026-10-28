find_package(protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

add_library(rpc_demo_proto STATIC "${CMAKE_CURRENT_LIST_DIR}/rpc_demo.proto")
set_target_properties(rpc_demo_proto PROPERTIES LINKER_LANGUAGE CXX)


target_link_libraries(rpc_demo_proto
  PUBLIC
    protobuf::libprotobuf
    gRPC::grpc++
)

set(PROTO_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
file(MAKE_DIRECTORY "${PROTO_BINARY_DIR}")

target_include_directories(rpc_demo_proto
  PUBLIC "$<BUILD_INTERFACE:${PROTO_BINARY_DIR}>")

protobuf_generate(
  TARGET rpc_demo_proto
  IMPORT_DIRS "${CMAKE_CURRENT_LIST_DIR}"
  PROTOC_OUT_DIR "${PROTO_BINARY_DIR}"
)

protobuf_generate(
  TARGET rpc_demo_proto
  LANGUAGE grpc
  GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
  PLUGIN "protoc-gen-grpc=$<TARGET_FILE:gRPC::grpc_cpp_plugin>"
  IMPORT_DIRS "${CMAKE_CURRENT_LIST_DIR}"
  PROTOC_OUT_DIR "${PROTO_BINARY_DIR}"
)
