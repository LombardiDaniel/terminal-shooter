CPPFLAGS=-std=c++11

TermShooter.exe: main.o engine.o
	g++ $(CPPFLAGS) main.o engine.o -o TermShooter.exe

main.o: src/main.cpp
	g++ $(CPPFLAGS) -c src/main.cpp

engine.o: src/engine.cpp src/headers/engine.h
	g++ $(CPPFLAGS) -c src/engine.cpp

# This makefile is make for the `mingw32-make`, NOT for gnu-make
# oth: g++ main.cpp engine.cpp -o .\..\TermShooter.exe
