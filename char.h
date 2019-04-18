#ifndef _CHAR_H_
#define _CHAR_H_

#include <stdio.h>
#include <stack.h>

namespace amo {

class Char {
private:
	static Char* instance;
	Char();
	~Char();
public:
	static Char& getInstance();
	void trim(const char exp[], int& lo, int& hi);
	int divide(const char exp[], int lo, int hi);
	bool paren(const char exp[], int begin, int end);
	bool paren(const char exp[], int len);
	void append(char* exp, char optr);
	void append(char* exp, int opnd);
	void convert(amo::Stack<char>& stack, int n, int base);
	void convert(char* dest, int n, int base);
	void resolve(char* p, amo::Stack<float>& stack);
};

};
#endif