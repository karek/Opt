CPP11 = -std=c++11
FLAGSRELEASE = -O2 -Wall -DDEBUG
CC = g++


all: a.o

%.o: %.cpp
	$(CC) $(CPP11) $(FLAGSRELEASE) $< -o $@

clean:
	rm -f *~ *.o

.PHONY: all clean
