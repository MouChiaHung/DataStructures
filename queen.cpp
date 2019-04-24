 /*************************
  *  queen.cpp
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


#include <queen.h>
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
Queen* Queen::instance = 0;
static int** chess; //A dynamic 2D array is basically an array of pointers to arrays
int row, col;
int track;
static int ans=0;
static std::vector<int> queens;
static std::map<int, int> moves;

/* -------------------------------------------------------------------- */
/* implements                                                           */
/* -------------------------------------------------------------------- */
void collect(std::map<int,int>& map, int count, ...) {
	va_list ap;
	count = count*2;
	va_start(ap, (count));
	int key;
	int value;
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

amo::Queen::Queen() {
	std::cout << "[Queen::Queen()]:" << this << std::endl;
}

amo::Queen::~Queen() {
	std::cout << "[Queen::~Queen()]:" << this << std::endl;
	//delete Queen::instance;
}

Queen& amo::Queen::getInstance() {
	if (instance == nullptr) {
		std::cout << "[Queen::getInstance()]: going to 'instance = new Queen()'" << std::endl;
		instance = new Queen();
	}
	if (chess == nullptr) {
		std::cout << "[Queen::getInstance()]: going to 'chess = new int[][]'"<< std::endl;
		row = 4;
		col = 4;
		chess = new int*[row];
		for (int i=0; i<row; i++)  {		
			*(chess+i) = new int[col];
			//chess[i] = new int[col];
			for (int j=0; j<col; j++) 
				*(*(chess+i)+j) = 10*(i+1)+j;
				//chess[i][j] = 10*(i+1)+j;
		}
	} 
	//std::cout << "[Queen::getInstance()]: returns:" << instance << std::endl;
	return *instance;
} 

void amo::Queen::traverse() {
	std::cout << "[Queen::traverse()]: --- Traverse begin ---" << WHITE << std::endl;
	for (int i=0; i<row; i++) {
		for (int j=0; j<col; j++) {
			std::cout << "[" << i <<"][" << j << "]:" << chess[i][j];
			if (j==col-1) std::cout << "" << std::endl;
		}
	}	
	std::cout << "[Queen::traverse()]: --- Traverse end ---" << WHITE << std::endl;
}

void amo::Queen::traverse(int marki, int markj) {
	std::cout << BLUE <<"[Queen::traverse()]: --- Traverse begin ---" << WHITE << std::endl;
	for (int i=0; i<row; i++) {
		for (int j=0; j<col; j++) {
			if (i== marki && j==markj) std::cout << GREEN << "[" << i << "][" << j << "]" << WHITE;
			else std::cout << "[" << i <<"][" << j << "]";
			if (j==col-1) std::cout << "" << std::endl;
		}
	}	
	std::cout << BLUE << "[Queen::traverse()]: --- Traverse end ---" << WHITE << std::endl;
}

inline bool is_answer(std::map<int,int>& map, int i, int j) {
	for (std::map<int,int>::iterator it=map.begin(); it!=moves.end(); it++)
		if (i==it->first && j==it->second) 	return true;
	return false;
}

void amo::Queen::traverse(std::map<int,int>& map) {
	std::cout << BLUE <<"[Queen::traverse()]: --- Traverse begin ---" << WHITE << std::endl;
	for (int i=0; i<row; i++) {
		for (int j=0; j<col; j++) {
			if (is_answer(map, i, j)) std::cout << GREEN << "[" << i <<"][" << j << "]" << WHITE; 
			else std::cout << "[" << i <<"][" << j << "]"; 
			if (j==col-1) std::cout << "" << std::endl;
		}
	}	
	std::cout << BLUE << "[Queen::traverse()]: --- Traverse end ---" << WHITE << std::endl;
}

void amo::Queen::place(int probing, int n) {
	if (n != row || n != col ) {
		if (chess != nullptr) {
			for (int i=0;i<row;i++) delete *(chess+i);
			delete chess;
		}	
		row = n;
		col = n;
		chess = new int*[n];
		for (int i=0;i<n;i++) {
			*(chess+i) = new int[col];
			for (int j=0; j<col; j++) 
				*(*(chess+i)+j) = 100*(i+1)+j;
		}
	}
	if (probing >= n) {
		ans += 1;
		std::cout << GREEN <<"[Queen::place()]: returns when met the pass-the-end of probing which means deduced one of answer:" << ans << WHITE << std::endl;
		for (std::vector<int>::iterator it=queens.begin(); it!=std::next(queens.begin(), n); it++)
			collect(moves, 1, std::distance(queens.begin(), it), *it);
		traverse(moves);
		moves.clear();
		return;
	}
	for (int pruning=0; pruning<col; pruning++) {
		track++;
		//traverse(probing, pruning);
		//if (probing==n-1 && pruning==col-1) std::cout << RED <<"[Queen::place()]: track:" << track << WHITE << std::endl; //final track=4^4+4^3+4^2+4^1=340 if n=4 or track=3^3+3^2+3^1=39 if n=3
		if (!check(probing, pruning)) {
		//if (false) { //watching all moves
			//std::cout << "[Queen::place()]: going to prune" << WHITE << std::endl;
			/**
			 * 'prunes' when met one of dead ends of this probing at this pruning
			 */
			continue;
		}
		else { //found one of rights of this probing at this pruning and digs into the one more deeper 
			//std::cout << "[Queen::place()]: going to probe" << WHITE << std::endl;
			if (queens.size() < n) queens.resize(n);
			queens.at(probing) = pruning;
			/**
			 * 'probes' one more deeper by making one more call stack returning back here as backtracking and proceeding to another pruning
			 */ 
			place(probing+1, n);
		}
	}
	/**
	 * 'backtracks'
	 */ 
	return;
}
	
bool amo::Queen::check(int row, int column) {
	if (row == 0) {
		//std::cout << CYAN << "okay chess[" << row <<"][" << column << "]" << WHITE << std::endl;
		return true;
	}
	for (std::vector<int>::iterator it=queens.begin(); it!=std::next(queens.begin(), row); it++) {
		int placed_row = std::distance(queens.begin(), it);
		int placed_column = queens.at(placed_row);
		if (placed_column == column) {
			//std::cout << MAGENTA << "not across,   queen[" << placed_row << "][" << placed_column << "] and chess[" << row <<"][" << column << "]" << WHITE << std::endl;
			return false;
		}
		if (std::abs(placed_column-column) == std::abs(placed_row-row)) {
			//std::cout << MAGENTA << "not diagonal, queen[" << placed_row << "][" << placed_column << "] and chess[" << row <<"][" << column << "]" << WHITE << std::endl;
			return false;
		}
	}
	//std::cout << CYAN << "okay chess[" << row <<"][" << column << "]" << WHITE << std::endl;
	return true;
}

int amo::Queen::answer() {
	return ans;
}





