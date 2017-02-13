#ifndef FRUIT_H_
#define FRUIT_H_

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "displayable.h"
#include <iostream>

class Fruit : public Displayable {
	public:
		virtual void paint(XInfo &xinfo);
        virtual void unPaint(XInfo &xinfo);
        
        Fruit(int maxX, int maxY);
        void regenerate(XInfo &xInfo);
        // ** ADD YOUR LOGIC **
        /*
         * The fruit needs to be re-generated at new location every time a snake eats it. See the assignment webpage for more details.
         */

        int x;
        int y;
        int maxX;
        int maxY;
};

#endif