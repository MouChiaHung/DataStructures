#ifndef _MOVE_H_
#define _MOVE_H_

#include <stdio.h>
#include <stack>

namespace amo {

class Move {
private:
	static Move* instance;
	Move();
	~Move();
public:
	static Move& getInstance();
	void hanoi(int n, std::stack<int>& from, std::stack<int>& buffer, std::stack<int>& to);
};

};
#endif