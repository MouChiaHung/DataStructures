#ifndef _MY_ARRAY_QUEUE_H_
#define _MY_ARRAY_QUEUE_H_

#include <node.h>
#include <queue.h>

#define MAGENTA "\033[35m"      /* Magenta */
#define WHITE   "\033[37m"      /* White */

template<class T>
class MyArrayQueue{
	private:
		int count;
		int capacity;
		int length;
		int first;
		T*	array;
	
	public:
		MyArrayQueue(){
			count = 0;
			capacity = 0;
			length = 0;
			first = 0;
			std::cout << MAGENTA << "[MyArrayQueue<T>::MyArrayQueue()]: >>> this:" << this << WHITE << std::endl;
		}
		MyArrayQueue(int cap){
			count = 0;
			capacity = cap;
			length = cap;
			first = 0;
			array = new T[capacity]; //calls to constructor
			std::cout << MAGENTA << "[MyArrayQueue<T>::MyArrayQueue()]: >>> this:" << this  << " and allocate array:" << array << ", allocate capacity:" << capacity << WHITE << std::endl;
		}
		~MyArrayQueue(){
			if(array) delete[] array;
			std::cout << MAGENTA << "[MyArrayQueue<T>::~MyArrayQueue()]: >>> this:" << this << " and release array:" << array << WHITE << std::endl;
		}
		void 	offer(const T &t);
		T		poll();
		T&		peek();
};

template<class T>
void MyArrayQueue<T>::offer(const T &t){
	if(count == length){
		T *array_exd = new T[(length+capacity)];
		memcpy(array_exd, array+first, (length-first)*sizeof(T));
		memcpy(array_exd+length-first, array, first*sizeof(T));
		length+=capacity;
		delete[] array;
		array = array_exd;
		first = 0;
		for(int i=0; i<length; i++){
			std::cout << MAGENTA << "[MyArrayQueue<T>::offer()]: new array[" << i << "]:" << &array[i] << " and value:" << array[i].getNumber() << WHITE << std::endl;
		}
	}
	std::cout << MAGENTA << "[MyArrayQueue<T>::offer()]: going to array["<< (first+count)%length <<"] = t" << WHITE << std::endl;
	array[(first+count)%length] = t; //calls to T::operator=(T&) because array[] already has an instance
	++this->count;
	std::cout << MAGENTA << "[MyArrayQueue<T>::offer()]: finished" << " and count:" << this->count << ", first:" << first << WHITE << std::endl;
}

/**
 * This is perfectly fine to return a self-defined object because every compiler nowadays implements some form of return value optimization.
 * See local variable 't' will not be destroyed when function finishes and can be accessed outside.
 * This way to return a object and access it is just like Java does.
 */
template<class T>
T MyArrayQueue<T>::poll(){
	std::cout << MAGENTA << "[MyArrayQueue<T>::poll()]: going to 'T t = array[" << first << "]'" << WHITE << std::endl;
	T t = array[first]; //using copy constructor
	//array[first] = 0; //err @@?
	memset(array+first, 0, sizeof(T));
	first = (first+1)%length;
	--this->count;
	std::cout << MAGENTA << "[MyArrayQueue<T>::poll()]: returns t (at " << &t << ") and count:" << count << ", first:" << first << WHITE << std::endl;
	return t;
}

template<class T>
T& MyArrayQueue<T>::peek(){
	std::cout << MAGENTA << "[MyArrayQueue<T>::peek()]: going to 'T& t = array[" << first << "]'" << WHITE << std::endl;
	T& t = array[first];
	for(int i=0; i<length; i++){
		std::cout << MAGENTA << "[MyArrayQueue<T>::peek()]: array[" << i << "]:" << &array[i] << " and value:" << array[i].getNumber() << WHITE << std::endl;
	}
	std::cout << MAGENTA << "[MyArrayQueue<T>::peek()]: returns t (at " << &t << ") and count:" << count << ", first:" << first << WHITE << std::endl;
	return t;
}
#endif