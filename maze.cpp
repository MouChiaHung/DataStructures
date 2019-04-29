 /*************************
  *  maze.cpp
  *  editor: amo
  *************************/
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> 
#include <string.h>
#include <bitset>
#include <cmath>
#include <vector>


#include <maze.h>
#include <algorithm>    // std::for_each

#include <stack>
#include <map>

using namespace amo;

/* -------------------------------------------------------------------- */
/* my define macro                                                     */
/* -------------------------------------------------------------------- */
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

#define INIT_OUT INIT

/* -------------------------------------------------------------------- */
/* global variables                                                     */
/* -------------------------------------------------------------------- */
// Allocating and initializing Class's static data member
Maze* Maze::instance = 0;
//std::stack<amo::Cell> Maze::path;
static std::vector<amo::Cell*> moves;

/* -------------------------------------------------------------------- */
/* implements                                                           */
/* -------------------------------------------------------------------- */
amo::Maze::~Maze() {
	std::cout << "[Maze::~Maze()]:" << this << ", row:" << row << ", col:" << col << std::endl;
	//delete Maze::instance;
}

amo::Maze::Maze(int n, int m): row(n), col(m) {
	std::cout << "[Maze::Maze()]:" << this << ", row:" << row << ", col:" << col << std::endl;
	for (int i=0; i<row; i++) {
		std::cout << YELLOW << "[Maze::Maze()]: going to create elements of row:" << i << WHITE << std::endl;
		*(mz+i) = new Cell[col];
		//*(mz+i) = (Cell*) malloc(sizeof(Cell)*col);
		for (int j=0; j<col; j++) {
			mz[i][j] = Cell(i, j);
			if (i == 2 && j == 0) mz[i][j].status = WALL;
			if (i == 2 && j == 1) mz[i][j].status = WALL;
			if (i == 3 && j == 0) mz[i][j].status = WALL;
		}
	}
} 

Maze& amo::Maze::getInstance(int n, int m) {
	if (instance == nullptr) {
		std::cout << "[Maze::getInstance()]: going to 'instance = new Maze()'" << std::endl;
		instance = new Maze(n, m);
	}
	return *instance;
} 

#if 0
void collect_move(std::vector<amo::Cell*>& vector, int count, ...) {
	va_list ap;
	va_start(ap, count);
	amo::Cell* e;
	for (int i=0; i<count; i=i++) {
		e = va_arg(ap, amo::Cell*);
		vector.push_back(e);
	}
	va_end(ap);
}

#else
void collect_move(std::vector<amo::Cell*>& vector, amo::Cell* e) {
	vector.push_back(e);
}
#endif

void erase_move(std::vector<amo::Cell*>& vector, amo::Cell* e) {
	for (std::vector<amo::Cell*>::iterator it=vector.begin(); it!=vector.end(); it++) {
		if (**(it) == *e) {
			std::cout << "[Maze::getInstance()]: going to erase cell:" << *e << " from moves at " << std::distance(vector.begin(), it) << std::endl;
			vector.erase(it);
		}
	}
	vector.push_back(e);
}

inline bool is_move(std::vector<amo::Cell*>& vector, int i, int j) {
	for (std::vector<amo::Cell*>::iterator it=vector.begin(); it!=vector.end(); it++)
		if (i==(*it)->x && j==(*it)->y) return true;
	return false;
}

void amo::Maze::traverse(std::vector<amo::Cell*>& vector) {
	std::cout << BLUE <<"[Maze::traverse()]: --- Traverse begin ---" << WHITE << std::endl;
	for (int i=0; i<row; i++) {
		for (int j=0; j<col; j++) {
			if (is_move(vector, i, j)) {
				if (mz[i][j].status == WALL) std::cout << RED << "[" << i <<"][" << j << "]" << mz[i][j] << WHITE;  
				else std::cout << GREEN << "[" << i <<"][" << j << "]" << mz[i][j] << WHITE; 
			}
			else {
				if (mz[i][j].status == WALL) std::cout  << MAGENTA << "["<< i <<"][" << j << "]" << mz[i][j] << WHITE;  
				else std::cout << "[" << i <<"][" << j << "]" << mz[i][j] << WHITE;  
			}
			if (j==col-1) std::cout << "" << std::endl;
		}
	}	
	std::cout << BLUE << "[Maze::traverse()]: --- Traverse end ---" << WHITE << std::endl;
}

