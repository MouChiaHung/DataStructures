#ifndef _QUEEN_H_
#define _QUEEN_H_

#include <stdio.h>
#include <stack.h>

namespace amo {

class Queen {
private:
	static Queen* instance;
	static int** chess; //A dynamic 2D array is basically an array of pointers to arrays. 
	Queen();
	~Queen();
public:
	static Queen& getInstance();
	void place(int probing, int n);
	bool check(int row, int column);
	void traverse();
	void traverse(int marki, int markj);
};

};
#endif