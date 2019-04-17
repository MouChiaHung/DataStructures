 /*************************
  *  math.cpp
  *  
  *
  *  editor: amo
  *************************/
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>

/* -------------------------------------------------------------------- */
/* my define macro                                                     */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* global variables                                                     */
/* -------------------------------------------------------------------- */
int MyMath::user = -1;
int num_instance = -9999;
MyMath MyMath::instance(num_instance);

/* -------------------------------------------------------------------- */
/* implements                                                           */
/* -------------------------------------------------------------------- */
MyMath::MyMath(){
	number = 0;
	data = new int[8];
	data_length = 8;
	user++;
	std::cout << "[MyMath::MyMath()]:" << this << ", data:" << data << ", number:" << number << std::endl;
}

MyMath::MyMath(int num){
	number = num;
	data = new int[8];
	data_length = 8;
	user++;
	if (num == num_instance)
		std::cout << "[MyMath::MyMath(int)]:Global instance used for functions returning a reference:" << this << " and number:" << number << std::endl;
	else 
		std::cout << "[MyMath::MyMath(int)]:" << this << ", data:" << data << ", number:" << number << std::endl;
}

MyMath::MyMath(MyMath &math){
	data = new int[math.data_length];
	data_length = math.data_length;
	user++;
	try{
		memcpy(data, math.data, data_length*sizeof(data[0]));
		number = math.number;
	}catch(...){
		std::cout << "[MyMath::MyMath(MyMath &math)]: !!! new failed" << std::endl;
	}
	std::cout << "[MyMath::MyMath(MyMath &math)]:this:" << this << " copy from " << &math << ", data:" << data << ", number:" << number << std::endl;
}

/**
 * Deep copy by overload copy constructor as well as overload assignment operator=
 */ 
MyMath::MyMath(const MyMath& math){
	data = new int[math.data_length];
	data_length = math.data_length;
	user++;
	try{
		memcpy(data, math.data, data_length*sizeof(data[0]));
		number = math.number;
	}catch(...){
		std::cout << "[MyMath::MyMath(MyMath& math)]: !!! new failed" << std::endl;
	}
	std::cout << "[MyMath::MyMath(MyMath& math)]:this:" << this << " copy from " << &math << ", data:" << data << ", number:" << number << std::endl;
}

/**
 * Shallow copy by overload move constructor
 * Using initialization lists to initialize fields
 */
MyMath::MyMath(MyMath&& math): data(math.data) {  // C++11 - specifying non-exception throwing functions
	std::cout << "[MyMath::MyMath(MyMath&& math)]:this:" << this << " move from " << &math << ", data:" << math.data << ", number:" << math.number << std::endl;
	data = math.data; // shallow copy
	math.data = nullptr;
	number = math.getNumber();
}

MyMath::~MyMath(){
	if(data) {
		if (getNumber() == num_instance) std::cout << "[MyMath::~MyMath()]:Global instance:" << this << ", release data:" << data << ", release number:" << number << std::endl;
		else std::cout << "[MyMath::~MyMath()]:" << this << ", release data:" << data << ", release number:" << number << std::endl;
		delete[] data; //leads SEGV err ?!
	}else{
		std::cout << "[MyMath::~MyMath()]:" << this << ", release number:" << number << std::endl;
	}
}	

void MyMath::setNumber(int num){
	number = num;
}

void MyMath::setData(int *src, int length){
	if(!data){
		data = new int[length];
		try{
			memcpy(data, src, length*sizeof(data[0]));
			data_length = length;
		}catch(...){
			std::cout << "[MyMath::setData()]: !!! new failed at setData()" << std::endl;
		}
	}else{
		std::cout << "[MyMath::setData()]: past data:" << data << std::endl;
		delete[] data;
		data = new int[length];
		std::cout << "[MyMath::setData()]: new data :" << data << std::endl;
		try{
			memcpy(data, src, length*sizeof(data[0]));
			data_length = length;
		}catch(...){
			std::cout << "[MyMath::setData()]: !!! new failed at setData()" << std::endl;
		}
	}	
}

int MyMath::getNumber() const{
	return number;
}

void MyMath::getData(int *buf) const{
	memcpy(buf, data, data_length*sizeof(int));
}

#if 1
MyMath& MyMath::decode(MyMath math) {
	std::cout << "[MyMath::decode()]: got math:" << &math << std::endl;
	//instance = *(new MyMath(math)); //this new object would be a leak
	instance = math;
	//MyMath instance = math;
	std::cout << "[MyMath::decode()]: return instance:" << &instance << std::endl;
	return instance;
}

MyMath& MyMath::decodeWithRef(MyMath& math) {
	std::cout << "[MyMath::decodeWithRef()]: got math:" << &math << std::endl;
	//instance = *(new MyMath(math)); //this new object would be a leak
	instance = math;
	//MyMath instance = math;
	std::cout << "[MyMath::decodeWithRef()]: return instance:" << &instance << std::endl;
	return instance;
}
#endif

#if 0
MyMath* MyMath::operator+(MyMath *math){
	std::cout << "[MyMath::operator+(MyMath &)) return MyMath*]:operator+()" << std::endl;
	MyMath* newMath;
	int 	newNum = number + math->number;
	newMath = new MyMath(newNum);
	return newMath;
}

#elif 0
void MyMath::operator+(MyMath &math){
	std::cout << "[MyMath::operator+(MyMath &) return void]:" << std::endl;
	int 	newNum = number + math.number;
	this->number = newNum;
}
#elif 0
MyMath MyMath::operator+(MyMath &math){
	std::cout << "[MyMath::operator+(MyMath &) return MyMath]:" << std::endl;
	int newNum = number + math.number;
	MyMath newMath(newNum); //locals will be deallocated when exits.
	return newMath; //reference to a local about to be deallocated?!
}
#else
MyMath& MyMath::operator+(MyMath &math){
	std::cout << "[MyMath::operator+(MyMath &) return MyMath&]:" << std::endl;
	number = number + math.number;
	return *this; //reference to a local about to be deallocated?!
}
#endif

