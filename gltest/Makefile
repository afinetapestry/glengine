CC=clang++
CFLAGS=-g -c $(shell sdl2-config --cflags) -I/opt/local/include
LDFLAGS=$(shell sdl2-config --libs) -L/opt/local/lib -lGLEW -framework OpenGL
SRC_C=
SRC_CXX=main.cpp
OBJECTS=$(SRC_C:.c=.o) $(SRC_CXX:.cpp=.o)
EXECUTABLE=gltest

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

.PHONY: clean

