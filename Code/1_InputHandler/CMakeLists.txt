cmake_minimum_required(VERSION 3.10)
project(TeamA)
set(CMAKE_CXX_STANDARD 17)

include_directories(Include)
include_directories(../4_CommonUtils/CANIO/Include)
include_directories(../4_CommonUtils/DataBase/Include)

# Create executable for InputHandlerMain
add_executable(InputHandler_Main    Src/main.cpp
                                    Src/input_handler.cpp
                                    Src/keyboard_reader.cpp
                                    ../../4_CommonUtils/CANIO/Src/can_io.cpp
                                    ../../4_CommonUtils/CANIO/Src/socketcan_cpp.cpp)
target_link_libraries(InputHandler_Main X11 pthread) 