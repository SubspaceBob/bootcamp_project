#include <iostream>
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "KeyboardReader.h" 


void KeyboardReader::start(){  
    /* open connection with the server */
    display = XOpenDisplay(NULL);
    if (display == NULL)
    {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }
    s = DefaultScreen(display);

    /* create window */
    window = XCreateSimpleWindow(display, RootWindow(display, s), 1, 200, 100, 200, 1,
                        BlackPixel(display, s), WhitePixel(display, s));

    /* select kind of events we are interested in */
    XSelectInput(display, window, KeyPressMask | KeyReleaseMask );

    //tried to get a textbox with instructions in the window, still fails
    Window w = XCreateSimpleWindow(display, window, 0, 0, 256, 256, 0, 0, 0xffffff);
    GC gc = DefaultGC(display, 0);
    XMapRaised(display, window);
    //XSelectInput(display, w, ExposureMask);
    const char *msg = "Enter = startbutton\nP = Park\nR = Reverse\nN = Neutral\nD = Drive"; 
    //XNextEvent(display, &event);
    XDrawString(display, window, gc, 16, 16, msg, (int) strlen(msg));
    
    /* map (show) the window */
    XMapWindow(display, window);
    XAutoRepeatOff(display);
}

int KeyboardReader::getKey()
{  
    //std::cout << "Getting key!" << std::endl;
    XNextEvent(display, &event);
    /* keyboard events */
    if (event.type == KeyPress)
    {
        printf( "KeyPress: %x\n", event.xkey.keycode );
        return event.xkey.keycode;
    }
}

void KeyboardReader::stop(){ 
    std::cout << "stopping!" << std::endl;
    XAutoRepeatOn(display);
    /* close connection to server */
    XCloseDisplay(display);
    std::cout << "stopped!" << std::endl;
}
