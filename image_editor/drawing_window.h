#ifndef _DRAWINGWINDOW_H
#define _DRAWINGWINDOW_H

/*
	drawing_window.h
	
	Class definition for the drawing_window class.

	author: C. Painter-Wakefield

	last modified: 1/15/2018
*/

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include <string>
#include <thread>
#include <mutex>

using namespace std;
using namespace sf;

/******************************************************************************

    class drawing_window

    The drawing_window class provides a simple 2-D drawing interface on
    top of SFML.  A drawing_window is initialized with set dimensions, which
    cannot be changed; the user can draw points of any color (RGB) or
    grayscale level at any coordinate within the original dimensions.

    The main differences between using this class and using raw SFML are:
      - The drawing_window does not require an event-driven approach.  You 
        simply open the window and tell it what to draw, when you want to
        draw it.  Your main() function lives in a different thread than the
        graphics window, so you can continue to interact with the user and
        not have to worry about event loops and callbacks.

      - The drawing_window object remembers what you've previously drawn; you 
        don't have to continuously refresh in a loop (that is done for you).

      - Points are drawn using VertexArrays rather than RectangleShapes; you
        of course can do this with raw SFML, but it is extra work.  The
        drawing_window object does this for you.  The advantage is *much*
        smoother performance.  The drawing_window uses two triangles to draw
        each point, just like a RectangleShape, so resizing of the window
        works - it just rescales to larger "pixels".

    Basic usage:
        // create and open the window
        drawing_window win(width, height, "My Window");
        win.open();

        // draw points on the window
        win.set_color(x, y, r, g, b); 
        win.set_gray(x2, y2, graylevel);

        // Either let the user click the close button on the window
        while (win.is_open()) { };

        // Or manage closing it yourself (user can still close the window)
        win.close();

    Known issues
      - This has been tested on linux only.  It might not port to other
        platforms correctly.

      - Multiple windows seem to work on some graphics cards, but not others.
        Avoid using multiple windows.  Probably something I did wrong :(
        Also, opening and closing windows / resizing only works a few times
        before crashing with an OpenGL error.

******************************************************************************/

class drawing_window {
public:
    // constructors, destructor
    drawing_window() { _width = 0; _height = 0; _title = "Drawing Window"; }
    drawing_window(unsigned w, unsigned h, string t = "Drawing Window") {
        initialize(w, h, t);
    }
    ~drawing_window() { _destroy(); }

    // initialize window
    void initialize(unsigned w, unsigned h, string t = "Drawing Window") {
        _width = w; _height = h; _title = t; _setup();
    }

    // open/close the window
    void open();
    void close();

    // resize window
    void resize(unsigned width, unsigned height);

    // test for window open
    bool is_open() { return _window != NULL && _window->isOpen(); }

    // get current width and height
    unsigned get_width()  { return _width; }
    unsigned get_height() { return _height; }

    // draw a point
    void set_color(unsigned x, unsigned y, char r, char g, char b);
    void set_gray(unsigned x, unsigned y, char grayval) {
        set_color(x, y, grayval, grayval, grayval);
    }

private:
    // bigger powers of 2 than 16 don't seem to work on some graphics
    // cards.
    static const unsigned PATCH_SIZE = 16;

    // the function that will handle the event loop; must be static
    // to allow running it in a new thread.  Unfortunately, that means
    // we have to pass this object into the static function!
    static void _draw(drawing_window *);

    // the patch struct lets us tile the window with VertexArrays, and
    // only update when needed.
    struct patch {
        void draw(RenderWindow& target) { 
            update();
            target.draw(points);
        }

        void set_point(unsigned x, unsigned y, char r, char g, char b) {
            // prevent vertex array updates while changing the patch
            mtx.lock();
            data[x][y][0] = r;
            data[x][y][1] = g;
            data[x][y][2] = b;
            dirty = true;
            mtx.unlock();
        }
        void update();

        VertexArray points;
        unsigned    x_off = 0, y_off = 0;
        unsigned    width = 0, height = 0;
        bool        dirty = true;
        char        data[PATCH_SIZE][PATCH_SIZE][3];
        mutex       mtx;
    };

    unsigned      _width, _height;
    string        _title;
    RenderWindow *_window = NULL;
    unsigned      _patch_count;
    patch*        _patches = NULL;
    mutex         _draw_mtx;

    void _setup();
    void _destroy();
};

#endif
