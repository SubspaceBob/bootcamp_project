#ifndef KEYBOARDREADER_H
#define KEYBOARDREADER_H
#include <iostream>
#include <cmath>
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

using KeyInput = std::pair<int, int>;


class KeyboardReader{
public:
    KeyboardReader() = default;
    ~KeyboardReader(){};
    Display *display;
    Window window;
    XEvent event;
    int s;
    KeyInput getKey();
    void start();
    void stop();
};

#endif // KEYBOARDREADER_H