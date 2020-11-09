#include <iostream>
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "KeyboardReader.h" 
#include "InputHandler.h"
#include <X11/keysym.h>

// Function to create a keyboard event
XKeyEvent createKeyEvent(Display *display, Window &win,
                         Window &winRoot, bool press,
                         int keycode, int modifiers)
{
	XKeyEvent event;

	event.display     = display;
	event.window      = win;
	event.root        = winRoot;
	event.subwindow   = None;
	event.time        = CurrentTime;
	event.x           = 1;
	event.y           = 1;
	event.x_root      = 1;
	event.y_root      = 1;
	event.same_screen = True;
	event.keycode     = XKeysymToKeycode(display, keycode);
	event.state       = modifiers;
	if(press)
		event.type = KeyPress;
	else
		event.type = KeyRelease;

	return event;
}

int random_key_press(){
    // random keypress between 0-9, some normal signs and A-Z
    srand( (unsigned)time(NULL));
    int rand_num = rand() % (0x5a-0x30) + 0x30;
    return rand_num;
} 

int main(){
    std::cout << "Hello there!" << std::endl;
    KeyboardReader reader;// = KeyboardReader();
    std::cout << "starting!" << std::endl;
    reader.start();
    Window winRoot = XDefaultRootWindow(reader.display);
    Display *d = reader.display;
    KeyInput key;
    // TODO: define proper QUIT and NoInput values
    while (key.first != 0x09)
    { 
        // for random inputs 
        /*auto random_key = random_key_press();
        XKeyEvent event = createKeyEvent(reader.display,
                                        reader.window,
                                        winRoot,
                                        true,                   // press
                                        random_key,
                                        0);
        
        XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);
        key = reader.getKey(); 

        event = createKeyEvent(reader.display,
                                        reader.window,
                                        winRoot,
                                        false,                  // release
                                        random_key,
                                        0);
        
        XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);
        */

        key = reader.getKey();
        std::cout << key.first << " " << key.second << std::endl; 
        // do something with value
    } 
    reader.stop();
    std::cout << "Goodbye!" << std::endl;
    return 0;
} 