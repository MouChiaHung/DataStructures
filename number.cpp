 /*************************
  *  number.cpp
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

#include <number.h>
#include <algorithm>    // std::for_each

#include <stack>

using namespace amo;

/* -------------------------------------------------------------------- */
/* my define macro                                                     */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* global variables                                                     */
/* -------------------------------------------------------------------- */
// Allocating and initializing Class's static data member
Number* Number::instance = 0;

/* -------------------------------------------------------------------- */
/* implements                                                           */
/* -------------------------------------------------------------------- */
amo::Number::Number() {
	std::cout << "[Number::Number()]:" << this << std::endl;
}

amo::Number::~Number() {
	std::cout << "[Number::~Number()]:" << this << std::endl;
}

Number& amo::Number::getInstance() {
	if (instance == nullptr) {
		std::cout << "[Number::getInstance()]:going to 'instance = new Number()':" << &instance << std::endl;
		instance = new Number();
	} 
	std::cout << "[Number::getInstance()]:returns:" << instance << std::endl;
	return *instance;
} 	

int amo::Number::getBinCount(int num) {
	int count = 0;
	while (num > 0) {
		if ((num&0x1)>0) count++;
		std::cout << "[Number::getBinCount(int)]: in while-loop, count:" << count << " and parameter:" << std::bitset<sizeof(int)*8>(num) << " (" << num << ")" << std::endl;
		num >>= 1;
	}
	return count;
}

#if 0
long long amo::Number::power2(int n) {
	if (n < 0) retrun 0;
	long long pow = 1;
	std::cout << "[Number::power2(int)]: pow:" << pow << std::endl;
	//while (0 < (--n)) {
	while (0 < n--) {
		pow <<= 1;
		std::cout << "[Number::power2(int)]: in while-loop, n:" << n << " and pow:" << pow << std::endl;
	}
	return pow;
}

#else
inline long long sqr(long long n) {return n * n;}	
long long amo::Number::power2(int n) {
	if (n < 0) return 0;
	if (n == 0) {
		std::cout << "[Number::power2(int)]: n == 0 and returns 1" << std::endl;
		return 1;
	}
	if (n & 1) std::cout << "[Number::power2(int)]: n:" << n << " and going to sqr(power2(" << n/2 << ")) << 1" << std::endl; //odd
	else	   std::cout << "[Number::power2(int)]: n:" << n << " and going to sqr(power2(" << n/2 << "))" << std::endl; //even
	return (n & 1) ? sqr(power2(n/2)) << 1 : sqr(power2(n/2));
}
#endif

int amo::Number::akermann(int m, int n) {
	if (m < 0 || n <0) {
		std::cout << "[Number::akermann(int, int)]: !!! m < 0 || n < 0 returns:" << -1 << std::endl;
		return -1;
	}
	if (m == 0) {
		std::cout << "[Number::akermann(int, int)]: m == 0 returns:" << n+1 << std::endl;
		return n+1;
	}
	if (n == 0) {
		std::cout << "[Number::akermann(int, int)]: m > 0 && n == 0 going to akermann(" << m-1 << ", " << 1 << "))" << std::endl;
		return akermann(m-1, 1);
	} else {
		std::cout << "[Number::akermann(int, int)]: m > 0 && n > 0 going to akermann(" << m-1 << ", akermann(" << m << ", " << n-1 << "))" << std::endl;
		return akermann(m-1, akermann(m, n-1));
	}	
}

int amo::Number::hailstone(int n) {
	int run = 1;
	if (n < 1) {
		std::cout << "[Number::hailstone(int)]: !!! n < 1 returns:" << -1 << std::endl;
		return 1;
	}
	if (n == 1) {
		std::cout << "[Number::hailstone(int)]: n == 1 && run = 0 returns:" << 0 << std::endl;
		return 0;
	}
	if (n%2 == 0) {
		std::cout << "[Number::hailstone(int)]: even and going to hailstone(n/2:" << n/2 << ")" << std::endl;
		run += hailstone(n/2);
	} else {
		std::cout << "[Number::hailstone(int)]: odd and going to hailstone((3*n+1):" << 3*n+1 << ")" << std::endl;
		run += hailstone(3*n+1);
	}
	std::cout << "[Number::hailstone(int)]: returns:" << run << std::endl;
	return run;
}

