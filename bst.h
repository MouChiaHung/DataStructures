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
	
	static int stature(BinNode<T>* node) { //leaf:0, null:-1
		return (node != NULL) ? node->height : -1;
	}
	static BinNode<T>* tallerChild(BinNode<T>* node) {
		if (BST<T>::stature(node->lchild) > BST<T>::stature(node->rchild)) {
			return node->lchild;
		}
		else if (BST<T>::stature(node->lchild) < BST<T>::stature(node->rchild)) {
			return node->rchild;
		}
		else if (BST<T>::stature(node->lchild) == BST<T>::stature(node->rchild)) {
			return node->isLeftChild() ? node->lchild : node->rchild;
		}
		else return NULL;
	}

friend std::ostream& operator<<(std::ostream& os, const BST<T>& bst) {
	os << YELLOW << "\n------ BST MEMBER ------" << endl;
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
class AVL : public BST<T> {
public:
	//BinNode<T>* insert(T const& e);
	//bool remove(T const& e);
	bool balance(BinNode<T>* node) {
		if (node == NULL) return false;
		return (BST<T>::stature(node->lchild) == BST<T>::stature(node->rchild)); 
	};
	bool balanceAVL(BinNode<T>* node) {
		if (node == NULL) return false;
		return  (BST<T>::stature(node->lchild) - BST<T>::stature(node->rchild)) < 2
				&& (BST<T>::stature(node->lchild) - BST<T>::stature(node->rchild)) > -2; 
	};
	int balanceFactor(BinNode<T>* node) {
		if (node == NULL) {
			std::cout << RED << __func__ << ":Exception case balance factor of null" << WHITE << std::endl;
			return -(std::numeric_limits<int>::max());
		}
		return (BST<T>::stature(node->lchild) - BST<T>::stature(node->rchild));
	}
	BinNode<T>* connect34(BinNode<T>* a, BinNode<T>* b, BinNode<T>* c, BinNode<T>* T0, BinNode<T>* T1, BinNode<T>* T2, BinNode<T>* T3);
	BinNode<T>* rotateGPV(BinNode<T>* v);
	BinNode<T>* insert(T const& e);
};

template<typename T>
BinNode<T>* BST<T>::searchIn(BinNode<T>* v, T const& e, BinNode<T>*& hot) {
	if ((v == NULL) || (e == v->data)) { 
		if (v == NULL) { 
			//std::cout << YELLOW << "not searched:" << e << " and hot:" << *hot << WHITE;
		}
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
	return (this->empty()) ? NULL : searchIn(this->root(), e, (this->_hot)=NULL);
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

template<typename T>
BinNode<T>* amo::AVL<T>::connect34(BinNode<T>* a, BinNode<T>* b, BinNode<T>* c, BinNode<T>* T0, BinNode<T>* T1, BinNode<T>* T2, BinNode<T>* T3) {
	if (a == NULL || b == NULL || c == NULL) {
		std::cout << RED << __func__ << ":Exception case null a or b or c" << WHITE << std::endl;
		return NULL;
	}
	
	//print
	std::string str;
	char abc[32];
	char tmp[16];
	sprintf(abc, "a:%d, b:%d, c:%d", a->data, b->data, c->data);
	str.append(abc);
	if (T0) {
		sprintf(tmp, ", T0:%d", T0->data);
		str.append(tmp);
	}
	else {
		sprintf(tmp, ", T0:NULL");
		str.append(tmp);
	}
	if (T1) {
		sprintf(tmp, ", T1:%d", T1->data);
		str.append(tmp);
	}
	else {
		sprintf(tmp, ", T1:NULL");
		str.append(tmp);
	}
	if (T2) {
		sprintf(tmp, ", T2:%d", T2->data);
		str.append(tmp);
	}
	else {
		sprintf(tmp, ", T2:NULL");
		str.append(tmp);
	}
	if (T3) {
		sprintf(tmp, ", T3:%d", T3->data);
		str.append(tmp);
	}
	else {
		sprintf(tmp, ", T3:NULL");
		str.append(tmp);
	}
	std::cout << YELLOW << str << std::endl;
	
	//connect
	a->lchild = T0;
	a->rchild = T1;
	if (T0) T0->parent = a;
	if (T1) T1->parent = a;
	c->lchild = T2;
	c->rchild = T3;
	if (T2) T2->parent = c;
	if (T3) T3->parent = c;
	a->parent = b;
	c->parent = b;
	b->lchild = a;
	b->rchild = c;
	this->updateHeight(a);
	this->updateHeight(c);
	this->updateHeight(b); //should be last to update its height
	return b;
}

template<typename T>
BinNode<T>* amo::AVL<T>::rotateGPV(BinNode<T>* v) {
	BinNode<T>* p = v->parent;
	BinNode<T>* g = p->parent;
	BinNode<T>* b;
	std::string str;
	char c[32];
	sprintf(c, "g:%d, p:%d, v:%d", g->data, p->data, v->data);
	str.append(c);
	if (p->isLeftChild()) {
		if (v->isLeftChild()) { //LL
			str.append(", AVL case LL ");
			std::cout << YELLOW << str << WHITE << std::endl;
			b = this->connect34(v, p, g, v->lchild, v->rchild, p->rchild, g->rchild);			
		}
		else { //LR
			str.append(", AVL case LR ");
			std::cout << YELLOW << str << WHITE << std::endl;
			b = this->connect34(p, v, g, p->lchild, v->lchild, v->rchild, g->rchild);
		}
	}
	else { //RR
		if (v->isRightChild()) {
			str.append(", AVL case RR ");
			std::cout << YELLOW << str << WHITE << std::endl;
			b = this->connect34(g, p, v, g->lchild, p->lchild, v->lchild, v->rchild);
		}
		else { //RL
			str.append(", AVL case RL ");
			std::cout << YELLOW << str << WHITE << std::endl;
			b = this->connect34(g, v, p, g->lchild, v->lchild, v->rchild, p->rchild);
		}
	}
	std::cout << YELLOW << "------ 3 + 4 balanced sub-tree top ------" << WHITE << std::endl;
	b->traverseLevel();
	std::cout << YELLOW << "------ 3 + 4 balanced sub-tree bottom ------" << WHITE << std::endl;
	return b;
}

template<typename T>
BinNode<T>* AVL<T>::insert(T const& e) {
	BinNode<T>* sentry = NULL;
	//first one to be the root
	if (this->empty()) {
		this->insertRoot(e);
		std::cout << CYAN << "AVL inserted root:" << *this->root() << WHITE;
		return this->root();
	}
	//already in as node
	if ((sentry = this->search(e)) != NULL) {
		std::cout << CYAN << "AVL equivalent element:" << *sentry << WHITE;;
		return sentry;
	}
	//inserts a new node
	BinNode<T>* x = new BinNode<T>(e, this->_hot);
	if (x->data < this->_hot->data) {
		this->_hot->lchild = x;
	}
	else if (x->data > this->_hot->data){
		this->_hot->rchild = x;
	}
	else {
		std::cout << RED << __func__ << ":Exception case unknown AVL inserting" << WHITE << std::endl;
		return NULL;
	}
	//checks if need to AVL balance
	std::cout << CYAN << "Check if AVL balance at insert:" << x->data << " (parent:" << x->parent->data << ")" << WHITE << std::endl;
	sentry = x;
	while (sentry) {
		if (!(this->balanceAVL(sentry))) { //met the deepest unbalanced g
			if (sentry->parent == NULL) { //g is root
				std::cout << CYAN << "AVL rotate at ROOT g:" << sentry->data << WHITE << endl;
				BinNode<T>* b = this->rotateGPV(BST<T>::tallerChild(BST<T>::tallerChild(sentry)));		
				b->parent = NULL;
				this->_root = b;
			}
			else { //g is node
				std::cout << CYAN << "AVL rotate at VERTEX g:" << sentry->data << WHITE << endl;
				BinNode<T>*& hot_link = sentry->parentLink();
				BinNode<T>* hot = sentry->parent;
				BinNode<T>* b = this->rotateGPV(BST<T>::tallerChild(BST<T>::tallerChild(sentry)));
				hot_link = b;
				b->parent = hot;
			}
			break;
		}
		else {
			this->updateHeight(sentry);
			std::cout << YELLOW << "updated of sentry:" << sentry->data << " to be " << sentry->height << std::endl;
		}
		sentry = sentry->parent;
	}
	std::cout << YELLOW << "------ AVL tree top ------";
	this->traverseLevel();
	std::cout << YELLOW << "------ AVL tree bottom ------" << WHITE << std::endl;
	return x;
}












};

#endif