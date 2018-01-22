# Makefile

CPPFLAGS = -Wall -pedantic -std=c++17

all: animal

animal: animal.cpp
	g++ $(CPPFLAGS) animal.cpp -o animal

clean:
	rm animal
