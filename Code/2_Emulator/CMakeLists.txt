cmake_minimum_required(VERSION 3.10)
project(TeamA)
set(CMAKE_CXX_STANDARD 17)

include_directories(Include)
include_directories(../4_CommonUtils/CANIO/Include)
include_directories(../4_CommonUtils/SharedMemory/Include)

# Create executable for EmulatorMain
# maybe static libraries for the shared
add_executable(EmulatorMain Src/emulator_main.cpp
                            Src/gearbox.cpp
                            Src/engine.cpp
                            ../../4_CommonUtils/CANIO/Src/can_io.cpp
                            ../../4_CommonUtils/CANIO/Src/socketcan_cpp.cpp)
target_link_libraries(EmulatorMain pthread)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link RunEngineTests with what we want to test 
# and the GTest and pthread library
add_executable(EngineTest Test/engine_test.cpp)
target_link_libraries(EngineTest ${GTEST_LIBRARIES} pthread)

add_executable(GearboxTest Test/gearbox_test.cpp)
target_link_libraries(GearboxTest ${GTEST_LIBRARIES} pthread)

#add_executable(EmulatorMainTest Test/emulator_main_test.cpp)
#target_link_libraries(EmulatorMainTest ${GTEST_LIBRARIES} pthread)


