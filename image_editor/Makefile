CC=g++
CFLAGS=-c -g -pthread
SOURCES=main.cpp image_editor.cpp drawing_window.cpp pixel.cpp
OBJECTS=$(SOURCES:.cpp=.o)
LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lpthread
LDFLAGS=-pthread 
PROGRAM=image_editor

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) -o $(PROGRAM) $(OBJECTS) $(LDFLAGS) $(LIBS) 

.cpp.o: 
	$(CC) $(CFLAGS) $<

depend: .depend

.depend: $(SOURCES)
	rm -f .depend
	$(CC) $(CFLAGS) -MM $^ >> .depend;

include .depend

clean:
	rm -f .depend $(PROGRAM) $(OBJECTS)

