CC = gcc
LDFLAGS =-std=c99 -w
CFLAGS =-c -std=c99 -w
SOURCES = main.o complex.o functions.o
EXECUTABLE = start

all: $(EXECUTABLE)


$(EXECUTABLE): $(SOURCES)
	$(CC) $(LDLAGS) $(SOURCES) -lm -o  $@


.c.o:
	$(CC) $(CFLAGS) $< -o $@


clean:
	-rm -f *.o start
