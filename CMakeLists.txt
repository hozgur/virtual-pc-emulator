cmake_minimum_required(VERSION 3.10)
project(VirtualPC C)

set(CMAKE_C_STANDARD 99)

include_directories(src)

add_executable(virtual_pc
    src/main.c
    src/video_controller.c
    src/call_ret_example.c
)
