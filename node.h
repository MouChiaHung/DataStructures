#ifndef _MY_NODE_H_
#define _MY_NODE_H_

#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

template<class T>
class MyNode {
	private:
		MyNode<T>* next = 0;
		T val;
	public:
		void setNext(MyNode* node);
		MyNode* getNext();
		void setValue(T& t);
		T& getValue();
		MyNode(const T &t);
		~MyNode();
};

template<class T>
MyNode<T>::MyNode(const T &t){
	std::cout << CYAN << "[MyNode<T>::MyNode()]: this (at " << this << ") going to val (at " << &val << ") = t (at " << &t << ")" << WHITE << std::endl;
	val = t; //using operator=
	//next = 0;
	//std::cout << CYAN << "[MyNode<T>::MyNode()]: after this (at " << this << "), val (at " << &val << "), t (at " << &t << ")" << WHITE << std::endl;
}

template<class T>
MyNode<T>::~MyNode(){
	if(next) delete next;
	//delete &val;
	std::cout << CYAN << "[MyNode<T>::~MyNode()]: this:" << this << ", released next:" << next << WHITE << std::endl;
}

template<class T>
void MyNode<T>::setNext(MyNode* node){
	next = node;
	std::cout << CYAN << "[MyNode<T>::setNext()]: this:" << this << " sets next:" << next << WHITE << std::endl;
}

template<class T>
MyNode<T>* MyNode<T>::getNext(){
	std::cout << CYAN << "[MyNode<T>::getNext()]: this:" << this << " returns next:" << next << WHITE << std::endl;
	return next;
}

template<class T>
void MyNode<T>::setValue(T& t){
	std::cout << CYAN  << "[MyNode<T>::setValue()]: this:" << this << " assigns t (at " << &t << ") to val of node at " << &val << WHITE << std::endl;
	val = t; //using operator=
}

template<class T>
T& MyNode<T>::getValue(){
	std::cout << CYAN << "[MyNode<T>::getValue()]: this:" << this << " returns ref of val at " << &val << WHITE << std::endl;
	return val;
}
#endif