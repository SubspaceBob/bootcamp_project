#ifndef KEYBOARDREADER_H
#define KEYBOARDREADER_H
#include<iostream>
#include<cmath>
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

// void 
class KeyboardReader{
public:
    KeyboardReader() = default;
    ~KeyboardReader(){};
    Display *display;
    Window window;
    XEvent event;
    int s;
    int getKey();
    void start();
    void stop();

};

#endif // KEYBOARDREADER_H