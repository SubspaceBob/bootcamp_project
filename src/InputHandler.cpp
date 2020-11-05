#include "InputHandler.h"

int main() {
    
    // send greetings to user :)
    std::cout << "Hello there!" << std::endl;

    // create CANWriter object
    // CANWriter.start()
    
    // create and start KeyboardReader
    KeyboardReader reader;
    reader.start();

    // while
    while (key != 0x09)
    { 

    //      KeyInput = KeyboardReader.getKey()
    //      Data = UpdateCANData(KeyInput)
    //      CANWriter.SendCANData(AccPdl=100, BrkPdl=0, GearReq=..., StartButton=..)
    //      check if KeyInput is termination
    //           terminate()
    //           break;
    //
    // KeyboardReader.stop();
    // delete KeyboardReader;
    // CANWriter.stop();
    // delete CANWriter;
    // return 0;
    }     
}