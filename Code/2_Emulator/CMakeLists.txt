cmake_minimum_required(VERSION 3.10)
project(TeamA)
set(CMAKE_CXX_STANDARD 17)

include_directories(Include)
include_directories(../4_CommonUtils/CANIO/Include)

# Create executable for EmulatorMain
add_executable(EmulatorMain Src/emulator_main.cpp
                            Src/gearbox.cpp
                            Src/engine.cpp
                            ../../4_CommonUtils/CANIO/Src/can_io.cpp
                            ../../4_CommonUtils/CANIO/Src/socketcan_cpp.cpp)
target_link_libraries(EmulatorMain pthread) 