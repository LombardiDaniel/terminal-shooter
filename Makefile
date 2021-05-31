CPPFLAGS=-std=c++11

output: compiled/main.o compiled/engine.o
	g++ $(CPPFLAGS) compiled/main.o compiled/engine.o -o TermShooter.exe

compiled/main.o: src/main.cpp src/engine.cpp
	g++ $(CPPFLAGS) -c main.cpp src/engine.cpp

clean:
	rm */**.o output */**.exe


# oth: g++ main.cpp engine.cpp -o .\..\TermShooter.exe
