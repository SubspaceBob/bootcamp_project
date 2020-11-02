#include "InputHandler.h"
#include "socketcan_cpp.h"
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

// https://github.com/siposcsaba89/socketcan-cpp


void send_can(scpp::SocketCan *socket_can, int data){ 
    scpp::CanFrame cf_to_write;
            
    cf_to_write.id = 123;
    cf_to_write.len = 8;
    for (int i = 0; i < 7; ++i)
        cf_to_write.data[i] = std::rand() % 256;
    std::cout << data << std::endl;
    cf_to_write.data[8] = data;
    auto write_sc_status = socket_can->write(cf_to_write);
    if (write_sc_status != scpp::STATUS_OK)
        printf("something went wrong on socket write, error code : %d \n", int32_t(write_sc_status));
            
}



int main() {
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
    delete sockat_can;
    return 0;
}