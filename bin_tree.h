#ifndef _BIN_TREE_H_
#define _BIN_TREE_H_

#include <iostream>

#include <stdio.h>
#include <stack.h>
#include <map>

#include <bin_node.h>

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
class BinTree { 
typedef struct functor_traverse {
	void operator() (BinTree<T> const& tree) {
		std::cout << tree << WHITE << std::endl;
	}
} FUNCTOR_TRAVERSER;
private:
	int _size; //0 if root is null
	BinTree<T>* _root;
public:
	BinTree() : _size(0), _root(NULL) {
		std::cout << "[BinTree::~BinTree()]: this:" << this << WHITE << std::endl;
	}
	~BinTree() {
		std::cout << "[BinTree::~BinTree()]: size:" << _size << WHITE << std::endl;
		if (0<size) remove(_root);
	}
	
	int size() const { return _size; }
	bool empty() const { return !_root;};
	BinTree<T>* root() const { return _root; }
	
	bool operator<(const BinTree<T>& tree) { return (_root && tree.root() && _root<*tree.root()); }
	bool operator==(const BinTree<T>& tree) { return (_root && tree.root() && _root==*tree.root()); }
	BinTree<T>& operator=(const BinTree& c);
	
	BinNode<T> insertRoot(const T& t);
	BinNode<T> insertLeftChild(BinNode<T>* node, const T& t);
	BinNode<T>* attachLeftChild(BinNode<T>* node, BinTree<T>* &tree);
	BinNode<T> insertRightChild(BinNode<T>* node, const T& t);
	BinNode<T>* attachRightChild(BinNode<T>* node, BinTree<T>* &tree);
	
	int remove(BinNode<T>* node);
	BinTree<T>* secede(BinNode<T>* node);
	
	void traverse();
	void traverseLevel();
	void traversePre();
	void traverseIn();
	void traversePost();

	virtual int updateHeight(BinNode<T>* node);
	void updateHeightAbove(BinNode<T>* node);
	
friend std::ostream& operator<<(std::ostream& os, const BinTree<T>& tree) {
	os  << WHITE << "[this]:" << &tree << endl;
	os  << WHITE << "[root]:" << tree.root << endl;
	os  << WHITE << "[size]:" << tree.size << endl;
	return os;
}

};

template<typename T>
int amo::BinTree<T>::updateHeight(BinNode<T>* node) {
	BinNode<T>* lchild = node->lchild;
	BinNode<T>* rchild = node->rchild;
	return node->height = 1+std::max(lchild->stature(), rchild->stature());
}

template<typename T>
void amo::BinTree<T>::updateHeightAbove(BinNode<T>* node) {
	while (node) {
		updateHeight(node);
		node = node->parent;
	}
}

template<typename T>
BinNode<T> amo::BinTree<T>::insertRoot(T const& t) {
	BinNode<T> r(t);
	_root = &r;
	_size = 1;
	return r;
}


template<typename T>
BinNode<T> amo::BinTree<T>::insertLeftChild(BinNode<T>* node, const T& t) {
	BinNode<T> insert = node->insertLeftChild(t);
	updateHeightAbove(node);
	size++;
	return insert;
}

template<typename T>
BinNode<T> amo::BinTree<T>::insertRightChild(BinNode<T>* node, const T& t) {
	BinNode<T> insert = node->insertRightChild(t);
	updateHeightAbove(node);
	size++;
	return insert;
}

template<typename T>
BinNode<T>* amo::BinTree<T>::attachLeftChild(BinNode<T>* node, BinTree<T>* &tree) {
	if (tree->root == NULL) goto NO_ROOT_AL;
	node->lchild = tree->root();
	tree->parent = node;
	size += tree->size();
	updateHeightAbove(node);
NO_ROOT:	
	tree->_root = NULL;
	tree->_size = 0;
	//release(tree);
	tree = NULL;
	return node;
}

template<typename T>
BinNode<T>* amo::BinTree<T>::attachRightChild(BinNode<T>* node, BinTree<T>* &tree) {
	if (tree->root == NULL) goto NO_ROOT_AR;
	node->rchild = tree;
	tree->parent = node;
	size += tree->size();
	updateHeightAbove(node);
NO_ROOT_AR:
	tree->_root = NULL;
	tree->_size = 0;
	tree = NULL;
	return node;
}





};
#endif