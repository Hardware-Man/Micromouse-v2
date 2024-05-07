Maze: bitmanip.o API.o DFS.o main.o maze.o stack.o BFS.o Queue.o
	g++ -g -O2 bitmanip.o API.o DFS.o main.o maze.o stack.o BFS.o Queue.o -o Maze
BFS.o: BFS.cpp
	g++ -g -O2 -c BFS.cpp
Queue.o: Queue.cpp
	g++ -g -O2 -c Queue.cpp
bitmanip.o: bitmanip.cpp
	g++ -g -O2 -c  bitmanip.cpp

API.o: API.cpp
	g++ -g -O2 -c  API.cpp

DFS.o: DFS.cpp
	g++ -g -O2 -c  DFS.cpp

main.o: main.cpp
	g++ -g -O2 -c  main.cpp

maze.o: maze.cpp
	g++ -g -O2 -c  maze.cpp
stack.o: stack.cpp
	g++ -g -O2 -c stack.cpp
clean: Maze
	rm *.o Maze