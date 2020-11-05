#include <iostream>
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

class KeyboardReader{
public:
    KeyboardReader() = default;
    ~KeyboardReader(){};
    Display *display;
    Window window;
    XEvent event;
    int s;
    
    
    void start(){  
        /* open connection with the server */
        display = XOpenDisplay(NULL);
        if (display == NULL)
        {
            fprintf(stderr, "Cannot open display\n");
            exit(1);
        }
        s = DefaultScreen(display);
    
        /* create window */
        window = XCreateSimpleWindow(display, RootWindow(display, s), 1, 200, 100, 2, 1,
                            BlackPixel(display, s), WhitePixel(display, s));
    
        /* select kind of events we are interested in */
        XSelectInput(display, window, KeyPressMask | KeyReleaseMask );
    
        /* map (show) the window */
        XMapWindow(display, window);
        XAutoRepeatOff(display);
    }

    int getKey()
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

    void stop(){ 
        std::cout << "stopping!" << std::endl;
        XAutoRepeatOn(display);
        /* close connection to server */
        XCloseDisplay(display);
        std::cout << "stopped!" << std::endl;
    }
};

int main(){
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
    return 0;
} 