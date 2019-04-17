#ifndef _MATH_H_
#define _MATH_H_

#include <iostream>

class MyMath {
//protected:
private:
	int		number;
	int		*data;
	int		data_length;
public:
	static int user;
	static MyMath instance;
	int 	getNumber()const; //with const qualifier
	void	getData(int *buf) const; //const function, denoted with the keyword const after a function declaration
	                                 //, makes it a compiler error for this class function to change a member variable of the class.
									 //However, reading of a class variables is okay inside of the function
									 //, but writing inside of this function will generate a compiler error.
									 //To allow some of the variables to be writable even when the function is marked as a const function
									 //, these class variables are marked with the keyword mutable. (C++11)
	void 	setNumber(int num);
	void 	setData(int *src, int length);
#if 1	
	static MyMath& 	decode(MyMath math);
	static MyMath& 	decodeWithRef(MyMath& math);
#else	
	static MyMath& decode(MyMath math) {
		std::cout << "[MyMath::decode()]: ... got math:" << &math << std::endl;
		//instance = *(new MyMath(math)); //this new object would be a leak
		instance = math;
		//MyMath instance = math;
		std::cout << "[MyMath::decode()]: ... return instance:" << &instance << std::endl;
		return instance;
	}

	static MyMath& decodeWithRef(MyMath& math) {
		std::cout << "[MyMath::decodeWithRef()]: ... got math:" << &math << std::endl;
		//instance = *(new MyMath(math)); //this new object would be a leak
		instance = math;
		//MyMath instance = math;
		std::cout << "[MyMath::decodeWithRef()]: ... return instance:" << &instance << std::endl;
		return instance;
	}
#endif	
#if 0	
	MyMath* operator+(MyMath* math);
#elif 0
	void  operator+(MyMath& math);
#else
	/**
	 * Although canonical form of pre-increment/pre-decrement returns a reference
	 * , as with any operator overload, the return type is user-defined;
	 */
	//MyMath  operator+(MyMath& math);
	MyMath&  operator+(MyMath& math);
#endif
	//MyMath* operator++();
	MyMath& operator++();
	MyMath& operator++(int);
	//MyMath* operator--();
	MyMath& operator--();
	MyMath& operator--(int);
	bool	operator==(const MyMath& math);
	bool	operator!=(const MyMath& math);
	bool	operator<(const MyMath& math) const;
	bool	operator>(const MyMath& math) const;
#if 0	
	MyMath* operator=(MyMath &math);
#else
	MyMath& operator=(const MyMath &math);
#endif	
	//friend void operator+(MyMath &math1, MyMath &math2);
	friend int operator-(MyMath& m1, MyMath& m2);
	friend void	operator++(MyMath &math);
	friend std::ostream &operator<<(std::ostream &stream, MyMath &math);
	friend std::istream &operator>>(std::istream &stream, MyMath &math);
	MyMath(); //default constructor
	MyMath(int num);
	MyMath(MyMath& math);  //copy constructor with a reference to lvalue
	MyMath(MyMath&& math); //move constructor with a reference to rvalue
	MyMath(const MyMath &math); //const type or leads vector::push_back() err
	static void setUser(int user_id){
		user = user_id;
	}
	static int getUser(){
		return user;
	}
	~MyMath();
};

#endif