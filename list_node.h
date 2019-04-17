#ifndef _MY_LIST_NODE_H_
#define _MY_LIST_NODE_H_

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

template<class T>
class Node{
private:	

public:	
	T data;
	Node<T>* pred;
	Node<T>* succ;
	Node() {
		std::cout << MAGENTA << "[Node::Node()]: this:" << this << WHITE << std::endl;
	}
	Node(T const& t, Node<T>* p=NULL, Node<T>* s=NULL) :  data(t), pred(p), succ(s) {
		std::cout << MAGENTA << "[Node::Node(T&,Node*,Node*)]: this:" << this << ", data:" << data << ", pred:" << pred << ", succ:" << succ << WHITE << std::endl;
	}
	~Node() {
		//std::cout << MAGENTA << "[Node::~Node()]: this:" << this << ", data:" << data << WHITE << std::endl;
	}
	Node<T>* insertPred(T const& t);
	//Node<T>  insertPred(T const& t);
	Node<T>* insertSucc(T const& t);
	//Node<T> insertSucc(T const& t);
	Node<T>* next(int n);
};

#if 1
template<class T>
Node<T>* amo::Node<T>::insertPred(T const& t) {
	Node<T>* node = new Node<T>(t, pred, this); 
	pred->succ = node;
	pred = node;
	return node;
}
/**
 * local created node will be destroyed if there is not any variable outside referring to the local created node because RNO doesn't cover this case. 
 */
#else
template<class T>
Node<T> amo::Node<T>::insertPred(T const& t) {
	Node<T> node(t, pred, this); 
	pred->succ = &node;
	pred = &node;
	std::cout << MAGENTA << "[Node::insertPred(T&)]: returns new inserted node at " << &node << WHITE << std::endl;
	return node;
}
#endif

#if 1
template<class T>
Node<T>* amo::Node<T>::insertSucc(T const& t) {
	Node<T>* node = new Node(t, this, succ);
	succ->pred = node;
	succ = node;
	return node;
}
/**
 * local created node will be destroyed if there is not any variable outside referring to the local created node because RNO doesn't cover this case. 
 */
#else 
template<class T>
Node<T> amo::Node<T>::insertSucc(T const& t) {
	Node<T> node(t, this, succ);
	succ->pred = &node;
	succ = &node;
	std::cout << MAGENTA << "[Node::insertSucc(T&)]: returns new inserted node at " << &node << WHITE << std::endl;
	return node;
}
#endif

template<class T>
Node<T>* amo::Node<T>::next(int n) {
	Node<T>* node = this;
	if (n >= 0) {
		while (0<n--) {
			node = node->succ;
			if (node == NULL) {
				std::cout << RED << "[Node::next(int)]: successor node is NULL and breaks from loop:" << n << WHITE << std::endl;
				break;
			}
		}
	} else {
		int k = -n;
		while(0<k--) {
			node = node->pred;
			if (node == NULL) {
				std::cout << RED << "[Node::next(int)]: predecessor node is NULL and breaks from loop:" << n << WHITE << std::endl;
				break;
			}
		}
	}
	if (node == NULL) std::cout << RED << "[Node::next(int)]: returns NULL" << WHITE << std::endl;
	//else std::cout << MAGENTA << "[Node::next(int)]: returns:" << node->data << " at " << node << WHITE << std::endl;
	return node;
}

}
#endif