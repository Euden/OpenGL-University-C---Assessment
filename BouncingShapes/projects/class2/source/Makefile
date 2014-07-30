CFLAGS = -Wall -pedantic -pedantic-errors -g
LIBS = -lGL -lGLU -lXrandr -lXi
ROOTDIR = ../../../
STATICLIBS = $(ROOTDIR)GLFrame/libGLFrame.a $(ROOTDIR)glfw/src/libglfw3.a
CC = g++
STANDARD = -std=c++0x
INCLUDEDIR = -I $(ROOTDIR)
PROJNAME = Cube
BINNAME = $(PROJNAME)Bin

all: $(PROJNAME)

ControlHandler.o: ControlHandler.cpp
	$(CC) $(CFLAGS) $(STANDARD) $(INCLUDEDIR) -c ControlHandler.cpp

$(PROJNAME): main.cpp
	$(CC) $(CFLAGS) $(STANDARD) $(INCLUDEDIR) -o $(BINNAME) main.cpp ControlHandler.o $(STATICLIBS) $(LIBS)

clean:
	rm -f *.o $(BINNAME)
