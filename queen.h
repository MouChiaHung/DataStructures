#ifndef _QUEEN_H_
#define _QUEEN_H_

#include <stdio.h>
#include <stack.h>
#include <map>


namespace amo {

class Queen {
private:
	static Queen* instance;
	Queen();
	~Queen();
public:
	static Queen& getInstance();
	int answer();
	void place(int probing, int n);
	bool check(int row, int column);
	void traverse();
	void traverse(int marki, int markj);
	void traverse(std::map<int,int>& map);
};

};
#endif