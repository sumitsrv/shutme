all: main

clean:
	rm -rf *.o

main: main.o webcam.o handdetector.o face.o contrast.o
	g++ -Wall -ansi -o shutme main.o webcam.o handdetector.o face.o contrast.o `pkg-config --cflags --libs opencv` 

main.o: main.c
	g++ -Wall -ansi -c main.c `pkg-config --cflags --libs opencv` 
	
webcam.o: webcam.c
	g++ -Wall -ansi -c webcam.c `pkg-config --cflags --libs opencv` 
	
handdetector.o: handdetector.c
	g++ -Wall -ansi -c handdetector.c `pkg-config --cflags --libs opencv` 

face.o: face.c
	g++ -Wall -ansi -c face.c `pkg-config --cflags --libs opencv` 

contrast.o: contrast.c
	g++ -Wall -ansi -c contrast.c `pkg-config --cflags --libs opencv`