#if 0
int amo::Number::sum(std::vector<int>& vector) {
	int back = 0;
	int sum = 0;
	if (vector.size() < 0) {
		std::cout << "[Number::sum(std::vector<int>&)]: !!! n < 0 returns:" << 0 << std::endl;
		return 0;
	}
	if (vector.size() == 0) {
		std::cout << "[Number::sum(std::vector<int>&)]: size == 0 returns:" << 0 << std::endl;
		return 0;
	}
	back = vector.back();
	vector.pop_back();
	int recursion = Number::sum(vector);
	std::cout << "[Number::sum(std::vector<int>&)]: going to sum = back:" << back << " + sum() recurrently:" << recursion << std::endl;
	sum = back + recursion;
	std::cout << "[Number::sum(std::vector<int>&)]: returns:" << sum << std::endl;
	return sum;
}
#else
struct functor {
		void operator() (int element) {std::cout << "element:" << element << std::endl;}
} my_functor;	
int amo::Number::sum(std::vector<int>& vector) {
	if (vector.size() < 0) {
		std::cout << "[Number::sum(std::vector<int>&)]: !!! n < 0 returns:" << 0 << std::endl;
		return 0;
	}
	if (vector.size() == 0) {
		std::cout << "[Number::sum(std::vector<int>&)]: size == 0 returns:" << 0 << std::endl;
		return 0;
	}
	if (vector.size() == 1) {
		std::cout << "[Number::sum(std::vector<int>&)]: size == 0 returns:" << 0 << std::endl;
		return vector.back();
	}
	int back  = 0;
	int sum = 0;
	int mi = vector.size()/2;
	std::vector<int> v1, v2;
	v1.assign(vector.begin(), std::next(vector.begin(), mi));
	v2.assign(std::next(vector.begin(), mi), vector.end());
	std::cout << "[Number::sum(std::vector<int>&)]: v1:" << std::endl;
	for_each(v1.begin(), v1.end(), my_functor);
	std::cout << "[Number::sum(std::vector<int>&)]: v2:" << std::endl;
	for_each(v2.begin(), v2.end(), my_functor);
	sum = Number::sum(v1) + Number::sum(v2);

	return sum;
}
#endif

#if 0
/**
 * O(2^n)
 */
int amo::Number::fibonacci(int n) {
	if (n < 2) {
		std::cout << "[Number::fibonacci(int)]: n < 2 returns:" << n << std::endl;
		return n;
	} else {
		int fib = fibonacci(n-1) + fibonacci(n-2);
		std::cout << "[Number::fibonacci(int)]: n = " << n << " returns:" << fib << std::endl;
		return fib;
	}
}

#else
/**
 * O(n)
 */
int amo::Number::fibonacci(int n) {
	int g = 1; //fib(k)
	int f = 0; //fib(k-1)
	int tmp;
	int k = n-1; //pattern starts from n = 1 not 0
	while (0 < k--) {
		tmp = g + f;
		f = g;
		g = tmp;
	}
	return g;
}
#endif

/**
 * base case of recursion could be set any n with known return and prev
 * O(n)
 */
int amo::Number::fibonacci(int n, int& prev) {
	/*
	if (n == 1) {
		std::cout << "[Number::fibonacci(int)]: base case of recursion n == 1 returns:" << 1 << " and prev = 0" << std::endl;
		prev = 0;
		return 1;
    } 
	if (n == 2) {
		std::cout << "[Number::fibonacci(int)]: base case of recursion n == 2 returns:" << 1 << " and prev = 1" << std::endl;
		prev = 1;
		return 1;
    }
	*/
	if (n == 3) {
		std::cout << "[Number::fibonacci(int)]: base case of recursion n == 3 returns:" << 2 << " and prev = 1" << std::endl;
		prev = 1;
		return 2;
    } else {
		int prevprev;
		prev = fibonacci(n-1, prevprev);
		std::cout << "[Number::fibonacci(int)]: n:" << n << " returns:" << prev + prevprev << std::endl;
		return prev + prevprev;
	}
}

