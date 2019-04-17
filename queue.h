#ifndef _MY_QUEUE_H_
#define _MY_QUEUE_H_

template<typename T>
class MyQueue {
	protected:
		int count; //amount of elements excluded null
	public:
		MyQueue(){
			count = 0;
		}
		virtual ~MyQueue();
		virtual void offer(T &t) = 0;
		virtual T poll() = 0;
		virtual T peek() = 0;
};

#endif