#include <iostream>
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "KeyboardReader.h" 
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
        
        /*
        XKeyEvent event = createKeyEvent(reader.display,
                                        reader.window,
                                        XDefaultRootWindow(reader.display),
                                        true,
                                        XK_Up,
                                        0)
        
        XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);

        event = createKeyEvent(reader.display,
                                        reader.window,
                                        XDefaultRootWindow(reader.display),
                                        false,
                                        XK_Up,
                                        0)
        
        XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);
        */
    reader.stop();
    std::cout << "Goodbye!" << std::endl;
    return 0;
} 