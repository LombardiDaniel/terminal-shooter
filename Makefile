CPPFLAGS=-std=c++11

TermShooter.exe: main.o engine.o player.o map.o
	g++ $(CPPFLAGS) main.o engine.o player.o map.o -o TermShooter.exe

main.o: src/main.cpp
	g++ $(CPPFLAGS) -c src/main.cpp

engine.o: src/engine.cpp src/headers/engine.h
	g++ $(CPPFLAGS) -c src/engine.cpp

player.o: src/player.cpp
	g++ $(CPPFLAGS) -c src/player.cpp

map.o: src/map.cpp
	g++ $(CPPFLAGS) -c src/map.cpp

clean:
	rm *.o
# This makefile is make for the `mingw32-make`, NOT for gnu-make
# oth: g++ main.cpp engine.cpp -o .\..\TermShooter.exe