bool amo::Maze::labyrinth(int sx, int sy, int tx, int ty) {
	Cell* s = new Cell(sx, sy);
	Cell* t = new Cell(tx, ty);
	std::stack<amo::Cell> path;
	int repeat = 7;
	Cell* probing = s;
	do {
		if (!(0<repeat--)){ //retry limit
			std::cout << RED << "[Maze::labyrinth()]: No solution" << WHITE << std::endl;
			break;
		} 
		probe(&probing); //probes and decides the next direction
		if (probing == NULL) { //met dead
			std::cout << RED << "[Maze::labyrinth()]: met DEAD" << WHITE << std::endl;
			break;
		}
		path.push(*probing); //records moves
		std::cout << CYAN << "[Maze::labyrinth()]: loop:" << repeat << ", probing:[" << probing->x << "][" << probing->y << "]:" << *probing << WHITE << std::endl;
		collect_move(moves, probing);
		if (probing->x == t->x && probing->y == t->y) { //checks if arrived target or goes ahead to probe
			std::cout << CYAN << "[Maze::labyrinth()]: Got solution" << WHITE << std::endl;
			break;
		}
	} while(true);
	
	//collect_move(moves, s);
	//collect_move(moves, t);
	
	traverse(moves);
	return false;
}

/**
 * manipulation of cells
 */
int amo::Maze::next_available(Cell& c) {
	int out = c.out;
	int i = c.x;
	int j = c.y;
	amo::Cell* next;
	int dir = INIT;
	while (DEAD>dir++) {
		switch (dir) {
		case EAST:
			if ((j+1)>=col) {
				std::cout << "[Maze::next_available()]: NOT EAST" << WHITE << std::endl;
				break;
			}
			next = &mz[i][j+1];
			if (next->status == AVAL) {
				std::cout << "[Maze::next_available()]: NEXT EAST from [" << i << "][" << j << "]" << c
						  << " onto [" << i << "][" << j+1 << "]" << *next << WHITE << std::endl;
				return dir;
			} else {
				std::cout << "[Maze::next_available()]: NO AVAL EAST" << WHITE << std::endl;
				break;
			}
		case SOUTH:
			if ((i+1)>=row) {
				std::cout << "[Maze::next_available()]: NOT SOUTH" << WHITE << std::endl;
				break;
			}
			next = &mz[i+1][j];
			if (next->status == AVAL) {
				std::cout << "[Maze::next_available()]: NEXT SOUTH from [" << i << "][" << j << "]" << c
					      << " onto [" << i+1 << "][" << j << "]" << *next << WHITE << std::endl;
				return dir;
			} else {
				std::cout << "[Maze::next_available()]: NO AVAL SOUTH" << WHITE << std::endl;
				break;
			}
		case WEST:
			if ((j-1)<0) {
				std::cout << "[Maze::next_available()]: NOT WEST" << WHITE << std::endl;
				break;
			}
			next = &mz[i][j-1];
			if (next->status == AVAL) {
				std::cout << "[Maze::next_available()]: NEXT WEST from [" << i << "][" << j << "]" << c
						  << " onto [" << i << "][" << j-1 << "]" << *next << WHITE << std::endl;
				return dir;
			} else {
				std::cout << "[Maze::next_available()]: NO AVAL WEST" << WHITE << std::endl;
				break;
			}
		case NORTH:
			if ((i-1)<0) {
				std::cout << "[Maze::next_available()]: NOT NORTH" << WHITE << std::endl;
				break;
			}
			next = &mz[i-1][j];
			if (next->status == AVAL) {
				std::cout << "[Maze::next_available()]: NEXT NORTH from [" << i << "][" << j << "]" << c
						  << " onto [" << i-1 << "][" << j << "]" << *next << WHITE << std::endl;
				return dir;
			} else {
				std::cout << "[Maze::next_available()]: NOT AVAL NORTH" << WHITE << std::endl;
				break;
			}
		}
	}
	std::cout << "[Maze::next_available()]: returns DEAD:" << dir << WHITE << std::endl;
	return dir;//DEAD
} 
 
