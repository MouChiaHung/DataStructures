 /*************************
  *  cell.cpp
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


#include <cell.h>
#include <algorithm> // std::for_each, copy
#include <iterator>   // std::back_inserter

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

/* -------------------------------------------------------------------- */
/* implements                                                           */
/* -------------------------------------------------------------------- */
std::istream& amo::operator>>(std::istream& is, Cell& cell) {
	is >> cell.status;
	return is;
}

std::ostream& amo::operator<<(std::ostream& os, Cell& cell) {
	switch (cell.status) {
		case AVAL:
			os << "AVAL /";
			break;
		case ROUTE:
			os << "ROUTE/";
			break;
		case BACK:
			os << "BACK /";
			break;
		case WALL:
			os << "WALL /";
			break;
		default:
			os << "ERROR /";
			break;
	}
	switch (cell.in) {
		case INIT:
			os << "INIT /";
			break;
		case EAST:
			os << "EAST /";
			break;
		case SOUTH:
			os << "SOUTH/";
			break;
		case WEST:
			os << "WEST /";
			break;
		case NORTH:
			os << "NORTH/";	
			break;
		case DEAD:
			os << "DEAD /";	
			break;	
		default:
			os << "ERROR/";
			break;
	}
	switch (cell.out) {
		case INIT :
			os << "INIT ";
			break;
		case EAST:
			os << "EAST ";
			break;
		case SOUTH:
			os << "SOUTH";
			break;
		case WEST:
			os << "WEST ";
			break;
		case NORTH:
			os << "NORTH";	
			break;
		case DEAD:
			os << "DEAD ";
			break;
		default:
			os << "ERROR";
			break;
	}
	return os;
}

amo::Cell::Cell(): x(0), y(0), status(AVAL), in(INIT), out(INIT) {
	std::cout << "[Cell::Cell()]:" << this << std::endl;
}

amo::Cell::Cell(int i, int j): x(i), y(j), status(AVAL), in(INIT), out(INIT) {
	std::cout << "[Cell::Cell(int,int)]:" << this << ", x:" << x << ", y:" << y << std::endl;
}

amo::Cell::Cell(const Cell& c) {
	x = c.x;
	y = c.y;
	status = c.status;
	in = c.in;
	out = c.out;
	std::cout << "[Cell::Cell(Cell&)]:" << this << ", x:" << x << ", y:" << y << std::endl;
}

amo::Cell::~Cell() {
	std::cout << "[Cell::~Cell()]:" << this << ", x:" << x << ", y:" << y << std::endl;
}

amo::Cell& amo::Cell::operator=(const amo::Cell& c) {
	x = c.x;
	y = c.y;
	status = c.status;
	in = c.in;
	out = c.out;
	std::cout << "[Cell::operator=(Cell&)]:" << this << ", x:" << c.x << ", y:" << c.y << std::endl;
	return *this;
}

bool amo::Cell::operator==(const amo::Cell& c) {
	bool ret = false;
	ret &= (x == c.x);
	ret &= (y == c.y);
	ret &= (status == c.status);
	ret &= (in == c.in);
	ret &= (out = c.out);
	//std::cout << "[Cell::operator==(Cell&)]:" << this << ", returns:" << ret << std::endl;
	return ret;
}





