#ifndef _MY_LINKED_QUEUE_H_
#define _MY_LINKED_QUEUE_H_

#include <node.h>
#include <queue.h>

#define MAGENTA "\033[35m"      /* Magenta */
#define WHITE   "\033[37m"      /* White */

template<class T>
//class MyLinkedListQueue:protected MyQueue<T> {
class MyLinkedListQueue{
	private:
		MyNode<T>* 	head;
		int			count;
	public:
		//MyLinkedListQueue():MyQueue<T>(){
		MyLinkedListQueue(){
			count = 0;
			std::cout << MAGENTA << "[MyLinkedListQueue<T>::MyLinkedListQueue()]: this:" << this << WHITE << std::endl;
		}
		~MyLinkedListQueue(){
			if(head) delete head;
			std::cout << MAGENTA << "[MyLinkedListQueue<T>::~MyLinkedListQueue()]: this:" << this << WHITE << std::endl;
		}
		void offer(const T &t);
		//T& poll();
		T poll();
		T& peek();
};

template<class T>
void MyLinkedListQueue<T>::offer(const T &t) {
	std::cout << MAGENTA << "[MyLinkedListQueue<T>::offer()]: going to MyNode<T> node(t)" << WHITE << std::endl;
	
	//MyNode<T> node(t); 					//SEGV because destroyed when finishes?! lifetime limit?!
	//MyNode<T> node = *(new MyNode<T>(t)); //SEGV when initializes node using copy constructor from *(new MyNode<T>(t))?! lifetime limit?!
	MyNode<T>& node = *(new MyNode<T>(t));
	
	if(count == 0){
		std::cout << MAGENTA << "[MyLinkedListQueue<T>::offer()]: going to head = &node:" << &node << WHITE << std::endl;
		head = &node;
	} else {
		MyNode<T>* back = head;
		//for (int i=0;i<count-1;i++) back = head + 1; //doesn't work because memory space of each elements in list is not related to the others   
		std::cout << MAGENTA << "[MyLinkedListQueue<T>::offer()]: going to while-loop" << WHITE << std::endl;
		while (back->getNext()!=0) {
			std::cout << MAGENTA << "[MyLinkedListQueue<T>::offer()]: going to back(at " << back << ") = back->getNext()"<< WHITE << std::endl;
			back = back->getNext(); 
		}	
		std::cout << MAGENTA << "[MyLinkedListQueue<T>::offer()]: going to back(at " << back << ")->setNext(&node):" << &(node) << WHITE << std::endl;
		back->setNext(&node);
	}
	++(count);
	std::cout << MAGENTA << "[MyLinkedListQueue<T>::offer()]: finished and count:" << count << ", head:" << head << WHITE << std::endl;
}	

/**
 * This will not work because you're returning an alias (a reference) to an object with a lifetime limited to the scope of the function call. 
 * The reference returned from the function worthless because it now refers to an object that doesn't exist.
 */
//T& MyLinkedListQueue<T>::poll() {}

/**
 * This is perfectly fine to return a self-defined object because every compiler nowadays implements some form of return value optimization.
 * See local variable 't' will not be destroyed when function finishes and can be accessed outside.
 * This way to return a object and access it is just like Java does.
 *
 * The criteria of compiler NRVO for elision can be combined to eliminate two calls to the copy constructor of Class: 
 * the copying of the local object 't' into the temporary object for the return value of function poll()
 * and the copying of that temporary object into object 'm_poll' outside. 
 * Effectively, the construction of the local object 't' can be viewed as directly initializing the object 'm_poll' outside
 * , and that object’s destruction will occur at program exit. 
 * Adding a move constructor to Class has the same effect, but it is the move construction from the temporary object to the object 'm_poll' outside that is elided.
 */
template<class T>
T MyLinkedListQueue<T>::poll() {
	MyNode<T>* node_poll = head;
	std::cout << MAGENTA << "[MyLinkedListQueue<T>::poll()]: going to head(at "<< head << ") = head->getNext():" << head->getNext() << WHITE << std::endl;
	head = head->getNext(); //updates the list head
	
	std::cout << MAGENTA << "[MyLinkedListQueue<T>::poll()]: going to node_poll->setNext(0)" << WHITE << std::endl;
	node_poll->setNext(0); //isolates the node going to poll
	
	std::cout << MAGENTA << "[MyLinkedListQueue<T>::poll()]: going to 'T t = node_poll->getValue()'" << WHITE << std::endl;
	T t = node_poll->getValue(); //using copy constructor
	
	std::cout << MAGENTA << "[MyLinkedListQueue<T>::poll()]: going to delete node_poll at " << node_poll << WHITE << std::endl;
	delete node_poll; //destroys the node and its member including val. On the other hand, t to be returned is a copy of val
	
	--(this->count);
	std::cout << MAGENTA << "[MyLinkedListQueue<T>::poll()]: returns T t(at " << &t << ") and count:" << count << ", head:" << head << WHITE << std::endl;
	return t; 
}

template<class T>
T& MyLinkedListQueue<T>::peek() {
	MyNode<T>* node = head;
	T& t = node->getValue();
	std::cout << MAGENTA << "[MyLinkedListQueue<T>::peek()]: returns T& t(at " << &t << ") and count:" << count << ", head:" << head << std::endl;
	return t;
}
#endif