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

/* -------------------------------------------------------------------- */
/* global variables                                                     */
/* -------------------------------------------------------------------- */
// Allocating and initializing Class's static data member
Maze* Maze::instance = 0;
static std::map<int, int> moves;

/* -------------------------------------------------------------------- */
/* implements                                                           */
/* -------------------------------------------------------------------- */
amo::Maze::~Maze() {
	std::cout << "[Maze::~Maze()]:" << this << ", row:" << row << ", col:" << col << std::endl;
	//delete Maze::instance;
}

amo::Maze::Maze(int n, int m): row(n), col(m) {
	std::cout << "[Maze::Maze()]:" << this << ", row:" << row << ", col:" << col << std::endl;
	
	Cell cell(1,1);
	std::cout << "[Maze::Maze()]: cell:" << cell << std::endl;
	
	for (int i=0; i<row; i++) {
		//*(mz+i) =  new Cell[col];
		*(mz+i) = (Cell*) malloc(sizeof(Cell)*col);
		std::cout << "[Maze::Maze()]: size of mz:" << sizeof(*mz)/sizeof(**mz) << std::endl;
		for (int j=0; j<col; j++) {
			mz[i][j] = Cell(i, j);
		}
	} 
} 

amo::Maze::Cell::Cell(int i, int j): x(i), y(j) {
	std::cout << "[Maze::Cell::Cell()]:" << this << ", x:" << x << ", y:" << y << " in " << instance->row << "x" << instance->col << " maze" << std::endl;
}

amo::Maze::Cell::~Cell() {
	std::cout << "[Maze::Cell::~Cell()]:" << this << ", x:" << x << ", y:" << y << " in " << instance->row << "x" << instance->col << " maze" << std::endl;
}

amo::Maze::Cell& amo::Maze::Cell::operator=(const amo::Maze::Cell& cell) {
	this->status = cell.status;
	return *this;
}

Maze& amo::Maze::getInstance(int n, int m) {
	if (instance == nullptr) {
		std::cout << "[Maze::getInstance()]: going to 'instance = new Maze()'" << std::endl;
		instance = new Maze(n, m);
	}
	return *instance;
} 

void collect_maze(std::map<int,int>& map, int count, ...) {
	va_list ap;
	count = count*2;
	va_start(ap, count);
	int key; //x of cell
	int value; //y of cell
	std::pair<std::map<int,int>::iterator,bool> ret;
	for (int i=0; i<count; i=i+2) {
		key = va_arg(ap, int);
		value = va_arg(ap, int);
		ret = map.insert(std::make_pair(key, value));
		//if(ret.second) std::cout << YELLOW << "newly inserted element key:" << ret.first->first << " and value:" << ret.first->second << WHITE << std::endl; 
		//else std::cout << YELLOW << "existing equivalent key element key:" << ret.first->first << " and value:" << ret.first->second << WHITE << std::endl; 
	}
	va_end(ap);
}

inline bool is_answer(std::map<int,int>& map, int i, int j) {
	for (std::map<int,int>::iterator it=map.begin(); it!=moves.end(); it++)
		if (i==it->first && j==it->second) 	return true;
	return false;
}

void amo::Maze::traverse(std::map<int,int>& map) {
	std::cout << BLUE <<"[Maze::traverse()]: --- Traverse begin ---" << WHITE << std::endl;
	for (int i=0; i<row; i++) {
		for (int j=0; j<col; j++) {
			if (is_answer(map, i, j)) std::cout << GREEN << "[" << i <<"][" << j << "]" << WHITE; 
			else std::cout << "[" << i <<"][" << j << "]"; 
			if (j==col-1) std::cout << "" << std::endl;
		}
	}	
	std::cout << BLUE << "[Maze::traverse()]: --- Traverse end ---" << WHITE << std::endl;
}

bool amo::Maze::labyrinth(int sx, int sy, int tx, int ty) {
	Maze::Cell* s = new Cell(sx, sy);
	Maze::Cell* t = new Cell(tx, ty);
	for (int i=0; i<row; i++)
		collect_maze(moves, 1, i, 0);
	traverse(moves);
	return false;
}





