#ifndef _BIN_TREE_H_
#define _BIN_TREE_H_

#include <iostream>

#include <stdio.h>
#include <stack.h>
#include <map>
#include <typeinfo> 

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
	void operator() (BinNode<T> const& node) {
		std::cout << node;
	}
} FUNCTOR_TRAVERSER;
private:
	
protected:
	int _size; //0 if root is null
	BinNode<T>* _root;
public:
	BinTree() : _size(0), _root(NULL) {}
	BinTree(BinNode<T>* node) : _size(node->height), _root(node) {}
	~BinTree() {
		if (0<size() && _root!=NULL) remove(_root);
	}
	
	int size() const { return _size; }
	bool empty() const { return !_root;};
	BinNode<T>* root() const { return _root; }
	
	bool operator<(const BinTree<T>& tree) { return (_root && tree.root() && _root<*tree.root()); }
	bool operator==(const BinTree<T>& tree) { return (_root && tree.root() && _root==*tree.root()); }
	BinTree<T>& operator=(const BinTree& c);
	
	BinNode<T>* insertRoot(const T& t);
	BinNode<T>* insertLeftChild(BinNode<T>* node, const T& t);
	BinNode<T>* attachLeftChild(BinNode<T>* node, BinTree<T>* &tree);
	BinNode<T>* insertRightChild(BinNode<T>* node, const T& t);
	BinNode<T>* attachRightChild(BinNode<T>* node, BinTree<T>* &tree);
	
	int remove(BinNode<T>* node);
	BinTree<T>* secede(BinNode<T>* node);
	int removeTree(BinNode<T>* node);
	
	void traverse();
	void traverse(FUNCTOR_TRAVERSER& functor);
	void traverseLevel();
	void traversePre();
	void traverseIn();
	void traversePost();

	virtual int updateHeight(BinNode<T>* node);
	void updateHeightAbove(BinNode<T>* node);
	void updateHeightAll();
	
friend std::ostream& operator<<(std::ostream& os, const BinTree<T>& tree) {
	return os;
}

};

template<typename T>
int amo::BinTree<T>::updateHeight(BinNode<T>* node) {
	if (node->isLeaf()) {
		node->height = 0;
		return node->height;
	}
	else {
		BinNode<T>* lchild = node->lchild;
		BinNode<T>* rchild = node->rchild;
		if (lchild && rchild) node->height = 1 + std::max(lchild->height, rchild->height);
		else if (lchild && rchild == NULL) node->height = 1 + lchild->height;
		else if (rchild && lchild == NULL) node->height = 1 + rchild->height;
		else {
			std::cout << RED << "Exception of " << __func__ << WHITE << std::endl;
			node->height = -1;
		}
		return node->height;
	}
}

template<typename T>
void amo::BinTree<T>::updateHeightAbove(BinNode<T>* node) {
	while (node!=NULL) {
		updateHeight(node);
		node = node->parent;
	}
}

template<typename T>
void amo::BinTree<T>::updateHeightAll() {
	std::queue<BinNode<T>*> queue;
	BinNode<T>* node = _root;
	queue.push(node);
	while (true) {
		if (queue.empty()) break;
		node = queue.front();
		queue.pop();
		if (node->isLeaf()) updateHeightAbove(node);
		if (node->hasLeftChild()) queue.push(node->lchild);
		if (node->hasRightChild()) queue.push(node->rchild);
	}
}

template<typename T>
BinNode<T>* amo::BinTree<T>::insertRoot(T const& t) {
	BinNode<T>* r = new BinNode<T>(t);
	_root = r;
	_size = 1;
	return r;
}

template<typename T>
BinNode<T>* amo::BinTree<T>::insertLeftChild(BinNode<T>* node, const T& t) {
	BinNode<T>* insert = node->insertLeftChild(t);
	updateHeightAbove(node);
	_size++;
	return insert;
}

template<typename T>
BinNode<T>* amo::BinTree<T>::insertRightChild(BinNode<T>* node, const T& t) {
	BinNode<T>* insert = node->insertRightChild(t);
	updateHeightAbove(node);
	_size++;
	return insert;
}

template<typename T>
BinNode<T>* amo::BinTree<T>::attachLeftChild(BinNode<T>* node, BinTree<T>* &tree) {
	if (tree->root == NULL) goto NO_ROOT_AL;
	node->lchild = tree->root();
	tree->parent = node;
	size += tree->size();
	updateHeightAbove(node);
NO_ROOT_AL:	
	tree->_root = NULL;
	tree->_size = 0;
	//release(tree);
	tree = NULL;
	return node;
}

template<typename T>
BinNode<T>* amo::BinTree<T>::attachRightChild(BinNode<T>* node, BinTree<T>* &tree) {
	if (tree->root == NULL) goto NO_ROOT_AR;
	node->rchild = tree->root;
	tree->parent = node;
	size += tree->size();
	updateHeightAbove(node);
NO_ROOT_AR:
	tree->_root = NULL;
	tree->_size = 0;
	tree = NULL;
	return node;
}

template<typename T>
int amo::BinTree<T>::removeTree(BinNode<T>* node) {
	int removed = 0;
	if (node == NULL) return 0;
	if (node->isLeaf()) {
		cout << "delete leaf:" << *node;
		delete node;
		removed++;
		return removed;
	}
	else { //removes in the post-order
		if (node->hasLeftChild()) { 
		
			removed += removeTree(node->lchild);
		}
		if (node->hasRightChild()) { 
			removed += removeTree(node->rchild);
		}
		cout << "delete vertex:" << *node;
		delete node;
		removed++;
		return removed;
	}
}

template<typename T>
int amo::BinTree<T>::remove(BinNode<T>* node) {
	if (!node->isRoot()) { 
		node->parentLink() = NULL;
		updateHeightAbove(node->parent);
	}
	int removed_count = removeTree(node);
	_size -= removed_count;
	return removed_count;
}

template<typename T>
BinTree<T>* amo::BinTree<T>::secede(BinNode<T>* node) {
	if (!node->isRoot()) {
		node->parentLink() = NULL;
		updateHeightAbove(node->parent);
		node->parent = NULL;
	}
	BinTree<T>* sub_tree = new BinTree(node);
	_size -= sub_tree->size();
	return sub_tree;
}

template<typename T>
void amo::BinTree<T>::traverse() {
	_root->traverse();
}

template<typename T>
void amo::BinTree<T>::traversePre() {
	_root->traversePre();
}

template<typename T>
void amo::BinTree<T>::traverseIn() {
	_root->traverseIn();
}

template<typename T>
void amo::BinTree<T>::traversePost() {
	_root->traversePost();
}

template<typename T>
void amo::BinTree<T>::traverseLevel() {
	_root->traverseLevel();
}
};
#endif