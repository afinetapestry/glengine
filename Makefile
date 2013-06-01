CC=g++
CXX=g++
LD=g++
CFLAGS=-g -c $(shell sdl2-config --cflags) -I/opt/local/include
LDFLAGS=$(shell sdl2-config --libs) -L/opt/local/lib -lGLEW -framework OpenGL
SRC_C=glerror.c
SRC_CXX=main.cpp
OBJECTS=$(SRC_C:.c=.o) $(SRC_CXX:.cpp=.o)
EXECUTABLE=gl3

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(LD) $(OBJECTS) $(LDFLAGS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

.cpp.o:
	$(CXX) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

.PHONY: clean

