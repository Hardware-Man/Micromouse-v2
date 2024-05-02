Maze: bitmanip.o API.o DFS.o main.o maze.o
	g++ -g bitmanip.o API.o DFS.o main.o maze.o -o Maze

bitmanip.o: bitmanip.cpp
	g++ -g -c  bitmanip.cpp

API.o: API.cpp
	g++ -g -c  API.cpp

DFS.o: DFS.cpp
	g++ -g -c  DFS.cpp

main.o: main.cpp
	g++ -g -c  main.cpp

maze.o: maze.cpp
	g++ -g -c  maze.cpp
clean: Maze
	rm *.o Maze