/*
CS 349 A1 Skeleton Code - Snake

- - - - - - - - - - - - - - - - - - - - - -

Commands to compile and run:

    g++ -o snake snake.cpp -L/usr/X11R6/lib -lX11 -lstdc++
    ./snake

Note: the -L option and -lstdc++ may not be needed on some machines.
*/

#include <iostream>
#include <list>
#include <cstdlib>
#include <sys/time.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <sstream>
#include <string>
/*
 * Header files for X functions
 */
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "displayable.h"
#include "fruit.h"
#include "snake.h"
#include "splash.h"
#include "score.h"
using namespace std;
 
/*
 * Global game state variables
 */
const int Border = 1;
const int BufferSize = 10;
const int width = 800;
const int height = 600;
const int DEFAULT_FPS = 30;
const int DEFAULT_SNAKE_SPEED = 5;
const int SLEEP_NUMERATOR_US = 1000000;

const int splashTextWidth = 8;
const int splashTextHeight = 25;

const string TITLE("Snake v1.0");
const string AUTHOR_NAME("QiYang Huang");
const string USER_ID("Q43HUANG");
const string GAME_DESC[] = {
	"Use the arrow keys to control your snake ;)",
	"Don't run into obstacles such as walls or some shit"
};
const string GAME_CONTROLS[] = {
	"Press ENTER anytime to begin a new game",
	"Press q anytime to quit the game"
};
const string SPLASH_SCREEN_TEXT[] = {
	TITLE,
	AUTHOR_NAME,
	USER_ID,
	GAME_DESC[0],
	GAME_DESC[1],
	GAME_CONTROLS[0],
	GAME_CONTROLS[1]
};
const string PAUSE_TEXT = "Game Paused, Press ESCAPE to continue, ENTER to restart.";
const int SPLASH_SCREEN_TEXT_ROWS = 7;
int FPS = DEFAULT_FPS;
int speed = DEFAULT_SNAKE_SPEED;
SplashText *sp[SPLASH_SCREEN_TEXT_ROWS];
/*
 * Function to put out a message on error exits.
 */
void error( string str ) {
  cerr << str << endl;
  exit(0);
}


list<Displayable *> dList;           // list of Displayables
Score *score = new Score(width / 2, height - 40, "Score: 0");
Fruit *fruit = new Fruit(width, height);
Snake *snake = new Snake(0, 450, fruit, score);
SplashText pauseText((width - (8 * PAUSE_TEXT.length())) / 2, height / 2, PAUSE_TEXT);

/*
 * Initialize X and create a window
 */
void initX(int argc, char *argv[], XInfo &xInfo) {
	XSizeHints hints;
	unsigned long white, black;

   /*
	* Display opening uses the DISPLAY	environment variable.
	* It can go wrong if DISPLAY isn't set, or you don't have permission.
	*/	
	xInfo.display = XOpenDisplay( "" );
	if ( !xInfo.display )	{
		error( "Can't open display." );
	}
	
   /*
	* Find out some things about the display you're using.
	*/
	xInfo.screen = DefaultScreen( xInfo.display );

	white = XWhitePixel( xInfo.display, xInfo.screen );
	black = XBlackPixel( xInfo.display, xInfo.screen );

	hints.x = 100;
	hints.y = 100;
	hints.width = 800;
	hints.height = 600;
	hints.flags = PPosition | PSize;

	xInfo.window = XCreateSimpleWindow( 
		xInfo.display,				// display where window appears
		DefaultRootWindow( xInfo.display ), // window's parent in window tree
		hints.x, hints.y,			// upper left corner location
		hints.width, hints.height,	// size of the window
		Border,						// width of window's border
		black,						// window border colour
		white );					// window background colour
		
	XSetStandardProperties(
		xInfo.display,		// display containing the window
		xInfo.window,		// window whose properties are set
		TITLE.c_str(),		// window's title
		"Snake",			// icon's title
		None,				// pixmap for the icon
		argv, argc,			// applications command line args
		&hints );			// size hints for the window

	/* 
	 * Create Graphics Contexts
	 */
	//for snake
	int i = 0;
	xInfo.gc[i] = XCreateGC(xInfo.display, xInfo.window, 0, 0);
	XSetForeground(xInfo.display, xInfo.gc[i], WhitePixel(xInfo.display, xInfo.screen));
	XSetBackground(xInfo.display, xInfo.gc[i], BlackPixel(xInfo.display, xInfo.screen));
	XSetFillStyle(xInfo.display, xInfo.gc[i], FillSolid);
	XSetLineAttributes(xInfo.display, xInfo.gc[i],
	                     1, LineSolid, CapButt, JoinRound);
	i = 1;
	xInfo.gc[i] = XCreateGC(xInfo.display, xInfo.window, 0, 0);
	XSetForeground(xInfo.display, xInfo.gc[i], BlackPixel(xInfo.display, xInfo.screen));
	XSetBackground(xInfo.display, xInfo.gc[i], WhitePixel(xInfo.display, xInfo.screen));
	XSetFillStyle(xInfo.display, xInfo.gc[i], FillSolid);
	XSetLineAttributes(xInfo.display, xInfo.gc[i],
	                     1, LineSolid, CapButt, JoinRound);

	XSelectInput(xInfo.display, xInfo.window, 
		ButtonPressMask | KeyPressMask | 
		PointerMotionMask | 
		EnterWindowMask | LeaveWindowMask |
		StructureNotifyMask);  // for resize events
	
	//XWindowAttributes windowInfo;
	//XGetWindowAttributes(xInfo.display, xInfo.window, &windowInfo);
	int depth = DefaultDepth(xInfo.display, DefaultScreen(xInfo.display));
	xInfo.pixmap = XCreatePixmap(xInfo.display, xInfo.window, width, height, depth);
	XSetWindowBackgroundPixmap(xInfo.display, xInfo.window, None);
	/*
	 * Put the window on the screen.
	 */
	XCopyArea(xInfo.display, xInfo.pixmap, xInfo.window, xInfo.gc[1], 0, 0, width, height, 0, 0);
	XMapRaised( xInfo.display, xInfo.window );
	XFlush(xInfo.display);
}

