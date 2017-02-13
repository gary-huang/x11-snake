#ifndef SPLASH_H_
#define SPLASH_H_

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <string>

#include "displayable.h"

using namespace std;

class SplashText : public Displayable {
	public:
		virtual void paint(XInfo &xinfo);
        virtual void unPaint(XInfo &xinfo);

        SplashText(int x, int y, string text);

        // ** ADD YOUR LOGIC **
        /*
         * The fruit needs to be re-generated at new location every time a snake eats it. See the assignment webpage for more details.
         */
        ~SplashText();

    protected:
        int x;
        int y;
        string text;
};

#endif