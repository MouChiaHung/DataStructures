#ifndef _MY_STACK_H_
#define _MY_STACK_H_

#include <vector>

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
class Stack{
private:
	std::vector<T> vector;
public:
	Stack() {
		std::cout << "[Stack::Stack()]: this:" << this << WHITE << std::endl;
	}

	~Stack() {
		std::cout << "[Stack::~Stack()]: this:" << this << WHITE << std::endl;
	}
	typedef struct functor_traverse {
		void operator() (T& t) {
			std::cout << "[Stack::VST::operator()(T&)]: element:" << t << " at " << &t << WHITE << std::endl;
		}
	} VST;
	void push(T const& t);
	T pop();
	T& top();
	void traverse();
	bool empty() { return vector.size() == 0 ? true : false;}
};

template<class T>
void amo::Stack<T>::traverse() {
	VST functor;
	std::cout << "[Stack::pop()]: --- STACK TOP ------" << WHITE << std::endl;
	for (typename std::vector<T>::iterator it=std::next(vector.end(),-1); it!=std::next(vector.begin(),-1); it--) functor(*it);
	std::cout << "[Stack::pop()]: --- STACK BOTTOM ---" << WHITE << std::endl;
}

template<class T>
void amo::Stack<T>::push(T const& t) {
	std::cout << "[Stack::push()]: t:" << t << WHITE << std::endl;
	vector.push_back(t);
}

template<class T>
T amo::Stack<T>::pop() {
	T t = vector.at(vector.size()-1);
	vector.pop_back();
	std::cout << "[Stack::pop()]: returns:" << t << WHITE << std::endl;
	return t; 
}

template<class T>
T& amo::Stack<T>::top() {
	return vector.at(vector.size()-1);
}














}
#endif