void unPaintAll(XInfo &xInfo) {
	list<Displayable *>::const_iterator begin = dList.begin();
	list<Displayable *>::const_iterator end = dList.end();

	while( begin != end ) {
		Displayable *d = *begin;
		//if (d != NULL) {
			d->unPaint(xInfo);
		//}
		begin++;			
	}
	dList.clear();
}

/*
 * Function to repaint a display list
 */
void repaint( XInfo &xInfo) {
	list<Displayable *>::const_iterator begin = dList.begin();
	list<Displayable *>::const_iterator end = dList.end();

	while( begin != end ) {
		Displayable *d = *begin;
		//if (d != NULL) {
			d->paint(xInfo);
		//}
		begin++;			
	}

	XCopyArea(xInfo.display, xInfo.pixmap, xInfo.window, xInfo.gc[1], 0, 0, width, height, 0, 0);
	//XFreePixmap(xInfo.display, xInfo.pixmap);
	XFlush( xInfo.display );
}

bool handleKeyPress(XInfo &xInfo, XEvent &event, bool &isInEventLoop, bool &isInPause, bool &hasLost) {
	KeySym key;
	char text[BufferSize];
	
	/*
	 * Exit when 'q' is typed.
	 * This is a simplified approach that does NOT use localization.
	 */
	int i = XLookupString( 
		(XKeyEvent *)&event, 	// the keyboard event
		text, 					// buffer when text will be written
		BufferSize, 			// size of the text buffer
		&key, 					// workstation-independent key symbol
		NULL );					// pointer to a composeStatus structure (unused)
	//if ( i == 1) {
		//printf("Got key press -- %c\n", text[0]);
		if (text[0] == 'q') {
			error("Terminating normally.");
		}
		if (text[0] == 'n') {
			hasLost = false;
			isInPause = false;
			isInEventLoop = false;
			unPaintAll(xInfo);
			cout << "Returning to main menu" << endl;
			for (int k = 0; k < SPLASH_SCREEN_TEXT_ROWS; ++k) {
				dList.push_back(sp[k]);
				
			}	
			repaint(xInfo);
		}
		if ((key == XK_Return)) {
//newGame(xInfo, isInGame);
			isInPause = false;
			hasLost = false;
			return true;
		}
		if ((key == XK_Escape) && (isInEventLoop)) {
			if (isInPause) {
				dList.remove(&pauseText);
				pauseText.unPaint(xInfo);
				isInPause = !isInPause;
				repaint(xInfo);
			} else {
				dList.push_front(&pauseText);
				isInPause = !isInPause;	
				repaint(xInfo);
			}
		}
		
		if ((key == XK_Left) && (isInEventLoop)) {
			snake->turnLeft();
		}
		if ((key == XK_Right) && (isInEventLoop)) {
			snake->turnRight();
		}
	//}
	return false;
}

