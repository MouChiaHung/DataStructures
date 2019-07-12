#include <stdio.h>
#include <vector>
using namespace std;
int main(int argc,char **argv)
{
	vector<int> tab;
	tab.push_back(100);
	tab.push_back(101);
	tab.push_back(102);
	for(int i=0;i<3;i++){
		printf("%d ",tab[i]);
	}
	printf("\n");
	return 0;
}