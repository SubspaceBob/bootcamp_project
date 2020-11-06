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

    /* tried to get a textbox with instructions in the window, still fails
    Window w = XCreateSimpleWindow(display, window, 0, 0, 256, 256, 0, 0, 0xffffff);
    GC gc = DefaultGC(display, 0);
    XMapRaised(display, w);
    XSelectInput(display, w, ExposureMask);
    const char *msg = "Enter = startbutton\nP = Park\nR = Reverse\nN = Neutral\nD = Drive"; 
    XNextEvent(display, &event);
    XDrawString(display, w, gc, 16, 16, msg, (int) strlen(msg));
    */
    /* map (show) the window */
    XMapWindow(display, window);
    XAutoRepeatOff(display);
}

KeyInput KeyboardReader::getKey()
{  
    KeyInput key;
    key.first = 0;
    key.second = 0;
    /* keyboard events */
    //if(1) 
    if(XCheckMaskEvent(display, KeyPressMask | KeyReleaseMask ,&event))
    {
        //XNextEvent(display, &event);
        if (event.type == KeyPress)
        {
            key.first = event.xkey.keycode;
            key.second = 1;
        }
        else if (event.type == KeyRelease)
        {
            key.first = event.xkey.keycode;
            key.second = 0;
        }
        
    } 
    return key; 
}

void KeyboardReader::stop(){ 
    std::cout << "stopping!" << std::endl;
    XAutoRepeatOn(display);
    /* close connection to server */
    XCloseDisplay(display);
    std::cout << "stopped!" << std::endl;
}
