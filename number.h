#ifndef _NUMBER_H_
#define _NUMBER_H_

#include <stdio.h>
#include <stack.h>

namespace amo {

typedef enum {ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE, ERROR} Operator; 

class Number {
private:
	static Number* instance;
	Number();
	~Number();
	amo::Operator toOp(char c);
	char orderOp(char op1, char op2);
	bool isPrior(char op1, char op2);
	bool isCal(char op);
	int calculate(int arg, char op);
	int calculate(int arg1, int arg2, char op);
public:
	static Number& getInstance();
	int getBinCount(int num);
	long long power2(int n);
	long long power(int base, int n);
	int akermann(int m, int n);
	int hailstone(int n);
	int sum(std::vector<int>& vector);
	int factory(int n);
	int fibonacci(int n);
	int fibonacci(int n, int& prev);
	void resolve(char* p, amo::Stack<float>& stack);
	std::vector<char> rePolish(std::vector<char>& infix);
	int evaluate(char* rpn);
};

};
#endif