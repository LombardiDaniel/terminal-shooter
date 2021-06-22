# This makefile is made for the `mingw32-make`, NOT for gnu-make

CPPFLAGS=-std=c++11
INCLUDEDLLFLAGS=-static-libstdc++ -static-libgcc
DISABLEWARN=--enable-stdcall-fixup --disable-stdcall-fixup

TermShooter.exe: main.o engine.o player.o map.o mobs.o utils.o
	g++ $(CPPFLAGS) main.o engine.o player.o map.o mobs.o utils.o -o TermShooter.exe C:\Windows\System32\winmm.dll $(INCLUDEDLLFLAGS) $(DISABLEWARN)

main.o: src/main.cpp
	g++ $(CPPFLAGS) -c src/main.cpp

engine.o: src/engine.cpp src/headers/engine.h
	g++ $(CPPFLAGS) -c src/engine.cpp

player.o: src/player.cpp
	g++ $(CPPFLAGS) -c src/player.cpp

map.o: src/map.cpp
	g++ $(CPPFLAGS) -c src/map.cpp

mobs.o: src/mobs.cpp
	g++ $(CPPFLAGS) -c src/mobs.cpp

utils.o: src/utils.cpp
	g++ $(CPPFLAGS) -c src/utils.cpp

clean:
	del *.o

cleanAll:
	del *.o src\headers\*.h.gch *.log
