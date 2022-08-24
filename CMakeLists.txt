cmake_minimum_required(VERSION 3.0.0)
project(packets VERSION 0.0.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(client source/client.c source/error.c source/clock.c)
add_executable(server source/server.c source/sleep.c source/ring.c 
                      source/error.c source/thread.c source/proc.c 
                      source/mutex.c)

if (WIN32)
    target_link_libraries(client Ws2_32)
    target_link_libraries(server Ws2_32)
else()
    target_link_libraries(server pthread)
endif()

target_include_directories(client PRIVATE include)
target_include_directories(server PRIVATE include)
