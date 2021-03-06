#ifndef _MAZE_H_
#define _MAZE_H_

#include <iostream>

#include <stdio.h>
#include <stack.h>
#include <stack>
#include <map>

#include <cell.h>

namespace amo {

typedef enum {AVAL, ROUTE, BACK, WALL} STATUS;
typedef enum {INIT, EAST, SOUTH, WEST, NORTH, DEAD} DIRECTION;
class Cell;
/**
 * Enclosing class
 */
class Maze {
public:
	/**
	 * Nested class
	 */
	class Inner { 
	private:
		
	public:
		Inner();		
		~Inner();
	friend class Maze;
	};
	static Maze& getInstance(int n, int m);
	void traverse(std::vector<Cell*>& vector);
	void traverse(std::stack<Cell*>& stack);
	bool labyrinth(int sx, int sy, int tx, int ty);
	Cell* pry(Cell& c);
	void probe(Cell** c);
	int next_available(Cell& c);
private:
	static Maze* instance;
	//static std::stack<amo::Cell> path;
	Maze(int i, int j);
	~Maze();
	int row;
	int col;
	Cell **mz;
friend class Inner; 
};

};
#endif