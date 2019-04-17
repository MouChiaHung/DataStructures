 /*************************
  *  move.cpp
  *  editor: amo
  *************************/
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bitset>
#include <cmath>

#include <move.h>
#include <stack>
#include <utility>      // std::move

using namespace amo;

/* -------------------------------------------------------------------- */
/* my define macro                                                     */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* global variables                                                     */
/* -------------------------------------------------------------------- */
// Allocating and initializing Class's static data member
Move* Move::instance = 0;

/* -------------------------------------------------------------------- */
/* implements                                                           */
/* -------------------------------------------------------------------- */
amo::Move::Move() {
	std::cout << "[Move::Move()]:" << this << std::endl;
}

amo::Move::~Move() {
	std::cout << "[Move::~Move()]:" << this << std::endl;
}

Move& amo::Move::getInstance() {
	if (instance == nullptr) {
		std::cout << "[Move::getInstance()]:going to 'instance = new Move()':" << &instance << std::endl;
		instance = new Move();
	} 
	std::cout << "[Move::getInstance()]:returns:" << instance << std::endl;
	return *instance;
} 	

void amo::Move::hanoi(int n, std::stack<int>& from, std::stack<int>& buffer, std::stack<int>& to) {
	if (n == 0) {
		std::cout << "[Move::hanoi()]: n is 0 and returns" << std::endl;
		return;
	}
	std::cout << "[Move::hanoi()]: going to recurrently call hanoi(" << n-1 
			  << ", from(from:" << &from 
			  << "), to(buffer:" << &to 
			  << "), buffer(to:" << &buffer 
			  << "));" << std::endl;
	hanoi(n-1, from, to, buffer);
	
	//std::move(from, to);
	to.push(from.top());
	from.pop();
	
	std::cout << "[Move::hanoi()]: going to recurrently call hanoi(" << n-1 
			  << ", buffer(from:" << &buffer
			  << "), from(buffer:" << &from 
			  << "), to(to:" << &to 
			  << "));" << std::endl;
	hanoi(n-1, buffer, from, to);
	return;
}
