#include <gtest/gtest.h>
#include <iostream>
#include "keyboard_reader.h"

TEST(KeyReaderTests, NormalUsecase)
{
    // just a temp copy of the main method from cpp-file

    std::cout << "Hello there!" << std::endl;
    KeyboardReader reader;// = KeyboardReader();
    std::cout << "starting!" << std::endl;
    reader.start();
    
    int key;
    // TODO: define proper QUIT and NoInput values
    while (key != 0x09)
        key = reader.getKey(); 
        // do something with value

    reader.stop();
    std::cout << "Goodbye!" << std::endl;
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}