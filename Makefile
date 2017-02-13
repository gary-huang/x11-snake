# super simple makefile
# call it using 'make NAME=name_of_code_file_without_extension'
# (assumes a .cpp extension)
NAME = snake

#
# Add $(MAC_OPT) to the compile line for Mac OSX.
MAC_OPT = "-I/opt/X11/include"

all:
	@echo "Compiling..."
	g++ -c -o fruit.o fruit.cpp
	g++ -c -o snake.o snake.cpp
	g++ -c -o snakeblock.o snakeblock.cpp
	g++ -c -o splash.o splash.cpp
	g++ -c -o main.o main.cpp
	g++ -c -o score.o score.cpp
	g++ -o $(NAME) $(NAME).o snakeblock.o fruit.o splash.o main.o score.o -L/usr/X11R6/lib -lX11 -lstdc++ $(MAC_OPT)

run: all
	@echo "Running..."
	./$(NAME) 30 5

clean:
	-rm animation clipping doublebuffer drawing drawing.min 
	-rm eventloop eventloop.min hello.min null null.min openwindow openwindow.min
	-rm *.o
	-rm $(NAME)
	-rm *.out
