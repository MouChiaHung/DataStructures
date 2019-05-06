#ifndef _BIN_NODE_H_
#define _BIN_NODE_H_

#include <iostream>

#include <stdio.h>
#include <stack.h>
#include <map>

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

typedef enum {RB_RED, RB_BLACK} RB_COLOR;

template<typename T>
class BinNode { 
typedef struct functor_traverse {
	void operator() (BinNode<T> const& node) {
		std::cout << node << WHITE << std::endl;
	}
} FUNCTOR_TRAVERSER;
private:
	T data;
	RB_COLOR color;
	int height;
	int npl;
	BinNode<T>* parent;
	BinNode<T>* lchild;
	BinNode<T>* rchild;
public:
	BinNode() : height(0), npl(1), color(RB_RED), parent(NULL), lchild(NULL), rchild(NULL) {}
	BinNode(const T& e, BinNode<T>* p=NULL, BinNode<T>* lc=NULL, BinNode<T>* rc=NULL, int h=0, int l=1, RB_COLOR c=RB_RED) : 
		data(e), parent(p), lchild(lc), rchild(rc), height(h), npl(l), color(c) {
			std::cout << "[BinNode::BinNode(T&)]: data:" << e << WHITE << std::endl;
		}
	~BinNode() {
		std::cout << "[BinNode::~BinNode()]: data:" << data << WHITE << std::endl;
	}
	BinNode<T> insertLeftChild(const T& t);
	BinNode<T> insertRightChild(const T& t);
	BinNode<T>* succ();
	int stature() { return height; }
	int size();
	bool operator<(const BinNode<T>& n);
	bool operator==(const BinNode<T>& c);
	BinNode<T>& operator=(const BinNode& c);
	void traverse();
	void traverseLevel();
	void traversePre();
	void traverseIn();
	void traversePost();
	bool isRoot();
	bool isLeftChild();
	bool isRightChild();
	bool isLeaf();
	bool hasParent();
	bool hasChild();
	bool hasBothChild();
	bool hasLeftChild();
	bool hasRightChild();
	BinNode<T>* sibling();
	BinNode<T>* uncle();
	BinNode<T>* fromParentTo();
	
//friend std::istream& operator>>(std::istream& is, BinNode<T>& node);
friend std::ostream& operator<<(std::ostream& os, const BinNode<T>& node) {
	os  << WHITE << "[this]:" << &node << endl;
	os  << WHITE << "[data]:" << node.data << endl;
	os  << WHITE << "[height]:" << node.height << endl;
	os  << WHITE << "[npl]:" << node.npl << endl;
	//if (node.parent!=NULL) os << WHITE << "parent:" << *(node.parent) << endl;
	//if (node.lchild!=NULL) os << WHITE << "lchild:" << *(node.lchild) << endl;
	//if (node.rchild!=NULL) os << WHITE << "rchild:" << *(node.rchild) << endl;
	return os;
}
class BinTree;
friend class BinTree;
};

#if 0
template<typename T>
void amo::BinNode<T>::traverse() {
	FUNCTOR_TRAVERSER functor;
	if (isRoot()) std::cout << "[BinNode::traverseLevel()]: --- TREE BOTTOM ------" << WHITE << std::endl;
	if (isLeaf()) {
		std::cout << GREEN << "leaf" << WHITE << std::endl;
		functor(*this);
	} else {
		lchild->traverse();
		rchild->traverse();
		std::cout << GREEN << "vertex" << WHITE << std::endl;
		functor(*this);
	}
	if (isRoot()) std::cout << "[BinNode::traverseLevel()]: --- TREE TOP ------" << WHITE << std::endl;
}
#else
template<typename T>
void amo::BinNode<T>::traverse() {
	FUNCTOR_TRAVERSER functor;
	if (isRoot()) std::cout << "[BinNode::traverseLevel()]: --- TREE TOP ------" << WHITE << std::endl;
	if (isLeaf()) {
		std::cout << GREEN << "leaf" << WHITE << std::endl;
		functor(*this);
	} else {
		std::cout << GREEN << "vertex" << WHITE << std::endl;
		functor(*this);
		lchild->traverse();
		rchild->traverse();
	}
	if (isRoot()) std::cout << "[BinNode::traverseLevel()]: --- TREE BOTTOM ------" << WHITE << std::endl;
}
#endif

template<typename T>
bool amo::BinNode<T>::isRoot() {
	return !parent ? true : false;
}

template<typename T>
bool amo::BinNode<T>::isLeftChild() {
	if (!isRoot()) {
		if (this == parent->lchild) return true;
		return false;
	}
	else return false;
}

template<typename T>
bool amo::BinNode<T>::isRightChild() {
	if (!isRoot()) {
		if (this == parent->rchild) return true;
		return false;
	}
	else return false;
}

template<typename T>
bool amo::BinNode<T>::isLeaf() {
	return !hasChild();
}

template<typename T>
bool amo::BinNode<T>::hasParent() {
	return parent ? true : false;
}

template<typename T>
bool amo::BinNode<T>::hasChild() {
	return hasLeftChild() || hasRightChild();
}

template<typename T>
bool amo::BinNode<T>::hasBothChild() {
	return hasLeftChild() && hasRightChild();
}

template<typename T>
bool amo::BinNode<T>::hasLeftChild() {
	return lchild ? true : false;
}

template<typename T>
bool amo::BinNode<T>::hasRightChild() {
	return rchild ? true : false;
}

template<typename T>
BinNode<T>* amo::BinNode<T>::sibling() {
	if (isLeftChild()) {
		return parent->rchild;
	}
	else {
		return parent->lchild;
	}
}

template<typename T>
BinNode<T>* amo::BinNode<T>::uncle() {
	if (parent->isLeftChild()) {
		return parent->parent->rchild;
	}
	else {
		return parent->parent->lchild;
	}
}

template<typename T>
BinNode<T>* amo::BinNode<T>::fromParentTo() {
	if (isRoot()) {
		return this;
	}
	else {
		if (isLeftChild()) return parent->lchild; 
		else return parent->rchild;
	}
}

//NRVO
template<typename T> 
BinNode<T> amo::BinNode<T>::insertLeftChild(const T& t) {
	BinNode<T> child(t, this);
	lchild = &child;
	return child;
}

template<typename T>
BinNode<T> amo::BinNode<T>::insertRightChild(const T& t) {
	BinNode<T> child(t, this);
	rchild = &child;
	return child;
}











};
#endif