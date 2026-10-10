project(rpc_demo CXX)

file(GLOB SOURCE rpc_caller/*.cpp)

add_executable(rpc_caller ${SOURCE})

target_include_directories(rpc_caller PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/rpc_caller/include
)

target_link_libraries(rpc_caller PRIVATE rt)
