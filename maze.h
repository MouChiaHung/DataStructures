#ifndef _MAZE_H_
#define _MAZE_H_

#include <iostream>

#include <stdio.h>
#include <stack.h>
#include <map>

namespace amo {

typedef enum {AVAL, ROUTE, BACK, WALL} STATUS;

/**
 * Enclosing class
 */
class Maze {
public:
	/**
	 * Nested class
	 */
	class Cell { 
	private:
		int x;
		int y;
		int in;
		int out;
	public:
		Cell():x(0),y(0){};
		Cell(int i, int j);
		~Cell();
		int status;
		Cell& operator=(const Cell& cell);
	friend class Maze;
	friend std::istream& operator>>(std::istream& is, Maze::Cell& cell);
	friend std::ostream& operator<<(std::ostream& os, Maze::Cell& cell);
	};
	static Maze& getInstance(int n, int m);
	void traverse(std::map<int,int>& map);
	bool labyrinth(int sx, int sy, int tx, int ty);
private:
	static Maze* instance;
	Maze(int i, int j);
	~Maze();
	int row;
	int col;
	Maze::Cell** mz;
	static int t;	
friend class Cell; 
friend std::istream& operator>>(std::istream& is, Maze::Cell& cell);
friend std::ostream& operator<<(std::ostream& os, Maze::Cell& cell);
};

};
#endif