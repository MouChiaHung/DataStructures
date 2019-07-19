#ifndef _BIN_SEARCH_TREE_H_
#define _BIN_SEARCH_TREE_H_

#include <iostream>
#include <stdio.h>
#include <typeinfo> 

#include <bin_node.h>
#include <bin_tree.h>

namespace amo {

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

template<typename T>
class BST : public BinTree<T> {
protected:	
	BinNode<T>* _hot;
	BinNode<T>* connect34(BinNode<T>*, BinNode<T>*, BinNode<T>*, 
						  BinNode<T>*, BinNode<T>*, BinNode<T>*, BinNode<T>*);
public:
	BST() : BinTree<T>() {}
	BST(BinNode<T>* node) : BinTree<T>(node) {}
	BinNode<T>*& search(T const& e);
	BinNode<T>*& searchIn(BinNode<T>*& v, T const& e, BinNode<T>*& hot);
	BinNode<T>* insert(T const& e);
	bool remove(T const& e);

friend std::ostream& operator<<(std::ostream& os, const BST<T>& bst) {
	return os;
}
};

template<typename T>
BinNode<T>*& BST<T>::searchIn(BinNode<T>*& v, T const& e, BinNode<T>*& hot) {
	if ((v == NULL) || (e == v->data)) { 
		if (v == NULL) std::cout << RED << "no searched:" << e << std::endl;
		else std::cout << GREEN << "searched:" << e << std::endl;
		return v;
	}
	hot = v;
	return searchIn(((e < v->data)?(v->lchild):(v->rchild)), e, hot);
}


template<typename T>
BinNode<T>*& BST<T>::search(T const& e) {
	return searchIn(this->_root, e, (this->_hot)=NULL);
}













};

#endif