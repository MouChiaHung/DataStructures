#ifndef _NUMBER_H_
#define _NUMBER_H_

#include <stdio.h>
#include <stack.h>

namespace amo {

typedef enum {ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE} Operator; 

class Number {
private:
	static Number* instance;
	Number();
	~Number();
public:
	static Number& getInstance();
	int getBinCount(int num);
	long long power2(int n);
	int akermann(int m, int n);
	int hailstone(int n);
	int sum(std::vector<int>& vector);
	int fibonacci(int n);
	int fibonacci(int n, int& prev);
	void convert(amo::Stack<char>& stack, int n, int base);
	void resolve(char* p, amo::Stack<float>& stack);
	amo::Operator toOp(char c);
	char orderOp(char op1, char op2);
	bool isPrior(char op1, char op2);
	bool isCal(char op);
	std::vector<char> rePolish(std::vector<char>& infix);
};

};
#endif