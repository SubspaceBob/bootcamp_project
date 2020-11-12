cmake_minimum_required(VERSION 3.10)
project(TeamA)
set(CMAKE_CXX_STANDARD 17)

include_directories(Headerfiles)

# Test KeyboardReader
add_executable(Test_KeyReader   tests/Test_KeyboardReader.cpp
                                InputHandler/KeyboardReader.cpp)
target_link_libraries(Test_KeyReader X11)    

# Test GearboxClass
#add_executable(Test_Gearbox     tests/TestGearboxClass.cpp
                                #Gearbox/GearClass.cpp)    

# Shared Object of InputHandler with SendCAN-stuff
add_library(InputHandler SHARED InputHandler/KeyboardReader.cpp
                                InputHandler/InputHandler.cpp
                                SendCan/frameToBus.cpp
                                Includes/socketcan_cpp/socketcan_cpp.cpp)                          
target_link_libraries(InputHandler X11)

# Test of InputHandler
add_executable(Test_InputHandler    tests/Test_InputHandler.cpp
                                    InputHandler/KeyboardReader.cpp
                                    InputHandler/InputHandler)
target_link_libraries(Test_InputHandler PUBLIC X11 InputHandler)

# Create executable for InputHandlerMain
add_executable(InputHandler_Main   InputHandler/main.cpp
                                InputHandler/InputHandler.cpp
                                InputHandler/KeyboardReader.cpp
                                SendCan/frameToBus.cpp
                                Includes/socketcan_cpp/socketcan_cpp.cpp)
target_link_libraries(InputHandler_Main X11) 

# EmulatorMainThreads
add_executable(EmulatorMainThreads Emulator-main-threads.cpp
                                Gearbox/GearClass.cpp
                                Engine/Engine.cpp
                                ReadCan/canReader.cpp
                                Includes/socketcan_cpp/socketcan_cpp.cpp  
                                EmulatorFramePacker/FramePacker.cpp
                                SendCan/frameToBus.cpp)
find_package (Threads)
target_link_libraries(EmulatorMainThreads pthread)              
