project(shm_demo CXX)

file(GLOB COMMON common/*.cpp)

add_executable(shm_producer shm_producer.cpp ${COMMON})
add_executable(shm_consumer shm_consumer.cpp ${COMMON})

target_include_directories(shm_producer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include
)

target_include_directories(shm_consumer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(shm_producer PRIVATE rt pthread)
target_link_libraries(shm_consumer PRIVATE rt pthread)
