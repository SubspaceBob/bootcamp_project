#include "InputHandler.h"

int main() {

    // send greetings to user :)
    //
    // create CANWriter object
    // CANWriter.start()
    //
    // create KeyboardReader
    // KeyboardReader.start()
    //
    // while
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
         

    std::cout << "Hello world" << std::endl;
    scpp::SocketCan *sockat_can = new scpp::SocketCan;
    if (sockat_can->open("vcan0") != scpp::STATUS_OK) {
        std::cout << "Cannot open vcan0." << std::endl;
        std::cout << "Check whether the vcan0 interface is up!" << std::endl;
        exit (-1);
    }
    Display *display;
    Window window;
    XEvent event;
    int s;
 
    /* open connection with the server */
    display = XOpenDisplay(NULL);
    if (display == NULL)
    {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }
 
    s = DefaultScreen(display);
 
    /* create window */
    window = XCreateSimpleWindow(display, RootWindow(display, s), 1, 1, 2, 2, 1,
                           BlackPixel(display, s), WhitePixel(display, s));
 
    /* select kind of events we are interested in */
    XSelectInput(display, window, KeyPressMask | KeyReleaseMask );
 
    /* map (show) the window */
    XMapWindow(display, window);
 
    /* event loop */
    while (1)
    {
        XNextEvent(display, &event);
 
        /* keyboard events */
        if (event.type == KeyPress)
        {
            printf( "KeyPress: %x\n", event.xkey.keycode );

            /* exit on ESC key press */
            if ( event.xkey.keycode == 0x09 )
                break;
            if ( event.xkey.keycode == 0x68 ) // page down button
                printf( "KeyRelease: %x\n", event.xkey.keycode );
                send_can(sockat_can, event.xkey.keycode);
        }

        else if (event.type == KeyRelease)
        {
            if ( event.xkey.keycode == 0x68 ) // page down button
            { 
                printf( "KeyRelease: %x\n", event.xkey.keycode );
                send_can(sockat_can, event.xkey.keycode);
            } 
        }
    }

    /* close connection to server */
    XCloseDisplay(display);
    return 0;
}