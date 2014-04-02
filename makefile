CFLAGS = -c -lSDL -lSDL_image

all: a.out

a.out: main.o cell.o graphic.o maze.o resource.o
	g++  main.o cell.o graphic.o maze.o resource.o -lSDL -lSDL_image -o a.out

main.o: main.cpp maze.h
	g++ $(CFLAGS) main.cpp

maze.o: maze.cpp resource.h graphic.h
	g++ $(CFLAGS) maze.cpp

graphic.o: graphic.h
	g++ $(CFLAGS) graphic.cpp

resource.o: resource.h
	g++ $(CFLAGS) resource.cpp

clean:
	rm -rf *o a.out