#if 0
void amo::Number::convert(amo::Stack<char>& stack, int n, int base) {
	static char digit[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	if (n > 0) {
		convert(stack, n/base, base);
		std::cout << "[Number::convert()]: going to push:" << digit[n%base] << std::endl;
		stack.push(digit[n%base]);
	} else std::cout << "[Number::convert()]: return and n:" << n << std::endl;
}

#else
void amo::Number::convert(amo::Stack<char>& stack, int n, int base) {
	static char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	int rmd;
	while ((rmd=n%base)>=0 && n!=0) {
		stack.push(digit[rmd]);
		n = n/base;
	}
}
#endif

void amo::Number::resolve(char* p, amo::Stack<float>& stack) {
	float factor = 10;
	float fraction = 0.1f;
	stack.push(0);
	while (isdigit(*p)) {
		std::cout << std::fixed << std::setprecision(4) << "[Number::resolve()]: integer resolving:" << *p-'0' << std::endl;
		stack.push(stack.pop()*factor+(*p-'0'));
		p++;
	}
	if ('.' != *p) return;
	else p++;
	while (isdigit(*p)) {
		std::cout << "[Number::resolve()]: fraction resolving:" << *p-'0' << ", fraction:" << fraction << ", top:" << stack.top() << std::endl;
		stack.push(stack.pop()+(*p-'0')*fraction);
		fraction /= 10;
		p++;
	}
	std::cout << "[Number::resolve()]: top of stack:" << stack.top() << std::endl;
	std::cout.unsetf( std::ios::fixed );
}

amo::Operator amo::Number::toOp(char op) {
	switch (op) {
		case '+' : return ADD;
		case '-' : return SUB;
		case '*' : return MUL;
		case '/' : return DIV;
		case '^' : return POW;
		case '!' : return FAC;
		case '(' : return L_P;
		case ')' : return R_P;
		case '\0': return EOE;
		default : exit(-1);
	}
}

#define N_OPTR 9
const char priority[N_OPTR][N_OPTR] = { 
 /*        +    -    *    /    ^    !    (    )   \0  */
 /*  + */ '>', '>', '<', '<', '<', '<', '<', '>', '>',
 /*  - */ '>', '>', '<', '<', '<', '<', '<', '>', '>',
 /*  * */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
 /*  / */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
 /*  ^ */ '>', '>', '>', '>', '>', '<', '<', '>', '>',
 /*  ! */ '>', '>', '>', '>', '>', '>', ' ', '>', '>',
 /*  ( */ '<', '<', '<', '<', '<', '<', '<', '=', ' ',
 /*  ) */ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
 /*  \0 */ '<', '<', '<', '<', '<', '<', '<', ' ', '='
 };

char amo::Number::orderOp(char op1, char op2) {
	return priority[toOp(op1)][toOp(op2)];
}

bool amo::Number::isPrior(char op1, char op2) {
	if (priority[toOp(op1)][toOp(op2)] == '>') return true;
	else return false;
}

bool amo::Number::isCal(char op) {
	if (toOp(op) <= Operator::FAC) return true;
	else return false;
}


std::vector<char> amo::Number::rePolish(std::vector<char>& infix) {
	std::vector<char> postfix;
	amo::Stack<char> stack;
	for (std::vector<char>::iterator it=infix.begin(); it!=infix.end(); it++) {
		char c = *it;
		std::cout << "[Number::rePolish()]: for-loop, c:" << c << std::endl;
		if (isdigit(c)) {
			std::cout << "[Number::rePolish()]: met a digit and pushes postfix char:" << c << std::endl;
			postfix.push_back(c);
		} else {
			if (c == '(') {
				std::cout << "[Number::rePolish()]: met a '(' and pushes stack char:" << c << std::endl;
				stack.push(c);
			} 
			else if (isCal(c)) {
				if (stack.empty()) {
					std::cout << "[Number::rePolish()]: met a cal, stack is empty and pushes stack char:" << c << std::endl;
					stack.push(c);
				} else if (stack.top() == '(') {
					std::cout << "[Number::rePolish()]: met a cal, stack top is '(' and pushes stack char:" << c << std::endl;
					stack.push(c);
				} else if (stack.top() != '(' && isPrior(c, stack.top())) {
					std::cout << "[Number::rePolish()]: met a cal, stack top is char:" << stack.top() << " which is lower prior and pushes stack char:" << c << std::endl;
					stack.push(c);
				} else if (!isPrior(c, stack.top())) {
					std::cout << "[Number::rePolish()]: met a cal, pops stack top:" << stack.top() 
							  << " which is higher prior and pushes postfix char:" << stack.top()
							  << " then pushes stack char:" << c 
							  << std::endl;
					postfix.push_back(stack.pop());
					stack.push(c);
				}
			}
			else if (c == ')') {
				while (stack.top()!='(') {
					std::cout << "[Number::rePolish()]: met a ')', pops stack top:" << stack.top() 
							  << " and pushes postfix char:" << stack.top()
							  << std::endl;
					postfix.push_back(stack.pop());
				}
				stack.pop(); //pops '(' out from stack 
			}
		}	
	}
	while(!stack.empty()) {
		std::cout << "[Number::rePolish()]: eventually pushes postfix and pops stack top:" << stack.top() << std::endl;
		postfix.push_back(stack.pop());
	}
	return postfix;
}
	
	
	
	
	
	












