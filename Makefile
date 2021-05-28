CPPFLAGS=-std=c++11

output: compiled/main.o compiled/renderer.o
	g++ $(CPPFLAGS) compiled/main.o compiled/renderer.o -o output

compiled/main.o: main.cpp source/renderer.cpp
	g++ $(CPPFLAGS) -c main.cpp source/renderer.cpp

clean:
	rm *.o output