void handleAnimation(XInfo &xInfo, bool &hasLost) {
    /*
     * ADD YOUR OWN LOGIC
     * This method handles animation for different objects on the screen and readies the next frame before the screen is re-painted.
     */ 
	if (snake->move(xInfo)) {
		repaint(xInfo);
	} else {
		hasLost = true;
	}
}

// get microseconds
unsigned long now() {
	timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000 + tv.tv_usec;
}

void newGame(XInfo &xInfo, bool &isInGame) {
	cout << "Starting game." << endl;
	unPaintAll(xInfo);
	free(snake);
	free(fruit);
	free(score);
	score = new Score(width / 2, height - 40, "Score: 0");
	fruit = new Fruit(width, height);
	snake = new Snake(0, 450, fruit, score);
	snake->setSpeed(speed);
	dList.push_front(snake);
	dList.push_front(fruit);
	dList.push_front(score);
	isInGame = true;
}

void eventLoop(XInfo &xInfo) {
	// Add stuff to paint to the display list

	string gameOverText = "Game Over. Press n to return to main screen, ENTER for a new game, or q to quit.";
	SplashText gameOver((width - (splashTextWidth * gameOverText.length())) / 2, height / 2, gameOverText);
	
	for (int k = 0; k < SPLASH_SCREEN_TEXT_ROWS; ++k) {
		string str = SPLASH_SCREEN_TEXT[k];
		sp[k] = new SplashText((width - (splashTextWidth * SPLASH_SCREEN_TEXT[k].length())) / 2, (height / 2 - (splashTextHeight * SPLASH_SCREEN_TEXT_ROWS)) + (k * splashTextHeight), str);
		dList.push_back(sp[k]);
		repaint(xInfo);
	}	

	bool isInGame = false;
	bool isPaused = false;
	bool hasLost = false;
	XEvent event;
	unsigned long lastRepaint = 0;
	int inside = 0;
	repaint(xInfo);
	while( true ) {
		/*
		 * This is NOT a performant event loop!  
		 * It needs help!
		 */
		if ((!isInGame) && (!isPaused) && (!hasLost)) {
	for (int k = 0; k < SPLASH_SCREEN_TEXT_ROWS; ++k) {
		string str = SPLASH_SCREEN_TEXT[k];
		dList.push_back(sp[k]);
		repaint(xInfo);
	}	
		}


		while (XPending(xInfo.display) > 0) {
			XNextEvent( xInfo.display, &event );
			//cout << "event.type=" << event.type << "\n";
			switch( event.type ) {
				case KeyPress:
					if (handleKeyPress(xInfo, event, isInGame, isPaused, hasLost)) {
						newGame(xInfo, isInGame);
					}
					break;
				case EnterNotify:
					inside = 1;
					break;
				case LeaveNotify:
					inside = 0;
					break;
			}
		} 

		usleep(SLEEP_NUMERATOR_US/FPS);
		if (!isPaused && isInGame) {
			handleAnimation(xInfo, hasLost);	
		}

		if (hasLost) {
			unPaintAll(xInfo);
			
			isInGame = false;
			
			dList.push_back(&gameOver);
			dList.push_back(score);
			repaint(xInfo);
			//cout << "GAME OVER" << endl;
		}
		
	}

		for (int k = 0; k < SPLASH_SCREEN_TEXT_ROWS; ++k) {
			free(sp[k]);
		}	
		free(snake);
		free(fruit);
		free(score);

}



/*
 * Start executing here.
 *	 First initialize window.
 *	 Next loop responding to events.
 *	 Exit forcing window manager to clean up - cheesy, but easy.
 */
int main ( int argc, char *argv[] ) {
	XInfo xInfo;

	
	switch (argc) {
		case 3:
		{
			stringstream ss(argv[1]);
			ss >> FPS;
			ss.clear();
			ss.str(argv[2]);
			ss >> speed;
			if (speed < 1 || speed > 10) error("Speed argument must be in the range of 1-10.");
			if (FPS < 1 || FPS > 100) error("FPS argument must be in the range of 1-100.");
			break;
		}
		default:
		{
			error("There needs to be a framerate argument as well as a speed argument supplied.");
			break;
		}
			
	}
	snake->setSpeed(speed);
	cout << "Speed is: " << snake->getSpeed() << endl;
	cout << "FPS is: " << FPS << endl;

	initX(argc, argv, xInfo);

	
	//splashScreen(xInfo);
	eventLoop(xInfo);
	XCloseDisplay(xInfo.display);
}
