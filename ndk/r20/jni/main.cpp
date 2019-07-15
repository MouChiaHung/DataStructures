#include <stdio.h>
#include <vector>
#include "bin_node.h"
#include "android_buf.h"

using namespace std;
using namespace amo;
int main(int argc,char **argv)
{	
	printf("****************** tree node ******************\n");
 
#if 1
	amo::BinNode<int> root(0);
	amo::BinNode<int>* lchild1 = root.insertLeftChild(1);
	amo::BinNode<int>* rchild2 = root.insertRightChild(2);
	amo::BinNode<int>* lchild3 = lchild1->insertLeftChild(3);
	amo::BinNode<int>* rchild4 = lchild1->insertRightChild(4);
	amo::BinNode<int>* lchild5 = rchild2->insertLeftChild(5);
	amo::BinNode<int>* rchild6 = rchild2->insertRightChild(6);
	amo::BinNode<int>* lchild7 = lchild3->insertLeftChild(7);
	amo::BinNode<int>* rchild8 = lchild3->insertRightChild(8);
	amo::BinNode<int>* lchild9 = rchild6->insertLeftChild(9);
	amo::BinNode<int>* rchild10 = rchild6->insertRightChild(10);
	amo::BinNode<int>* lchild11 = rchild8->insertLeftChild(11);
	amo::BinNode<int>* rchild12 = rchild8->insertRightChild(12);
	
#if 1
	printf("going to root.traversePre()\n");
	root.traversePre();
	printf("going to root.traversePreLoop()\n");
	root.traversePreLoop();
	printf("going to root.traversePreLoop2()\n");
	root.traversePreLoop2();
#elif 0
	printf("going to root.traverseIn()\n");
	root.traverseIn();
	printf("going to root.traverseInLoop()\n");
	root.traverseInLoop();
	printf("going to root.traverseInLoop2()\n");
	root.traverseInLoop2();
	printf("going to root.traverseInLoop3()\n");
	root.traverseInLoop3();
#elif 0
	printf("going to root.traversePost()\n");
	root.traversePost();
	root.traversePostLoop();
#elif 0
	printf("going to root.traverseLevel()\n");
	root.traverseLevel();
#else
#endif
	printf("\n****************** main return ******************\n");
	return 0;
#endif	
	return 0;
}