#if 0
MyMath* MyMath::operator++(){
	std::cout << "[MyMath::operator++()]:operator++()" << std::endl;
	number++;
	return this;
}

MyMath* MyMath::operator--(){
	std::cout << "[MyMath::operator--()]:operator--(int)" << std::endl;
	number--;
	return this;
}
#else
MyMath& MyMath::operator++(){
	std::cout << "[MyMath::operator++()]:operator++()" << std::endl;
	number++;
	return *this;
}

MyMath& MyMath::operator++(int){
	std::cout << "[MyMath::operator++()]:operator++(int)" << std::endl;
	operator++();
	return *this;
}

MyMath& MyMath::operator--(){
	std::cout << "[MyMath::operator--()]:operator--()" << std::endl;
	number--;
	return *this;
}

MyMath& MyMath::operator--(int){
	std::cout << "[MyMath::operator--()]:operator--(int)" << std::endl;
	operator--();
	return *this;
}
#endif
#if 0
MyMath* MyMath::operator=(MyMath &math){
	if(!data){
		data = new int[math.data_length];
		try{
			memcpy(data, math.data, math.data_length*sizeof(data[0]));
			data_length = math.data_length;
			number = math.number;
		}catch(...){
			std::cout << "[MyMath::operator=(MyMath&)]: !!! new failed at setData()" << std::endl;
		}
	}else{
		//std::cout << "[MyMath::operator=(MyMath&)]: past data:" << data << std::endl;
		delete[] data;
		data = new int[math.data_length];
		//std::cout << "[MyMath::operator=(MyMath&)]: new data :" << data << std::endl;
		try{
			memcpy(data, math.data, math.data_length*sizeof(data[0]));
			data_length = math.data_length;
			number = math.number;
		}catch(...){
			std::cout << "[MyMath::operator=(MyMath&)]: !!! new failed at setData()" << std::endl;
		}
	}
	return this;
}
#else
MyMath& MyMath::operator=(const MyMath &math){
	if(!data){
		std::cout << "[MyMath::operator=(MyMath&)]: !!! data is null" << data << std::endl;
	}else{
		std::cout << "[MyMath::operator=(MyMath&)]: going to delete the past data:" << data << std::endl;
		delete[] data;
		data = new int[math.data_length];
		std::cout << "[MyMath::operator=(MyMath&)]: allocated new data :" << data << std::endl;
		try{
			memcpy(data, math.data, math.data_length*sizeof(data[0]));
			data_length = math.data_length;
			number = math.number;
			std::cout << "[MyMath::operator=(MyMath&)]: passed math at    :" << &math << std::endl;
			std::cout << "[MyMath::operator=(MyMath&)]: passed math.data  :" << math.data << std::endl;
			std::cout << "[MyMath::operator=(MyMath&)]: passed math.number:" << math.getNumber()	<< std::endl;
			std::cout << "[MyMath::operator=(MyMath&)]: this  :" << this << std::endl;
			std::cout << "[MyMath::operator=(MyMath&)]: data  :" << data << std::endl;
			//std::cout << "[MyMath::operator=(MyMath&)]: this->data      :" << this->data << std::endl;
			std::cout << "[MyMath::operator=(MyMath&)]: number:" << number << std::endl;
		}catch(...){
			std::cout << "[MyMath::operator=(MyMath&)]: !!! new failed at setData()" << std::endl;
		}
	}
	return *this; //a reference returned refers a object pointed by this 
}
#endif

bool MyMath::operator==(const MyMath& math){
	bool ret = false;
	ret = this->getNumber() == math.getNumber()?true:false;
	if (ret) std::cout << "[MyMath::operator==()]: returns true meaning equivalently " << this << " == " << &math << std::endl;
	else std::cout << "[MyMath::operator==()]: returns false meaning equivalently " << this << " != " << &math << std::endl;
	return ret;	
}

bool MyMath::operator!=(const MyMath& math){
	bool ret = false;
	ret = this->getNumber() != math.getNumber()?true:false;
	if (ret) std::cout << "[MyMath::operator!=()]: returns true meaning equivalently " << this << " != " << &math << std::endl;
	else std::cout << "[MyMath::operator!=()]: returns false meaning equivalently " << this << " == " << &math << std::endl;
	return ret;	
}

bool MyMath::operator<(const MyMath& math) const{
	bool ret = false;
	ret = this->getNumber() < math.getNumber()?true:false;
	if (ret) 
		std::cout << "[MyMath::operator<()]: returns true  meaning equivalently " << this << "(" << getNumber() << ")" << " < " << &math << "(" << math.getNumber() << ")"<< std::endl;
	else 
		std::cout << "[MyMath::operator<()]: returns false meaning equivalently " << this << "(" << getNumber() << ")" << " >= or !< " << &math << "(" << math.getNumber() << ")"<< std::endl;
	return ret;	
}

bool MyMath::operator>(const MyMath& math) const{
	bool ret = false;
	ret = this->getNumber() > math.getNumber()?true:false;
	if (ret) std::cout << "[MyMath::operator>()]: returns true  meaning equivalently " << this << "(" << getNumber() << ")" << " > " << &math << "(" << math.getNumber() << ")"<< std::endl;
	else std::cout << "[MyMath::operator>()]: returns false meaning equivalently " << this << "(" << getNumber() << ")" << " <= or !>" << &math << "(" << math.getNumber() << ")"<< std::endl;
	return ret;	
}