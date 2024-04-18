maze.exe: API.o flood.o main.o
	g++ API.o flood.o main.o -o maze
API.o: API.cpp
	g++    -c -o API.o API.cpp
flood.o: flood.cpp
	g++    -c -o flood.o flood.cpp
main.o: main.cpp
	g++    -c -o main.o main.cpp
clean: maze.exe
	rm *.o
	rm maze.exe