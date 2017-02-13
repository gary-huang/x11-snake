SNAKE

DEVELOPEMENT ENVIRONMENT:
This game was developed on the UW student Linux environment, as well as the Ubuntu 16.04LTS
OS. The game was compiled using g++ 4.9.4 on Ubuntu 14.04.1. The game was tested over
ssh as well as locally on UBuntu 16.04LTS. 

GAME OVERALL DESIGN:
The game board/canvas is considered to be main.cpp. Where the main event loop as well as
event handling are implemented. The snake is implemented in snake.cpp with a list of 
snake blocks as its body to mimick turning as best as possible. Fruits are generated at
250, 250 when the game starts as a freebie for the player, and will be generated in the game 
with a 200 pixel margin. Every fruit eaten is 15 points. The game texts and scores are 
implemented as a special type of displayable, and score is a derived class of SplashText.

GAME DESCRIPTION:
The objective of this game is to control your snake into eating the randomly generated fruits
, which are white blocks that randomly generate throughout the map, while avoiding obstacles like the edges of the screen, and avoiding colliding into your body.


GAME CONTROLS:
LEFT: Turn the snake left with respect to the direction that the snake is going.
RIGHT: Turn the snake right with respect to the direction that the snake is going.
q: Quit the game at any time.
ENTER: Start/restart the game.
n: Return to main menu/splash screen.
