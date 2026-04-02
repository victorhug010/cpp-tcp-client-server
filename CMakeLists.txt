cmake_minimum_required(VERSION 3.10)
project(KEYFLUX)

set(CMAKE_CXX_STANDARD 17)

add_executable(KEYFLUX_SERVER
    src/main.cpp
    src/server.cpp
    src/commands.cpp
)

add_executable(KEYFLUX_CLIENT
    src/client_main.cpp
    src/client.cpp
)