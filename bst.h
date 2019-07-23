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
	BinNode<T>* succ(BinNode<T>* node);

friend std::ostream& operator<<(std::ostream& os, const BST<T>& bst) {
	os << YELLOW << "------ BST MEMBER ------" << endl;
	//os << "[this]:" << &bst << endl;
	if (bst.root() == NULL) os << "[root]:" << "NULL" << endl;
	else os << "[root]:" << *bst.root();
	os << "[size]:" << bst.size() << endl;	
	if (bst.root() == NULL) os << "[height]:" << "NULL" << endl;
	else os << "[height]:" << bst.root()->height << endl;
	os << "------ BST MEMBER ------" << WHITE;
	return os;
}
};

template<typename T>
BinNode<T>* BST<T>::searchIn(BinNode<T>* v, T const& e, BinNode<T>*& hot) {
	if ((v == NULL) || (e == v->data)) { 
		if (v == NULL) std::cout << WHITE << "not searched:" << e << " and hot:" << *hot << WHITE;
		else {
			if (hot != NULL) std::cout << GREEN << "searched:" << e << " and hot:" << *hot << WHITE;
			else std::cout << GREEN << "searched root:" << e << " and hot:NULL" << WHITE << std::endl;
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
		std::cout << CYAN << "inserted root:" << *this->root() << WHITE;
		return this->root();
	}
	//already in as node
	if ((sentry = search(e)) != NULL) {
		std::cout << CYAN << "equivalent element:" << *sentry << WHITE;;
		return sentry;
	}
	//inserts a new node
	if (e < this->_hot->data) {
		this->insertLeftChild(this->_hot, e);
		std::cout << CYAN << "inserted lchild:" << *this->_hot->lchild << WHITE;
		return this->_hot->lchild;
	}
	else if (e > this->_hot->data){
		this->insertRightChild(this->_hot, e);
		std::cout << CYAN << "inserted rchild:" << *this->_hot->rchild << WHITE;
		return this->_hot->rchild;
	}
	else {
		std::cout << RED << __func__ << ":Exception case unknown inserting" << WHITE << std::endl;
		return NULL;
	}
}

template<typename T>
BinNode<T>* BST<T>::succ(BinNode<T>* node) {
	if (!node->hasRightChild()) return NULL;
	node = node->rchild;
	while (node->hasLeftChild())
		node = node->lchild;
	return node;
}

template<typename T>
bool BST<T>::remove(T const& e) {
	BinNode<T>* sentry = NULL;
	if ((sentry = search(e)) == NULL) {
		std::cout << CYAN << "no equivalent:" << e << WHITE << std::endl;
		return false;
	}
	BinNode<int>* replace = removeAt(sentry, this->_hot);
	if (replace != NULL) 
		cout << CYAN << "removed:" << e << " and replaced:" << *replace << WHITE;
	else 
		cout << CYAN << "removed:" << e << " and replaced:NULL" << WHITE << std::endl;
	this->_size--;
	this->updateHeightAbove(this->_hot);
	return true;
}

template<typename T>
BinNode<T>* BST<T>::removeAt(BinNode<T>* node, BinNode<T>*& hot) {
	if (node == NULL) {
		std::cout << RED << __func__ << ":Exception case removing null" << WHITE << std::endl;
		hot = NULL;
		return NULL;
	}
	BinNode<T>* replace = NULL;
	
	//replaces for single sub->tree or swaps and replaces for dual sub->tree
	if (node->hasLeftChild() && !node->hasRightChild()) { //node has single left sub->tree
		replace = node->lchild;
	}
	else if (!node->hasLeftChild() && node->hasRightChild()) { //node has single right sub->tree
		replace = node->rchild;
		
	}
	else if (node->hasLeftChild() && node->hasRightChild()) { //node has dual sub->tree
		//BinNode<T>* succ = node->succ(); //succ is the most left of the right sub->tree of node
		BinNode<T>* succ = this->succ(node); //succ is the most left of the right sub->tree of node
		if (succ == NULL) {
			std::cout << RED << __func__ << ":Exception case null succ" << WHITE << std::endl;
			hot = NULL;
			return NULL;
		}
		std::cout << YELLOW << "swap " << node->data << " and " << succ->data << WHITE << std::endl;
		std::swap(node->data, succ->data);
		hot = succ->parent; //I chose hot pointing to the parent of succ instead of parent of the node
		node = succ;
		replace = node->rchild;//most left doesn't have lchild and rchild might be null too
	}
	else if (!node->hasLeftChild() && !node->hasRightChild())  {
		replace = NULL;
	}
	else {
		std::cout << RED << __func__ << ":Exception case unknown sub-tree type" << WHITE << std::endl;
		hot = NULL;
		return NULL;
	}
	
	//reconnects tree and deletes node
	if (hot != NULL) { //case of deleting node
		if (hot->lchild == node)
			hot->lchild = replace;
		else if (hot->rchild == node)
			hot->rchild = replace;
		else {
			std::cout << RED << __func__ << ":Exception case neither left nor right" << WHITE << std::endl;
			hot = NULL;
			return NULL;
		}
	}
	else { //case of deleting root
		if (this->_root->isLeaf()) { 
			std::cout << YELLOW << "delete the last:" << node->data << WHITE << std::endl;
			this->_root = NULL;
		}
		else {
			std::cout << YELLOW << "delete root:" << node->data << " and replace:" << replace->data << WHITE << std::endl;
			this->_root = replace;
		}
	}
	if (replace != NULL) replace->parent = hot;
	delete node;
	return replace;
}










};

#endif