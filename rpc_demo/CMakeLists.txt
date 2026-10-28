project(rpc_demo CXX)

find_package(protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

add_subdirectory(proto)


file(GLOB SOURCE CONFIGURE_DEPENDS rpc_caller/src/*.cpp)

add_executable(rpc_caller ${SOURCE})

target_include_directories(rpc_caller PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/rpc_caller/include
    ${CMAKE_CURRENT_BINARY_DIR}/proto/generated
)

target_link_libraries(rpc_caller
  PRIVATE
    rt
    rpc_demo_proto
    gRPC::grpc++
    protobuf::libprotobuf
)