void amo::Maze::probe(amo::Cell** c) {
	if (((**c)).out >= DEAD) { //as BACK
		std::cout << YELLOW << "[Maze::probe()]: [" << (**c).x << "][" << (**c).y << "] is DEAD:" << (**c).out << WHITE << std::endl;
		*c = NULL;
		return;
	} 
	switch ((**c).out) {
		case INIT:
			std::cout << YELLOW << "[Maze::probe()]: INIT" << WHITE << std::endl;
			(**c).out = next_available(**c);
			probe(c); 
			return;
		case EAST:
			if (((**c).y+1)>=col) {
				std::cout << YELLOW << "[Maze::probe()]: Beyond EAST and Recur" << WHITE << std::endl;
				probe(c);
				return;
			}
			std::cout << YELLOW << "[Maze::probe()]: GO EAST from [" << (**c).x << "][" << (**c).y << "]"
								<< " onto [" << (**c).x << "][" << (**c).y+1 << "]" << WHITE << std::endl;		
			(**c).status = ROUTE; //marks old moves for avoiding to go out of then go back to the same position
			*c = &mz[(**c).x][(**c).y+1]; //probes
			(**c).in = WEST;
			(**c).out = next_available(**c);
			return;
		case SOUTH:
			if (((**c).x+1)>=row) {
				std::cout << YELLOW << "[Maze::probe()]: Beyond SOUTH and Recur" << WHITE << std::endl;
				probe(c); 
				return;
			}
			std::cout << YELLOW << "[Maze::probe()]: GO SOUTH from [" << (**c).x << "][" << (**c).y << "]"
								<< " onto [" << (**c).x+1 << "][" << (**c).y << "]" << WHITE << std::endl;
			(**c).status = ROUTE;
			*c = &mz[(**c).x+1][(**c).y];
			(**c).in = NORTH;
			(**c).out = next_available(**c);
			return;
		case WEST:
			if (((**c).y-1)<0) {
				std::cout << YELLOW << "[Maze::probe()]: Beyond WEST and Recur" << WHITE << std::endl;
				probe(c); 
				return;
			}
			std::cout << YELLOW << "[Maze::probe()]: GO WEST from [" << (**c).x << "][" << (**c).y << "]"
								<< " onto [" << (**c).x << "][" << (**c).y-1 << "]" << WHITE << std::endl;
			(**c).status = ROUTE;
			*c = &mz[(**c).x][(**c).y-1];
			(**c).in = EAST;
			(**c).out = next_available(**c);
			return;
		case NORTH:
			if (((**c).x-1)<0) {
				std::cout << YELLOW << "[Maze::probe()]: Beyond NORTH and Recur" << WHITE << std::endl;
				probe(c); 
				return;
			}
			std::cout << YELLOW << "[Maze::probe()]: GO NORTH from [" << (**c).x << "][" << (**c).y << "]"
								<< " onto [" << (**c).x-1 << "][" << (**c).y << "]" << WHITE << std::endl;
			(**c).status = ROUTE;
			*c = &mz[(**c).x-1][(**c).y];
			(**c).in = SOUTH;
			(**c).out = next_available(**c);
			return;
		case DEAD:
			std::cout << YELLOW << "[Maze::probe()]: DEAD" << WHITE << std::endl;
			*c = NULL;
			return;
		default:
			std::cout << YELLOW << "[Maze::probe()]: ERROR" << WHITE << std::endl;
			*c = NULL; 
			return;
	}
}

amo::Cell* amo::Maze::pry(amo::Cell& c) {
	amo::Cell* next = NULL;
	int direction;
	if (c.out >= DEAD) {
		std::cout << YELLOW << "[Maze::pry()]: [" << c.x << "][" << c.y << "] is DEAD:" << c.out << WHITE << std::endl;
		return NULL;
	} 
	else {
		direction = c.out+1;
	}
	switch (direction) {
		case INIT:
			std::cout << YELLOW << "[Maze::pry()]: INIT" << WHITE << std::endl;
			next = NULL; 
			break;
		case EAST:
			if ((c.y+1)>=col) {
				std::cout << YELLOW << "[Maze::pry()]: Beyond EAST" << WHITE << std::endl;
				return NULL;
			}
			else {
				std::cout << YELLOW << "[Maze::pry()]: EAST" << WHITE << std::endl;
				next = &mz[c.x][c.y+1];
			}
			break;	
		case SOUTH:
			if ((c.x+1)>=row) {
				std::cout << YELLOW << "[Maze::pry()]: Beyond SOUTH" << WHITE << std::endl;
				return NULL;
			}
			else {
				std::cout << YELLOW << "[Maze::pry()]: SOUTH" << WHITE << std::endl;
				next = &mz[c.x+1][c.y];
			}
			break;
		case WEST:
			if ((c.y-1)<0) {
				std::cout << YELLOW << "[Maze::pry()]: Beyond WEST" << WHITE << std::endl;
				return NULL;
			}
			else {
				std::cout << YELLOW << "[Maze::pry()]: WEST" << WHITE << std::endl;
				next = &mz[c.x][c.y-1];
			}
			break;
		case NORTH:
			if ((c.x-1)<0) {
				std::cout << YELLOW << "[Maze::pry()]: Beyond NORTH" << WHITE << std::endl;
				return NULL;
			}
			else {
				std::cout << YELLOW << "[Maze::pry()]: NORTH" << WHITE << std::endl;
				next = &mz[c.x-1][c.y];
			}
			break;
		case DEAD:
			std::cout << YELLOW << "[Maze::pry()]: DEAD" << WHITE << std::endl;
			return NULL;
		default:
			std::cout << YELLOW << "[Maze::pry()]: ERROR" << WHITE << std::endl;
			return NULL;
	}
	return next;
}














