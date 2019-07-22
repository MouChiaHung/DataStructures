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
	BinNode<T>* _hot; //like a global variable living with bst object
	BinNode<T>* connect34(BinNode<T>*, BinNode<T>*, BinNode<T>*, 
						  BinNode<T>*, BinNode<T>*, BinNode<T>*, BinNode<T>*);
public:
	BST() : BinTree<T>() {}
	BST(BinNode<T>* node) : BinTree<T>(node) {}
	~BST() {}
	BinNode<T>* search(T const& e);
	BinNode<T>* searchIn(BinNode<T>* v, T const& e, BinNode<T>*& hot);
	BinNode<T>* insert(T const& e);
	bool remove(T const& e);
	BinNode<T>* removeAt(BinNode<T>* node, BinNode<T>*& hot);

friend std::ostream& operator<<(std::ostream& os, const BST<T>& bst) {
	os << CYAN;
	os << "[this]:" << &bst << endl;
	if (bst.root() == NULL) os << "[root]:" << "NULL" << endl;
	else os << "[root]:" << *bst.root();
	os << "[size]:" << bst.size() << endl;	
	os << "[height]:" << bst.root()->height << endl;
	os << WHITE;
	return os;
}
};

template<typename T>
BinNode<T>* BST<T>::searchIn(BinNode<T>* v, T const& e, BinNode<T>*& hot) {
	if ((v == NULL) || (e == v->data)) { 
		if (v == NULL) std::cout << YELLOW << "no:" << e << ", [hot]:" << *(this->_hot) << WHITE;
		else {
			if ((this->_hot)!=NULL) std::cout << CYAN << "searched:" << e << ", [hot]:" << *(this->_hot) << WHITE;
			else std::cout << CYAN << "searched:" << e << " (root), [hot]:NULL" << WHITE << std::endl;
		}
		return v;
	}
	hot = v;
	return searchIn(((e < v->data)?(v->lchild):(v->rchild)), e, hot);
}


template<typename T>
BinNode<T>* BST<T>::search(T const& e) {
	return searchIn(this->root(), e, (this->_hot)=NULL);
}

template<typename T>
BinNode<T>* BST<T>::insert(T const& e) {
	BinNode<T>* sentry = NULL;
	//first one to be the root
	if (this->empty()) {
		this->insertRoot(e);
		std::cout << "inserted root:" << *this->root();
		return this->root();
	}
	//already in as node
	if ((sentry = search(e)) != NULL) {
		std::cout << "equivalent element:" << *sentry;
		return sentry;
	}
	//inserts a new node
	if (e < this->_hot->data) {
		this->insertLeftChild(this->_hot, e);
		std::cout << "inserted lchild:" << *this->_hot->lchild;
		return this->_hot->lchild;
	}
	else if (e > this->_hot->data){
		this->insertRightChild(this->_hot, e);
		std::cout << "inserted rchild:" << *this->_hot->rchild;
		return this->_hot->rchild;
	}
	else {
		std::cout << RED << "Exception of " << __func__ << WHITE << std::endl;
		return NULL;
	}
}

template<typename T>
bool BST<T>::remove(T const& e) {
	BinNode<T>* sentry = NULL;
	if ((sentry = search(e)) == NULL) {
		std::cout << "no:" << e << std::endl;
		return false;
	}
	BinNode<int>* replace = removeAt(sentry, this->_hot);
	if (replace != NULL) cout << "removed element:" << e << " and replaced with element:" << *replace;
	else cout << "removed element:" << e << " and replaced with element NULL" << std::endl;
	this->_size--;
	this->updateHeightAbove(this->_hot);
	return true;
}

template<typename T>
BinNode<T>* BST<T>::removeAt(BinNode<T>* node, BinNode<T>*& hot) {
	if (node == NULL) {
		std::cout << RED << "Exception case 1 of " << __func__ << WHITE << std::endl;
		hot = NULL;
		return NULL;
	}
	BinNode<T>* replace = NULL;
	
	//replace or swap and replace
	if (node->hasLeftChild() && !node->hasRightChild()) { //node has single left sub->tree
		replace = node->lchild;
	}
	else if (!node->hasLeftChild() && node->hasRightChild()) { //node has single right sub->tree
		replace = node->rchild;
		
	}
	else if (node->hasLeftChild() && node->hasRightChild()) { //node has dual sub->tree
		BinNode<T>* succ = node->succ(); //succ is the most left of the right sub->tree of node
		std::swap(node->data, succ->data);
		hot = succ->parent;
		node = succ;
		replace = node->rchild;//most left doesn't have lchild
		std::cout << "node:" << *node;
		std::cout << "hot:" << *hot;
		if (replace != NULL) std::cout << "replace:" << *replace;
		else std::cout << "replace:" << "NULL" << std::endl;
	}
	else {
		std::cout << RED << "Exception case 2 of " << __func__ << WHITE << std::endl;
		hot = NULL;
		return NULL;
	}
	
	//update tree and delete node
	if (replace == NULL) {
		if (hot->lchild == node) { //node is lchild
		hot->lchild = replace;
		}
		else if (hot->rchild == node){ //node is rchild
			hot->rchild = replace;
		}
		else {
			std::cout << RED << "Exception case 3 of " << __func__ << WHITE << std::endl;
			hot = NULL;
			return NULL;
		}
		delete node;
		return replace;
	}
	
	if (hot->lchild == node) { //node is lchild
		hot->lchild = replace;
		replace->parent = hot;
	}
	else if (hot->rchild == node){ //node is rchild
		hot->rchild = replace;
		replace->parent = hot;
	}
	else {
		std::cout << RED << "Exception case 4 of " << __func__ << WHITE << std::endl;
		hot = NULL;
		return NULL;
	}
	delete node;
	return replace;
}





};

#endif