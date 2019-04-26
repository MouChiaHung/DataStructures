#ifndef _CELL_H_
#define _CELL_H_

#include <iostream>

#include <stdio.h>
#include <stack.h>
#include <map>

#include <maze.h>

namespace amo {

class Cell { 
private:

public:
	Cell();
	Cell(Cell& c);
	Cell(int i, int j);
	~Cell();
	int x; //row
	int y; //col
	int in;
	int out;
	int status;
	Cell& operator=(const Cell& c);
	bool operator==(const Cell& c);
friend class Maze;
friend std::istream& operator>>(std::istream& is, Cell& cell);
friend std::ostream& operator<<(std::ostream& os, Cell& cell);
};
	
std::istream& operator>>(std::istream& is, Cell& cell);
std::ostream& operator<<(std::ostream& os, Cell& cell);
};
#endif