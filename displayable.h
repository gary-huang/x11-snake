#ifndef DISPLAYABLE_H_
#define DISPLAYABLE_H_

#include <X11/Xlib.h>
#include <X11/Xutil.h>

/*
 * Information to draw on the window.
 */
struct XInfo {
	Display	 *display;
	Pixmap	pixmap;
	int		 screen;
	Window	 window;
	GC		 gc[3];
	int		width;		// size of window
	int		height;
};

/*
 * An abstract class representing displayable things. 
 */
class Displayable {
	public:
		virtual void paint(XInfo &xinfo) = 0;
		virtual void unPaint(XInfo &xinfo) = 0;
}; 

#endif