Maze: bitmanip.o API.o DFS.o main.o maze.o stack.o BFS.o Queue.o
	g++ -g bitmanip.o API.o DFS.o main.o maze.o stack.o BFS.o Queue.o -o Maze
BFS.o: BFS.cpp
	g++ -g -c BFS.cpp
Queue.o: Queue.cpp
	g++ -g -c Queue.cpp
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
stack.o: stack.cpp
	g++ -g -c stack.cpp
clean: Maze
	rm *.o Maze