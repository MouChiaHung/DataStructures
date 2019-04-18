 /*************************
  *  char.cpp
  *  editor: amo
  *************************/
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bitset>
#include <cmath>
#include <vector>


#include <char.h>
#include <algorithm>    // std::for_each

#include <stack>

using namespace amo;
using std::hex;

/* -------------------------------------------------------------------- */
/* my define macro                                                     */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* global variables                                                     */
/* -------------------------------------------------------------------- */
// Allocating and initializing Class's static data member
Char* Char::instance = 0;

/* -------------------------------------------------------------------- */
/* implements                                                           */
/* -------------------------------------------------------------------- */
amo::Char::Char() {
	std::cout << "[Char::Char()]:" << this << std::endl;
}

amo::Char::~Char() {
	std::cout << "[Char::~Char()]:" << this << std::endl;
	//delete Char::instance;
}

Char& amo::Char::getInstance() {
	if (instance == nullptr) {
		std::cout << "[Char::getInstance()]: going to 'instance = new Char()':" << &instance << std::endl;
		instance = new Char();
	} 
	//std::cout << "[Char::getInstance()]: returns:" << instance << std::endl;
	return *instance;
} 

void amo::Char::trim(const char exp[], int& lo, int& hi) {
	std::cout << "[Char::trim()]: exp:" << exp << std::endl;
	int i = hi-lo+1;
	int index = lo;
	while (0<i--) std::cout << "[Char::trim()]: char[" << index++ << "]:" << exp[index] << std::endl;
	while (lo<=hi && exp[lo]!='(' && exp[lo]!=')')	lo++;
	while (hi>=lo && exp[hi]!='(' && exp[hi]!=')')	hi--;
} 

int amo::Char::divide(const char exp[], int lo, int hi) {
	std::cout << "[Char::divide()]: lo:" << lo << " and hi:" << hi << std::endl;
	int count = 1;
	int mi = lo;
	while (0!=count && ++mi<hi) {
		std::cout << "[Char::divide()]: while=loop, exp[" << mi << "]:" << exp[mi] << std::endl;
		if (exp[mi] == '(') {
			std::cout << "[Char::divide()]: going to count++ to be " << count+1 << std::endl;
			count++;
		}
		if (exp[mi] == ')') {
			std::cout << "[Char::divide()]: going to count-- to be " << count-1 << std::endl;
			count--;
		}
	}
	std::cout << "[Char::divide()]: returns:" << mi << std::endl;
	return mi;
}

bool amo::Char::paren(const char exp[], int begin, int end){ 
	std::cout << CYAN << "[Char::paren()]: begin:" << begin << " and end:" << end << WHITE << std::endl;
	int lo=begin, hi=end, mi;
	trim(exp, lo, hi);
	std::cout << YELLOW << "[Char::paren()]: trimmed lo:" << lo << " and hi:" << hi << WHITE << std::endl;
	if (lo > hi) {
		std::cout << YELLOW << "[Char::paren()]: lo > hi and returns true" << WHITE << std::endl;
		return true;
	}
	if (exp[lo] != '(') {
		std::cout << YELLOW << "[Char::paren()]: exp[lo] != '(':" << exp[lo] << " and returns false" << WHITE << std::endl;
		return false;
	}
	if (exp[hi] != ')') {
		std::cout << YELLOW << "[Char::paren()]: exp[hi] != ')':" << exp[hi] << " and returns false" << WHITE << std::endl;
		return false;
	}
	mi = divide(exp, lo, hi);
	std::cout << YELLOW << "[Char::paren()]: divided index:" << mi << WHITE << std::endl;
	if (mi > hi) return false;
	std::cout << CYAN << "[Char::paren()]: going to recursion" << WHITE << std::endl;
	bool ret = paren(exp, lo+1, mi-1) && paren(exp, mi+1, hi);
	std::cout << YELLOW << "[Char::paren()]: returns:" << (bool)ret << WHITE << std::endl;
	return ret;
}

bool amo::Char::paren(const char exp[], int len) {
	amo::Stack<char> stack;
	for (int i=0; i<len; i++) {
		if (exp[i] == '(' || exp[i] == '[' || exp[i] == '{') {
			stack.push(exp[i]);
			continue;
		}
		else if (exp[i] == ')' && stack.pop()!= '(') {
			std::cout << YELLOW << "[Char::paren()]: not () and  returns false" << WHITE << std::endl;
			return false;
		} 
		else if (exp[i] == '}' && stack.pop()!= '{') {
			std::cout << YELLOW << "[Char::paren()]: not {} and  returns false" << WHITE << std::endl;
			return false;
		} 
		else if (exp[i] == ']' && stack.pop()!= '[') {
			std::cout << YELLOW << "[Char::paren()]: not [] and  returns false" << WHITE << std::endl;
			return false;
		}
		else continue;
	}
	std::cout << YELLOW << "[Char::paren()]: returns true" << WHITE << std::endl;
	return true;
}

#if 0 //HB at bottom
void amo::Char::convert(amo::Stack<char>& stack, int n, int base) {
	static char digit[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	if (n > 0) {
		convert(stack, n/base, base);
		std::cout << "[Char::convert()]: going to push:" << digit[n%base] << std::endl;
		stack.push(digit[n%base]);
	} else std::cout << "[Char::convert()]: return and n:" << n << std::endl;
}

#else 
void amo::Char::convert(amo::Stack<char>& stack, int n, int base) {
	static char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	int rmd;
	while ((rmd=n%base)>=0 && n!=0) {
		stack.push(digit[rmd]);
		n = n/base;
	}
}
#endif

void amo::Char::convert(char dest[], int n, int base) { //like atoi()
	char* ori = dest;
	amo::Stack<char> stack;
	convert(stack, n, base);
	while(!stack.empty()) { //LB at bottom
		*(dest++) = stack.pop();
	}
	*(dest++) = '\0';
	dest = ori;
	std::cout << "[Char::convert(char*,int,int)]: dest:" << dest << std::endl;
}

void amo::Char::append(char* exp, int opnd) {
	int n = strlen(exp);
	int len;
	char opnds[64];
	convert(opnds, opnd, 10);
	len = strlen(opnds);
	//exp = (char*) realloc(exp, sizeof(char)*(n+len+1));
	strcat(exp, opnds);
}

void amo::Char::append(char* exp, char optr) {
	int n = strlen(exp);
	//exp = (char*) realloc(exp, sizeof(char)*(n+2));
	sprintf(exp+n, "%c", optr);
	*(exp+n+1) = '\0';
}
















