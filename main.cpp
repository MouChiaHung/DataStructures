 /*************************************************************************************************************************************************
  *  main.cpp
  *  editor: amo
  *************************************************************************************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <deque>
#include <queue>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <screen.h>
#include <text_view.h>
#include <view.h>
#include <math.h>
#include <space.h>
#include <node.h>
#include <linked_queue.h>
#include <array_queue.h>
#include <time.h>

#include <list.h>
#include <list_node.h>
#include <stack.h>

#include <sort.h>
#include <number.h>
#include <move.h>

#include <char.h>
#include <queen.h>
#include <maze.h>
#include <cell.h>

#include <bin_tree.h>
#include <bin_node.h>
#include <huffman_tree.h>
#include <bst.h>

#include <graph.h>
#include <entry.h>

#include <dict.h>
#include <entry.h>
#include <cmath>

#include <bmp.h>

using namespace std;
using namespace amo;
using namespace mystd::myfstream;
using amo::List;
using amo::Node;
using amo::Char;
using  mystd::myfstream::ifstream;
using  mystd::myfstream::ofstream;

/* -------------------------------------------------------------------- */
/* my define macro                                                     */
/* -------------------------------------------------------------------- */
typedef struct myframe {
	int x;
	int y;
	void show_location(){
		std::cout << "x:" << x << std::endl;
		std::cout << "y:" << y << std::endl;
	}
} myframe_t;

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

/* -------------------------------------------------------------------- */
/* global variables                                                     */
/* -------------------------------------------------------------------- */
char data[128];
int mTheme = 0;
int mXPad = 10;
int mYPad = 20;

/* -------------------------------------------------------------------- */
/* implements                                                           */
/* -------------------------------------------------------------------- */
class MyFrame{
	int positionX;
	int positionY;
public:
	void setX(int x);
	void setY(int y);
	void showLocation();
	MyFrame(int x, int y);
	//MyFrame(MyFrame &frame);
	MyFrame(int value);
	~MyFrame();
	MyFrame(){
		positionX = 0;
		positionY = 0;
	}
};	

/*
MyFrame::MyFrame(MyFrame &frame){
	positionX = frame.positionX + 10;
	positionY = frame.positionY + 10;
}
*/

MyFrame::MyFrame(int x, int y){
		positionX = x;
		positionY = y;
}

MyFrame::MyFrame(int value){
	positionX = value;
	positionY = -10;
}

MyFrame::~MyFrame(){
	std::cout << "release at positionX:" << positionX << std::endl;
	std::cout << "release at positionY:" << positionY << std::endl;
}

void MyFrame::showLocation(){
		std::cout << "positionX:" << positionX << std::endl;
		std::cout << "positionY:" << positionY << std::endl;
}	

void MyFrame::setX(int x){
	positionX = x;
}

void MyFrame::setY(int y){
	positionY = y;
}

MyFrame* getMyFrameRef(int x, int y){
	MyFrame *frame = new MyFrame(x, y);
	return frame;
}

int layout(MyScreen screen){
	int layoutX = screen.getPixelX() + mXPad;
	int layoutY = screen.getPixelY() + mYPad;
	switch(mTheme){
		case 0:
			std::cout << "### Standard Theme ###"<< std::endl;
			std::cout << "... layoutX:" << layoutX << std::endl;
			std::cout << "... layoutY:" << layoutY << std::endl;
			break;
		case 1:
			std::cout << "### Festival Theme ###"<< std::endl;
			std::cout << "... layoutX:" << layoutX << std::endl;
			std::cout << "... layoutY:" << layoutY << std::endl;
			break;
		default:
			std::cout << "### Unknown Theme ###"<< std::endl;
			std::cout << "... layoutX:" << layoutX << std::endl;
			std::cout << "... layoutY:" << layoutY << std::endl;
			break;
	}
}

void updateView(MyView *view, int changed, int l, int r, int t, int b){
	std::cout << "[main]: >>> updateView()" << std::endl;
	view->onLayout(changed, l, r, t, b);
}

/**
 * Other than the restrictions above, the language puts no other constraints on what the overloaded operators do
 * , or on the return type (it does not participate in overload resolution)
 *
int operator+(MyMath &math1, MyMath &math2){
	std::cout << "[main]: >>> operator+()" << std::endl;
	int x = math1.getNumber();
	int y = math2.getNumber();
	math1.setNumber(x+y);
	return 0;
}

void operator+(MyMath &math1, MyMath &math2){
	std::cout << "[main]: >>> operator+()" << std::endl;
	int x = math1.getNumber();
	int y = math2.getNumber();
	math1.setNumber(x+y);
}
*/

int operator-(MyMath& m1, MyMath& m2) {
	std::cout << "[main::operator-(MyMath&, MyMath)]: >>>" << std::endl;
	return m1.getNumber() - m2.getNumber();
}

void operator++(MyMath &math) {
	std::cout << "[main::operator++(MyMath&)]: >>>" << std::endl;
	++math.number;
}

namespace mystd::myfstream {
	std::istream &operator>>(std::istream &stream, mystd::myfstream::ifstream &fis) {
		std::cout << "[main::operator>>(std::istream&, mystd::myfstream::ifstream&)]: >>> enter numbers..." << std::endl;
		stream >> fis.filebuf;
		return stream;
	}

	std::ostream &operator<<(std::ostream &stream, mystd::myfstream::ifstream &fis) {
		std::cout << "[main::operator<<(std::ostream&, mystd::myfstream::ifstream&)]: >>> content:" << std::endl;
		for(int i=0; i<sizeof(fis.filebuf); i++) stream << "fis.filebuf[" << i << "]:" << fis.filebuf[i] << std::endl;
		return stream;
	}

	std::istream &operator>>(std::istream &stream, mystd::myfstream::ofstream &fos) {
		std::cout << "[main::operator>>(std::istream&, mystd::myfstream::ifstream&)]: >>> enter numbers..." << std::endl;
		stream >> fos.filebuf;
		return stream;
	}

	std::ostream &operator<<(std::ostream &stream, mystd::myfstream::ofstream &fos) {
		std::cout << "[main::operator<<(std::ostream&, mystd::myfstream::ifstream&)]: >>> content:" << std::endl;
		for(int i=0; i<sizeof(fos.filebuf); i++) stream << "fos.filebuf[" << i << "[]:" << fos.filebuf[i] << std::endl;
		return stream;
	}
}

/* a binary predicate implement as a class */
struct PredicateMyMathEqual{
	bool operator()(MyMath& math1, MyMath& math2){
		bool ret = math1.getNumber()==math2.getNumber()?true:false;
		if (ret) std::cout << "[PredicateMyMathEqual::operator()(MyMath&,MyMath&)]: returns true meaning equivalently " << &math1 << " == " << &math2 << std::endl;
		else std::cout << "[PredicateMyMathEqual::operator()(MyMath&,MyMath&)]: returns false meaning equivalently " << &math1 << " != " << &math2 << std::endl;
		return ret;
	}
};

/* a binary predicate implement as a class */
struct PredicateMyMathLess{
	bool operator()(MyMath& math1, MyMath& math2){
		bool ret = math1.getNumber()<math2.getNumber()?true:false;
		if (ret) std::cout << "[PredicateMyMathLess::operator()(MyMath&,MyMath&)]: returns true meaning equivalently " << &math1 << " < " << &math2 << std::endl;
		else std::cout << "[PredicateMyMathLess::operator()(MyMath&,MyMath&)]: returns false meaning equivalently " << &math1 << " >= " << &math2 << std::endl;
		return ret;
	}
};

void input(vector<char>& input) {
	char c;
#if 0
	while (true) {
		cin >> c;
		if(c == '\n') {
			std::cout << "c == \\n and break" << std::endl;
			break;
		}
		if(c == '\0') {
			std::cout << "c == \\0 and break" << std::endl;
			break;
		}
		if(c == ' ') {
			std::cout << "c == ' ' and break" << std::endl;
			break;
		}
		std::cout << "going to push char:" << c << std::endl;
		input.push_back(c);
	}
#elif 1
/**
 * char * fgets ( char * str, int num, FILE * stream );
 * Get string from stream
 * Reads characters from stream and stores them as a C string into str until (num-1) characters have been read
 * or either a newline or the end-of-file is reached, whichever happens first.
 *
 * A newline character makes fgets stop reading, but it is considered a valid character by the function and included in the string copied to str.
 * A terminating null character is automatically appended after the characters copied to str.
 *
 * Notice that fgets is quite different from gets: not only fgets accepts a stream argument
 * , but also allows to specify the maximum size of str and includes in the string any ending newline character.
 *
 * Parameters
 * str: Pointer to an array of chars where the string read is copied.
 * num: Maximum number of characters to be copied into str (including the terminating null-character).
 * stream: Pointer to a FILE object that identifies an input stream.
 * 		   stdin can be used as argument to read from the standard input.	
 * Return value:
 * On success, the function returns str.
 * If the end-of-file is encountered while attempting to read a character, the eof indicator is set (feof).
 * If this happens before any characters could be read, the pointer returned is a null pointer.
 */
	char buf[32];
	std::cout << "Please enter input..." << std::endl;
	fgets(buf, sizeof(buf), stdin);
	std::cout << "Your input..." << std::endl;
	puts(buf);
	int i = 0;
	while ((c=buf[i++]) && i<=strlen(buf)) {
		if(c == '\n') {
			std::cout << "c == \\n and break" << std::endl;
			break;
		}
		if(c == '\0') {
			std::cout << "c == \\0 and break" << std::endl;
			break;
		}
		if(c == ' ') {
			std::cout << "c == ' ' and break" << std::endl;
			break;
		}
		std::cout << "going to push char:" << c << std::endl;
		input.push_back(c);
	}
#else
	while (true) {
		cin.get(c);
		if(c == '\n') {
			std::cout << "c == \\n and break" << std::endl;
			break;
		}
		if(c == '\0') {
			std::cout << "c == \\0 and break" << std::endl;
			break;
		}
		if(c == ' ') {
			std::cout << "c == ' ' and break" << std::endl;
			break;
		}
		std::cout << "going to push char:" << c << std::endl;
		input.push_back(c);
	}
#endif	
}

void output(vector<char>& output) {
	for (std::vector<char>::iterator it=output.begin(); it!=output.end(); it++) cout << *it;
	cout << endl;
}

int main(int argc, char *argv[])
{
	int num = 10;
	int* pnum = &num;
	std::cout << std::endl;
	std::cout << GREEN << "****************** argc:" << argc << " ******************"<< WHITE << std::endl;
	for(int i=0; i<argc; i++) std::cout << GREEN << "****************** arg[" << i << "]: " << argv[i] << " ******************"<< WHITE << std::endl;
	
#if 0
	std::cout << "Enter your name:" << std::endl;
	std::cin >> data;
	std::cout << "hello c++ to " << data << std::endl;
	std::cout << std::setw(1) << "dec: " << std::dec << num << std::endl;
	std::cout << std::setw(1) << "dec: " << std::dec << num << std::endl;
	std::cout << "hex: 0x" << std::hex << num << std::endl;
	return 0;
#endif

#if 0		
	std::cout << "Enter a number:" << std::endl;
	std::cin >> num;
	sprintf(data, "%d", num);
	std::cout << "num: " << data << std::endl;
	std::cout << "... going to handle pointer" << std::endl;
	*pnum = 100;
	sprintf(data, "%d", num);
	std::cout << "num: " << data << std::endl;
#endif

#if 0
	//A dynamic 2D array is basically an array of pointers to arrays.
	int	image[3][3] = {
		{11, 12, 13},
		{21, 22, 23},
		{31, 32, 33},
	};
	int* pimage = image[0];
	std::cout << "image          : " << std::hex << image << std::endl;
	std::cout << "image[0]       : " << std::hex << image[0] << std::endl;
	std::cout << "pimage         : " << std::hex << pimage << std::endl;
	std::cout << "image[1]       : " << std::hex << image[1] << std::endl;
	std::cout << "(image+1)      : " << std::hex << (image+1) << std::endl;
	std::cout << "*(image+1)     : " << std::hex << *(image+1) << std::endl;
	std::cout << "**(image+1)    : " << std::dec << **(image+1) << std::endl;
	std::cout << "*(image+1)+1   : " << std::hex << *(image+1)+1 << std::endl;
	std::cout << "*(*(image+1)+1): " << std::dec << *(*(image+1)+1) << std::endl;
	
	std::cout << "image[2]       : " << std::hex << image[2] << std::endl;
	std::cout << "(image+2)      : " << std::hex << (image+2) << std::endl;
	std::cout << "*(image+2)     : " << std::hex << *(image+2) << std::endl;
	std::cout << "**(image+2)    : " << std::dec << **(image+2) << std::endl;
	std::cout << "*(image+2)+1   : " << std::hex << *(image+2)+1 << std::endl;
	std::cout << "*(*(image+2)+1): " << std::dec << *(*(image+2)+1) << std::endl;
	std::cout << "*(*(image+2)+2): " << std::dec << *(*(image+2)+2) << std::endl;
	return 0;
#endif

#if 0
	myframe_t frame = {3, 3, };
	frame.show_location();
#endif
	
#if 0	
	MyFrame mFrame;
	//mFrame.x = 9;
	//mFrame.y = 8;
	mFrame.showLocation();
	
	MyFrame mFrameList[3] = {MyFrame(1,1), MyFrame(2,2), MyFrame(3,3)};
	mFrameList[0].showLocation();
	mFrameList[1].showLocation();
	mFrameList[2].showLocation();
	
	MyFrame mFrameDup = MyFrame(mFrameList[0]);
	mFrameDup.showLocation();
	
	MyFrame* mFrameRef = getMyFrameRef(31, 89);
	if(mFrameRef) mFrameRef->showLocation();
	if(mFrameRef) delete mFrameRef;
#endif	
	
#if 0		
	MyScreen mScreen(300, 300);
	mScreen.showSize();
	layout(mScreen);
#endif	
	
#if 0
	std::cout << "****************** instantiate ******************\n" << std::endl;
	
	std::cout << "[main]: ... going to MyTextView tv1;" << std::endl;
	MyTextView tv1;	
	std::cout << "[main]: ... going to MyTextView tv2();" << std::endl;
	MyTextView tv2();
	std::cout << "[main]: ... going to MyTextView tv3(\"main\", 1, 2, 3, 4);" << std::endl;
	MyTextView tv3("main", 1, 2, 3, 4);
	std::cout << "\n****************** main return ******************" << std::endl;
	return 0;
#endif	
	
#if 0
	std::cout << "****************** polymorphism ******************\n" << std::endl;
	
	char my_text[16] = "amo";
	MyTextView tv(my_text, 0, 2, 0, 4);
	
	//tv.showSuperField();
	//tv.left = 111; //error due to access the protected member of superclass inherited private
	tv.arg = 222;    //fine to access the public member of superclass inherited public
	std::cout << "[main]: ... going to tv.showPosition()" << std::endl;
	tv.showPosition();
	MyTextView* ptv = &tv;
	std::cout << "[main]: ... going to ptv->showPosition()" << std::endl;
	ptv->showPosition();
	MyView* pv = &tv;
	std::cout << "[main]: ... going to pv->showPosition()" << std::endl;
	pv->showPosition();

	std::cout << "****************** static override ******************\n" << std::endl;
	//tv.displayLayout(10, 50, 30, 80);
	tv.onLayout(1, 10, 50, 30, 80);
	
	std::cout << "****************** dynamic override ******************\n" << std::endl;
	MyView *view;
	view = &tv;
	if(view) view->onLayout(1, 10, 50, 30, 80);
	//updateView(view, 1, 22, 33, 44, 55);
	
	std::cout << "\n****************** main return ******************" << std::endl;
	return 0;
#endif

#if 0
	std::cout << "****************** about C++ reference ******************\n" << std::endl;
	//std::cout << "... going to create mathA" << std::endl;
	//MyMath mathA(11);
	//std::cout << "... going to create mathB" << std::endl;
	//MyMath mathB(mathA);
	std::cout << "\ngoing to MyMath mathC(33)\n" << std::endl;
	MyMath mathC(33);
	int	data[6] = {1, 2, 3, 4, 5, 6};
	std::cout << "sizeof(data):" << sizeof(data) << " and sizeof(data[0]):" << sizeof(data[0]) << std::endl;
	mathC.setData(data, sizeof(data)/sizeof(data[0]));
	std::cout << "object mathC:" << &mathC << std::endl;
	
#if 0	
	std::cout << "\ngoing to MyMath& mathD = mathC\n" << std::endl;
	MyMath& mathD = mathC;
	std::cout << "reference mathD:" << &mathD << std::endl;
	
	std::cout << "\ngoing to MyMath& mathE1 = mathC.decodeWithRef(mathC)\n" << std::endl;
	MyMath& mathE1 = mathC.decodeWithRef(mathC); //no calling to copy constructor
	std::cout << "reference mathE1:" << &mathE1 << std::endl;
	
	std::cout << "\ngoing to MyMath& mathE2 = mathC.decode(mathC)\n" << std::endl;
	MyMath& mathE2 = mathC.decode(mathC); //invokes ONE calling to copy constructor for parameter duplicating 
	std::cout << "reference mathE2:" << &mathE2 << std::endl;
	
	std::cout << "\ngoing to MyMath mathF1 = mathC.decodeWithRef(mathC)\n" << std::endl;
	//mathC.decodeWithRef(mathC); //no calling to copy constructor
	MyMath mathF1 = mathC.decodeWithRef(mathC);//invokes ONE calling to copy constructor for object creating
	std::cout << "... object mathF1:" << &mathF1 << std::endl;
	
	std::cout << "\ngoing to MyMath mathF2 = mathC.decode(mathC)\n" << std::endl;
	MyMath mathF2 = mathC.decode(mathC);//invokes TWO callings to copy constructor for object creating and  parameter duplicating 
	std::cout << "object mathF2:" << &mathF2 << std::endl;
	std::cout << "mathF2:" << mathF2;
#endif
	
	std::cout << GREEN << "\ngoing to 'MyMath mathRVO = mathC.decodeWithRefRVO(mathC)'\n" << WHITE <<std::endl;
	MyMath mathRVO = mathC.decodeWithRefRVO(mathC);
	std::cout << "mathRVO:" << mathRVO;
	
	std::cout << GREEN << "\ngoing to 'MyMath mathRef& = mathC.decodeWithRefReturnRef(mathC)'\n" << WHITE <<std::endl;
	MyMath& mathRef = mathC.decodeWithRefReturnRef(mathC);
	std::cout << "mathRef:" << mathRef;
	
	std::cout << "\n****************** main return ******************" << std::endl;
	return 0;
#endif
	
#if 0
	std::cout << "****************** operator override ******************\n" << std::endl;
	
#if 0
	std::cout << "\n****************** class override ******************\n" << std::endl;
	MyMath mMath1(11);
	MyMath mMath2(22);
	//std::cout << "[main]: ... going to ref1 = mMath1.operator+(mMath2)" << std::endl;
	//MyMath& ref1 = mMath1.operator+(mMath2);
	//std::cout << "[main]: ... now ref1.getNumber():" << ref1.getNumber() << std::endl;
	
	std::cout << "[main]: ... going to ref2 = = mMath1 + mMath2" << std::endl;
	MyMath& ref2 = mMath1 + mMath2;
	std::cout << "[main]: ... now ref2.getNumber():" << ref2.getNumber() << std::endl;
	std::cout << "[main]: ... now mMath1.getNumber():" << mMath1.getNumber() << std::endl;
	
	std::cout << "[main]: ... going to MyMath& m4 = mMath1++" << std::endl;
	MyMath& m4 = mMath1++;
	std::cout << "[main]: ... now m4.getNumber():" << m4.getNumber() << std::endl;
	std::cout << "[main]: ... now mMath1.getNumber():" << mMath1.getNumber() << std::endl;
	
	//std::cout << "[main]: ... going to mResult = mResult->operator++()" << std::endl;
	//mResult = mResult->operator++();
	//std::cout << "[main]: ... now mResult->operator++():" << mResult->getNumber() << std::endl;
	
	//std::cout << "[main]: ... going to mResult = mResult->operator--(0)" << std::endl;
	//mResult = mResult->operator--(0);
	//std::cout << "[main]: ... now mResult->getNumber():" << mResult->getNumber() << std::endl;
	//if(mResult) delete mResult;
#endif

#if 0
	std::cout << "\n****************** friend override ******************\n" << std::endl;
	int ret_sub = mMath1 - mMath2;
	std::cout << "[main]: ... mMath1 - mMath2:" << ret_sub << std::endl;
	operator++(mMath1);
	std::cout << "[main]: ... now  mMath1.getNumber():" << mMath1.getNumber() << std::endl;
#endif	

#if 0
	std::cout << "****************** = override ******************\n" << std::endl;
	std::cout << "[main]: ... going to MyMath model(100)" << std::endl;
	MyMath model(100);
	int	data[6] = {1, 2, 3, 4, 5, 6};
	int *test;
	model.setData(data, sizeof(data)/sizeof(data[0]));
	model.getData(test);
	
#if 0
	std::cout << "[main]: ... going to MyMath tmp(444)" << std::endl;
	MyMath tmp(444);
	std::cout << "[main]: ... going to MyMath &mock = tmp.operator=(model)" << std::endl;
	MyMath &mock = tmp.operator=(model); //not refer to model for override operator =
	std::cout << "[main]: ... now mock:" << &mock << ", tmp:" << &tmp << " and model:" << &model << std::endl;
	std::cout << "[main]: ... now mock.getNumber():" << mock.getNumber() << ", tmp.getNumber():" << tmp.getNumber() << " and model.getNumber():" << model.getNumber() << std::endl;
#elif 1
	std::cout << "[main]: ... going to MyMath tmp(555)" << std::endl;
	MyMath tmp(555);
	std::cout << "[main]: ... going to tmp = model" << std::endl;
	tmp = model;
	std::cout << "[main]: ... now tmp:" << &tmp << " and model:" << &model << std::endl;
	std::cout << "[main]: ... now tmp.getNumber():" << tmp.getNumber() << " and model.getNumber():" << model.getNumber() << std::endl;
#elif 0
    std::cout << "[main]: ... going to MyMath &mock = model;" << std::endl;
	MyMath &mock = model;
	std::cout << "[main]: ... now mock:" << &mock << " and model:" << &model << std::endl;
	std::cout << "[main]: ... now mock.getNumber():" << mock.getNumber() << " and model.getNumber():" << model.getNumber() << std::endl;
#else	
	std::cout << "[main]: ... going to MyMath mock = model" << std::endl;
	MyMath mock = model;
	std::cout << "[main]: ... now mock:" << &mock << " and model:" << &model << std::endl;
	std::cout << "[main]: ... now mock.getNumber():" << mock.getNumber() << " and model.getNumber():" << model.getNumber() << std::endl;
	mock.getData(test);
	std::cout << "[main]: ... now test[0] :" << test[0] << std::endl;
	std::cout << "[main]: ... now test[1] :" << test[1] << std::endl;
	std::cout << "[main]: ... now test[2]):" << test[2] << std::endl;	
#endif
	
	std::cout << "\n****************** main return ******************" << std::endl;
	return 0;
#endif

#endif

#if 0
#if 0
	std::cout << "****************** stream: get() ******************" << std::endl;
	//std::cout << myostream << std::cin.get() << std::endl;
	std::cout << "std::cin.get():" << std::cin.get() << std::endl;
	/**
	 * The cin object in C++ is an object of class istream.
	 * It is used to accept the input from the standard input device i.e. keyboard.
	 */
	std::cin.get(); //discard '\n' left in stream buffer
	
	/**
	 * Strings are actually one-dimensional array of characters terminated by a null character '\0'.
	 * Thus a null-terminated string contains the characters that comprise the string followed by a null.
     * 
	 * The following declaration and initialization create a string consisting of the word "Hello".
	 * To hold the null character at the end of the array, the size of the character array containing
	 * the string is one more than the number of characters in the word "Hello."
	 */
	char str1[4];
	std::cout << "****************** stream: get(char &) *** not more than " << sizeof(str1)-1 << " words ***************" << std::endl;
	for(int i=0; i<sizeof(str1); i++){
		std::cin.get(str1[i]); 
		if(str1[i] == '\n') {
			std::cout << "str1[" << i << "] == \\n and set as \\0" << std::endl;
			str1[i] = '\0';
			break;
		}
		if(str1[i] == '\0') {
			std::cout << "str1[" << i << "] == \\0 and set as \\0" << std::endl;
			str1[i] = '\0';
			break;
		}
		if (i == sizeof(str1)-1) {
			std::cout << "" << i << " is the last index and set as \\0" << std::endl;
			str1[i] = '\0';
			break;
		}
	}
	std::cout << "str1:" << str1 << std::endl;
	
	char str2[8];	
	std::cout << "****************** stream: get(char*, int, char) *** not more than " << sizeof(str2)-1 << " words ***************" << std::endl;
	std::cin.get(str2, 8); //maximum number of characters to write to str2 (including the terminating null character).
	std::cout << "str2:" << str2 << std::endl;
#if 1	
	std::cin.get(); //discard '\n' left in stream buffer
#else	
	char tmp;
	std::cin.get(tmp); //pick up '\n' left in stream buffer
	if(tmp == '\n') std::cout << "tmp == \\n:" << tmp << std::endl;
	if(tmp == '\0') std::cout << "tmp == \\0:" << tmp << std::endl;
#endif	

	std::cout << "****************** stream: getline(char*, int, char) ******************" << std::endl;
	char str3[8] = {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'};	
	std::cin.getline(str3, 8); //getline() doesn't leave '\n' in stream buffer
	std::cout << str3 << std::endl;;
#if 0
	std::cin.get(); //discard '\n' left in stream buffer
#else
	char tmp;
	std::cin.get(tmp); //pick up '\n' left in stream buffer
	if(tmp == '\n') std::cout << "tmp == \\n:" << tmp << std::endl;
	else if(tmp == '\0') std::cout << "tmp == \\0:" << tmp << std::endl;
	else std::cout << "tmp:" << tmp << std::endl;
#endif	
#endif		

#if 0
	std::vector<char> v;
	cout << GREEN << "going to input" << WHITE << endl;
	input(v);
	cout << GREEN << "going to output:" << v.size() << WHITE << endl;
	output(v);
#endif

#if 0
	std::cout << "****************** i/o operator overload ******************" << std::endl;
	std::cout << "going to MyMath desc(999)" << std::endl;
	MyMath desc(999);
	int	data_desc[6] = {10, 20, 30, 40, 50, 60};
	desc.setData(data_desc, sizeof(data_desc)/sizeof(data_desc[0]));
	std::cout << "going to operator<<(std::cout, desc)" << std::endl;
	operator<<(std::cout, desc);
	std::cout << "going to std::cout << desc;" << std::endl;
	std::cout << desc;
	std::cout << "going to std::cin >> desc;" << std::endl;
	std::cin >> desc;
	std::cout << "going to std::cout << desc;" << std::endl;
	std::cout << desc;
#endif

	std::cout << "\n****************** main return ******************" << std::endl;
	return 0;
#endif
	
#if 0
	std::cout << "\n****************** iofstream ******************\n" << std::endl;
	/**
	 * write to fos
	 */
#if 1
	int	data_fos[6] = {10, 20, 30, 40, 50, 60};
	//std::cout << "sizeof(data_fos):" << sizeof(data_fos) << " and sizeof(data_fos[0]):" << sizeof(data_fos[0]) << std::endl;
	std::cout << "going to std::ofstream fos(test.log)" << std::endl;
	std::ofstream fos("test.log");
	for(int i=0; i<sizeof(data_fos)/sizeof(data_fos[0]); i++) {
		std::cout << "going to fos << std::dec << " << data_fos[i] << std::endl;
		fos << std::dec << data_fos[i] << ' '; 
	}
	std::cout << "going to fos << amo_test" << std::endl;
	fos << "amo_test";
	std::cout << "going to fos.close()" << std::endl;
	fos.close();
#else 	
	std::cout << "going to std::ofstream fos(temp.log)" << std::endl;
	std::ofstream fos("temp.log");
	if (!fos) {
		std::cout << "open output file failed" << std::endl;
		std::cout << "\n****************** main return ******************" << std::endl;
		return 0;
	}
	fos << "amo enter some text";
	std::cout << "going to fos.close()" << std::endl;
	fos.close();
#endif

	/**
	 * read from fis
	 */
#if 1
	std::cout << "going to std::ifstream fis" << std::endl;
	std::ifstream fis;
	std::cout << "going to fis.open(test.log, std::ifstream::in)" << std::endl;
	fis.open("test.log", std::ifstream::in);
	if(!fis.fail()) std::cout << "open file succeeded" << std::endl;
	else std::cout << "open file failed:" << fis.fail() << std::endl;
	
	int buf[6];
	char str_buf[256];
	for(int i=0; i<sizeof(buf)/sizeof(buf[0]); i++) { 
		std::cout << "going to fis >> buf[" << i << "]"  << std::endl;
		fis >> buf[i];
	}
	std::cout << "going to fis.get(str_buf, 16)" << std::endl;
	fis.get(str_buf, 16);
	//fis.getline(str_buf, 16);
	
#else 
	std::cout << "going to std::ifstream fis(temp.log)" << std::endl;
	std::ifstream fis("temp.log");
	if (!fis) {
		std::cout << "open input file failed" << std::endl;
		std::cout << "\n****************** main return ******************" << std::endl;
		return 0;
	}
	char str_buf[16] = {'b','b','b','b'};
	//std::cout << "going to fis >> str_buf" << std::endl;
	//fis >> str_buf;
	//std::cout << "going to fis.get(str_buf, " << sizeof(str_buf)*sizeof(str_buf[0]) << ")" << std::endl;
	//fis.get(str_buf, sizeof(str_buf)*sizeof(str_buf[0]));
	std::cout << "going to fis.get(str_buf[0])" << std::endl;
	fis.get(str_buf[0]);
#endif	
	
    /**
	 * display
	 */
#if 1
	for(int i=0; i<sizeof(buf)/sizeof(buf[0]); i++) std::cout << "buf[" << i << "]:" << buf[i] << std::endl; 	
	std::cout << "str_buf:" << str_buf << std::endl;
#else
	std::cout << "str_buf:" << str_buf << std::endl;
#endif
	std::cout << "going to fis.close()" << std::endl;
	fis.close();
	
	//std::cout << "\n****************** main return ******************" << std::endl;
	//return 0;
#endif

#if 0
	std::cout << "\n****************** iofstream with get()/put() ******************\n" << std::endl;
#if 0
	if(argc != 3) {
		std::cout << "not supported copy file command" << std::endl;
		return 0;
	}
	std::cout << "src file :" << argv[1] << std::endl;	
	std::cout << "dest file:" << argv[2] << std::endl;		
	
	std::ifstream mFin(argv[1], std::ios::binary|std::ios::in);
	std::ofstream mFout(argv[2], std::ios::binary|std::ios::out);
#else
	std::cout << "going to mFin(in.log)" << std::endl;
	std::ifstream mFin("in.log", std::ios::binary|std::ios::in);
	std::cout << "going to mFout(out.log)" << std::endl;
	std::ofstream mFout("out.log", std::ios::binary|std::ios::out);
#endif	
	std::streampos pos;
	/**
	 * std::istream::tellg returns the position of the current character in the input stream.
	 */
	pos	= mFin.tellg();
	std::cout << "beginning pos of mFin :" << pos << std::endl;
	/**
	 * std::ostream::tellp() returns the position of the current character in the output stream
	 */
	pos = mFout.tellp(); 
	std::cout << "beginning pos of mFout:" << pos << std::endl;	
	char tmp;	
	int	mFinSize;	
	
	while(0){
		std::cout << "going to mFin.get(tmp)" << std::endl;
		mFin.get(tmp);
		if(mFin.eof()) {
			std::cout << "mFin.eof() returned true" << std::endl;
			break; //std::istream::get() set fail bit flag when returns EOF
		}
		std::cout << "going to mFout.put(tmp)" << std::endl;
		mFout.put(tmp);
	}
	/**
	 * std::istream::get() returns the first signature that the character read
	 * , or the end-of-file value (EOF) if no characters are available in the stream
	 * All other signatures always return *this. 
	 * Note that this return value can be checked for the state of the stream
	 *(see CASTING a stream to bool for more info: Returns whether an error flag is set (either failbit or badbit)).
	 */
	while(mFin.get(tmp)){
		std::cout << "going to mFout.put(tmp):" << tmp << " and now pos of input stream:" << mFin.tellg()  << std::endl;
		mFout.put(tmp);
	}
	
	/**
	 * std::ios::clear(iostate state = goodbit) sets a new value for the stream's internal error state flags.
	 * If state is goodbit (which is zero) all error flags are cleared.
	 */
	mFin.clear();
	mFout.clear();
	
	std::cout << "going to mFin.seekg(0, mFin.end)" << std::endl;
	/**
	 *std::istream::seekg() sets the position of the next character to be extracted from the input stream.
	 */
	mFin.seekg(0, mFin.end);
	/**
	 * std::istream::tellg() gets position in input sequence, returns the position of the current character in the input stream
	 * Internally, the function accesses the input sequence by first constructing a sentry object without evaluating it.
	 * Then, if member fail returns true, the function returns -1.
	 */
	mFinSize = mFin.tellg();
	std::cout << "now pos of input stream:" << mFin.tellg() << std::endl;
	std::cout << "going to mFin.seekg(4, mFin.beg)" << std::endl;
	mFin.seekg(4, mFin.beg);//offset to filebuf[4]
	std::cout << "now pos of input stream:" << mFin.tellg() << std::endl;
	
	std::cout << "\n****************** iofstream with read()/write() ******************\n" << std::endl;
	mFin.seekg(0, mFin.beg);
	mFout.seekp(0, mFout.beg);
	/**
	 * std::istream::read() extracts n characters from the stream and stores them in the array pointed to by s.
	 * This function simply copies a block of data, without checking its contents nor appending a null character at the end.
	 * and returns the istream object (*this).
	 */
	char content[mFinSize*4];
	memset(content, 0, sizeof(content));
	int length_fis = mFin.seekg(0, mFin.end).tellg();
	mFin.seekg(0, mFin.beg);
	std::cout << "created a char content["<< sizeof(content) << "]" << std::endl;
	std::cout << "after mFin.read(content, " << length_fis << "), pos of input stream:" << mFin.read(content, length_fis).tellg() << std::endl;
	char appends[32];
	strcpy(appends, "\nappend_end\0");
	std::cout << "now content:" << content << std::endl;
	strncat(content, appends, strlen(appends));
	std::cout << "now content:" << content << std::endl;
	/** 
	 * std::ostream::write() simply copies a block of data, without checking its contents:
     * The array may contain null characters, which are also copied without stopping the copying process.
	 * and returns the ostream object (*this).
	 */
	std::cout << "after mFout.write(content, " << strlen(content) << "), pos of output stream:" << mFout.write(content, strlen(content)).tellp() << std::endl;

	mFin.close();
	mFout.close();
	std::cout << "\n****************** main return ******************" << std::endl;
	return 0;
#endif

#if 0
	std::cout << "\n****************** namespace ******************\n" << std::endl;
	char path1[32] = "myfis.log";
	char path2[32] = "myfos.log";
	mystd::myfstream::ifstream fis(path1);
	mystd::myfstream::ofstream fos(path2);
	
	//mystd::myfstream::ifstream::setUser(10);
	//std::cout << "input file stream user:" << mystd::myfstream::ifstream::getUser() << std::endl;
	fis.setUser(100);
	std::cout << "input file stream user:" << fis.getUser() << std::endl;
	
	//mystd::myfstream::ofstream::setUser(10);
	//std::cout << "output file stream user:" << mystd::myfstream::ofstream::getUser() << std::endl;
	fos.setUser(100);
	std::cout << "input file stream user:" << fos.getUser() << std::endl;
	
	char content[16] = "my_namespace";
	
	fos.seekp(0, 0);
	fos.write(content, strlen(content)+1);
	
	fis.seekg(30, 0);
	fis.read(content, strlen(content)+1);
	std::cout << "going to std::cout << fis" << std::endl;
	std::cout << fis;
	std::cout << "going to std::cout << fos" << std::endl;
	std::cout << fos;
	
	std::cout << "going to std::cin >> fis" << std::endl;
	std::cin >> fis;
	
	std::cout << "going to std::cout << fis"<< std::endl;
	std::cout << fis;
	
	
	
	/*
	fis.seekg(30, 0);
	fis.read(content, strlen(content)+1);
	fos.seekp(30, 0);
	fos.write(content, strlen(content)+1);
	*/
	std::cout << "\n****************** main return ******************" << std::endl;
	return 0;
#endif

#if 0
	std::cout << "\n****************** new/delete ******************\n" << std::endl;
	int (*p)[2]; //address shift is 2 of times of sizeof(int) between p and p+1
	p = new int[3][2] {{11,12}, {21,22}, {31,32}};
	//int data[3][2] {{11,12}, {21,22}, {31,32}};
	//int (*p)[2] = data; //address shift is 2 of times of sizeof(int) between p and p+1
	std::cout << "... beginning p :" << p << std::endl;
	std::cout << "... beginning p+1:" << p+1 << std::endl;
	std::cout << "... beginning p+2:" << p+2 << std::endl;
	for (int i=0;i<3;i++) {
		for (int j=0;j<2;j++) {
			std::cout << "*(p+" << i << ")+" << j << ":" << *(p+i)+j << std::endl;
			std::cout << "p[" << i << "]+" << j << "  :" << p[i]+j << std::endl;
			std::cout << "p[" << i << "]" << "[" << j << "]:" << (p[i][j]) << std::endl;
		}
	}
	
	std::cout << "going to MyMath *m = new MyMath(999) that would invoke constructor" << std::endl;
	MyMath *m = new MyMath(999);
	std::cout << "going to delete m that would invoke deconstructor" << std::endl;
	delete m;
	
	std::cout << "\n****************** main return ******************" << std::endl;
	return 0;
#endif
	
#if 0	
	std::cout << "****************** static laboratory ******************" << std::endl;
	MyMath::user = 99;
	MyMath::setUser(99);
	std::cout << "math user:" << MyMath::getUser() << std::endl;
#endif

#if 0
	std::cout << "****************** STL laboratory ******************/n" << std::endl;
#endif	
	
#if 0
	/**
	 * template < class T, class Alloc = allocator<T> > class vector; // generic template
	 *
	 * Vectors are sequence containers representing arrays that can change in size.
	 *
     * Just like arrays, vectors use contiguous storage locations for their elements
	 * , which means that their elements can also be accessed using offsets on regular pointers to its element, and just as efficiently as in arrays
	 * . But unlike arrays, their size can change dynamically, with their storage being handled automatically by the container.
	 *
	 * Internally, vectors use a dynamically allocated array to store their elements. 
	 * This array may need to be reallocated in order to grow in size when new elements are inserted
	 * , which implies allocating a new array and moving all elements to it. 
	 * This is a relatively expensive task in terms of processing time, thus vectors do not reallocate each time an element is added to the container.
     * Instead, vector containers may allocate some extra storage to accommodate for possible growth
	 * , and thus the container may have an actual capacity greater than the storage strictly needed to contain its elements (i.e., its size).
     *
	 * Therefore, compared to arrays, vectors consume more memory in exchange for the ability to manage storage and grow dynamically in an efficient way.
     *
	 * Compared to the other dynamic sequence containers (deques, lists and forward_lists)
	 * , vectors are very efficient accessing its elements (just like arrays) and relatively efficient adding or removing elements from its end.
     * For operations that involve inserting or removing elements at positions other than the end, they perform worse than the others
	 * , and have less consistent iterators and references than lists and forward_lists.
	 */
	std::cout << GREEN << "****************** vector laboratory ******************\n" << WHITE << std::endl;
	std::vector<MyMath> vector1;
	std::vector<MyMath>::iterator it;
	std::cout << GREEN << "going to MyMath utility(10)" << WHITE << std::endl;
	MyMath utility(10);
	for(int i=0; i<2; i++){
		std::cout << GREEN << "going to vector1.push_back(utility) and i:" << i  << WHITE << std::endl;
		utility.setNumber(utility.getNumber()+1);
		/**
		 * void std::vector::push_back(const value_type& val) 
		 * Effectively increases the container size by one, which causes an automatic reallocation of the allocated storage space
		 * if and only if the new vector size surpasses the current vector capacity.
		 *
		 * Member type value_type is the type of the elements in the container
		 * , defined in vector as an alias of its first template parameter (T).
		 */
		vector1.push_back(utility);
	}
	for(int j=0; j<vector1.size(); j++){
		std::cout << YELLOW << "after push_back() &vector1[" << j << "]:" << &vector1[j] << " and vector1[" << j << "]:" << vector1[j].getNumber() << WHITE << std::endl;
	}
	
	/**
	 * std::vector::begin()
	 * Returns an iterator pointing to the first element in the vector.
	 *
	 * std::vector::end()
	 * Returns an iterator referring to the past-the-end element in the vector
	 * , the past-the-end element is the theoretical element that would follow the last element in the vector which shall not be dereferenced.
	 */
	 
	/**
	 * Iterator: a pointer-like object that can be incremented with ++, dereferenced with *, and compared against another iterator with != 
	 * using operator*, *it dereferences iterator and obtains the value that it refers to (except output iterator).
	 * using operator->, it-> dereferences iterator and accesses the member value of the object that it refers to including calling a member function 
	 */ 
	for (it=vector1.begin(); it!=vector1.end(); it++) {
		/**
		 * dereferences *iterator to access the object which is one of container element pointed by iterator
		 */
		std::cout << GREEN << "going dereference *iterator to access object" << WHITE << std::endl;
		MyMath &ref = *it;
		std::cout << GREEN << "going ref.setNumber(1000-ref.getNumber());" << WHITE << std::endl;
		ref.setNumber(1000-ref.getNumber());
		int number = ref.getNumber();
		std::cout << YELLOW << "&ref:" << &ref << " and ref.getNumber():" << ref.getNumber() << WHITE << std::endl;
	}
	
	/**
	 * const_iterator
	 */
	std::cout << GREEN << "\ngoing to std::vector<MyMath>::const_iterator const_it = vector1.begin()" << WHITE << std::endl;
	std::vector<MyMath>::const_iterator const_it = vector1.begin(); 
	const MyMath &tmp = *const_it;
	//tmp.setNumber(2222); //err: discard const qualifier
	std::cout << GREEN << "going to const_it++" << WHITE << std::endl;
	const_it++;
	std::cout << YELLOW << "(*const_it).getNumber()" << (*const_it).getNumber() << WHITE << std::endl;
	
	/**
	 * const iterator
	 */
	std::cout << GREEN << "\ngoing to const std::vector<MyMath>::iterator it_const = vector1.begin()" << WHITE << std::endl;
	const std::vector<MyMath>::iterator it_const = vector1.begin();
	//it_const++; //err: discard const qualifier
	std::cout << YELLOW << "(*it_const).getNumber()" << (*it_const).getNumber() << WHITE << std::endl;
	
	/**
	 * std::sort() sorts the elements in the range [first, last) into ascending order
     * , first and last are random access iterators to the initial and final positions of the sequence to be sorted.
	 * The range used is [first, last), which contains all the elements between first and last
	 * , including the element pointed by first but not the element pointed by the last.
	 */
	for(vector<MyMath>::iterator it=vector1.begin(); it!=vector1.end(); it++){
		std::cout << YELLOW <<  "(using operator->) before sort() vector1[" << std::distance(vector1.begin(), it) << "]:" << it->getNumber() << " at " << &*it << WHITE << std::endl;
	} 
	cout << GREEN << "going to sort(vector1.begin(), vector1.end())" << WHITE << endl;
	sort(vector1.begin(), vector1.end());
	
	for(vector<MyMath>::iterator it=vector1.begin(); it!=vector1.end(); it++){
		std::cout << YELLOW <<  "(using operator.) after sort() vector1[" << std::distance(vector1.begin(), it) << "]:" << (*it).getNumber() << " at " << &(*it) << WHITE << std::endl;
	}
	
	/**
	 * iterator std::vector::erase(iterator position);
     * iterator std::vector::erase(iterator first, iterator last)
	 * Removes from the vector either a single element (position) or a range of elements ([first,last)).
	 * This effectively reduces the container size by the number of elements removed, which are destroyed.
	 * Because vectors use an array as their underlying storage, erasing elements in positions other than the vector end
	 * causes the container to relocate all the elements after the segment erased to their new positions.
	 * This is generally an inefficient operation compared to the one performed for the same operation by other kinds of sequence containers
	 * (such as list or forward_list).
	 * Return value:
     * An iterator pointing to the new location of the element that followed the last element erased by the function call.
	 * This is the container end if the operation erased the last element in the sequence.
     * Member type iterator is a random access iterator type that points to elements.
	 */
	for(vector<MyMath>::iterator it=vector1.begin(); it!=vector1.end(); it++){
		std::cout << YELLOW <<  "before erase() vector1[" << std::distance(vector1.begin(), it) << "]:" << (*it).getNumber() << WHITE << std::endl;
	}
	std::cout << GREEN <<  "going to erase()" << WHITE << std::endl;
	vector1.erase(vector1.begin());
	for(vector<MyMath>::iterator it=vector1.begin(); it!=vector1.end(); it++){
		std::cout << YELLOW <<  "after erase() vector1[" << std::distance(vector1.begin(), it) << "]:" << (*it).getNumber() << WHITE << std::endl;
	}
	std::cout << GREEN << "\n****************** main return ******************" << WHITE << std::endl;
	return 0;
#endif

#if 0
	/**
     * template < class T, class Alloc = allocator<T> > class list;	
	 *
	 * List containers are implemented as doubly-linked lists.
	 * Doubly linked lists can store each of the elements they contain in different and unrelated storage locations.
	 * The ordering is kept internally by the association to each element of a link to the element preceding it and a link to the element following it.
	 *
	 * Compared to other base standard sequence containers (array, vector and deque)
	 * , lists perform better in inserting, extracting and moving elements in any position within the container for which an iterator has been obtained
	 * , and therefore also in algorithms that make intensive use of these, like sorting algorithms.
     *
     * The main drawback of lists and forward_lists compared to other containers is that they lack direct access to the elements by their position;
	 * For example, to access the sixth element in a list, one has to iterate from a known position (like the beginning or the end) to that position
	 * , which takes linear time in the distance between these. 
	 * They also consume some extra memory to keep the linking information associated to each element
     * (which may be an important factor for large lists of small-sized elements).
	 */
	std::cout << GREEN << "****************** list laboratory ******************\n" << WHITE << std::endl;
	std::list<MyMath> list1;
	std::list<MyMath> list2;
	std::list<MyMath>::iterator it1;
	std::list<MyMath>::iterator it2;
	
	std::cout << YELLOW << "" << WHITE << std::endl;
	/**
     * std::list::push_back(const value_type& val) adds a new element at the end of the list container, after its current last element.
	 * The content of val is copied (or moved) to the new element, using copy constructor.
     * This effectively increases the container size by one.
	 * Member type value_type is the type of the elements in the container, defined in list as an alias of its first template parameter (T).
	 */
	 
	for(int i=0; i<2; i++){
		std::cout << GREEN << "going to MyMath math(i)" << WHITE << std::endl;
		MyMath math(i);
		std::cout << GREEN << "going to list1.push_back(math)" << WHITE << std::endl;
		list1.push_back(math);
	}
	for(it1=list1.begin(); it1!=list1.end(); it1++){
		std::cout << YELLOW <<  "after push_back() list1[" << std::distance(list1.begin(), it1) << "]:" << (*it1).getNumber() << WHITE << std::endl;
	}
	
	std::cout << YELLOW << "" << WHITE << std::endl;
	/**
	 * std::list::assign(InputIterator first, InputIterator last) (1)
	 * std::list::assign(size_type n, const value_type& val) (2)
	 * Assigns new contents to the list container, replacing its current contents, and modifying its size accordingly.
     * In the range version (1), the new contents are elements constructed from each of the elements in the range between first and last, in the same order.
     * In the fill version (2), the new contents are n elements, each initialized to a copy of val
	 * , using operator=(value_type& val) if the element at a position within container has been already constructed one, otherwise using copy constructor.
     * Any elements held in the container before the call are destroyed and replaced by newly constructed elements (no assignments of elements take place).
	 *
	 * first, last: input iterators to the initial and final positions in a sequence. The range used is [first,last)
	 *, which includes all the elements between first and last, including the element pointed by first but not the element pointed by last.
     */	 
	for (int i=0;i<3; i++) {
		std::cout << GREEN << "going to list2.push_back(MyMath(" << i << "+10))" << WHITE << std::endl;
		list2.push_back(MyMath(i+10));
	}
	for(it2=list2.begin(); it2!=list2.end(); it2++){
		std::cout << YELLOW << "before assign() list2[" << std::distance(list2.begin(), it2) << "]:" << (*it2).getNumber() << WHITE << std::endl;
	}
	std::cout << GREEN << "going to list2.assign(list1.begin(), list1.end())" << WHITE << std::endl;
	list2.assign(list1.begin(), list1.end());
	for(it2=list2.begin(); it2!=list2.end(); it2++){
		std::cout << YELLOW << "after assign() list2[" << std::distance(list2.begin(), it2) << "]:" << (*it2).getNumber() << WHITE << std::endl;
	}
	std::cout << GREEN << "going to list2.assign(3, MyMath(555))" << WHITE << std::endl;
	list2.assign(3, MyMath(555));
	for(it2=list2.begin(); it2!=list2.end(); it2++){
		std::cout << YELLOW << "after assign() list2[" << std::distance(list2.begin(), it2) << "]:" << (*it2).getNumber() << WHITE << std::endl;
	}
	
	std::cout << YELLOW << "" << WHITE << std::endl;
	/**
	 * std::list::resize(size_type n, value_type val = value_type()) resizes the container so that it contains n elements.
     * If n is smaller than the current container size, the content is reduced to its first n elements, removing those beyond (and destroying them).
     * If n is greater than the current container size, the content is expanded by inserting at the end as many elements as needed to reach a size of n.
	 * If val is specified, the new elements are initialized as copies of val using copy constructor, otherwise, they are value-initialized.
     * Notice that this function changes the actual content of the container by inserting or erasing elements from it.
     * n: New container size, expressed in number of elements. Member type size_type is an unsigned integral type.
	 * val: Object whose content is copied to the added elements in case that n is greater than the current container size.
     *      If not specified, the default constructor is used instead.
     *      Member type value_type is the type of the elements in the container, defined in list as an alias of the first template parameter (T). 
	 */
	std::cout << YELLOW << "before resize(), list2.size():" << list2.size() << WHITE << std::endl;
	for(it2=list2.begin(); it2!=list2.end(); it2++){
		std::cout << YELLOW << "before resize() list2[" << std::distance(list2.begin(), it2) << "]:" << (*it2).getNumber() << WHITE << std::endl;
	}
	//list2.resize(1, MyMath(666));
	std::cout << GREEN << "going to list2.resize(5, MyMath(666))" << WHITE << std::endl;
	list2.resize(5, MyMath(666));
	std::cout << YELLOW << "after resize(), list2.size():" << list2.size() << WHITE << std::endl;
	for(it2=list2.begin(); it2!=list2.end(); it2++){
		std::cout << YELLOW << "after resize() list2[" << std::distance(list2.begin(), it2) << "]:" << (*it2).getNumber() << WHITE << std::endl;
	}	
	
	std::cout << YELLOW << "" << WHITE << std::endl;
	/** 
     * std::list::insert(iterator position, const value_type& val)
     * std::list::insert(iterator position, size_type n, const value_type& val)
     * std::list::insert(iterator position, InputIterator first, InputIterator last)
	 * The container is extended by inserting new elements before the element at the specified position.
     * This effectively increases the list size by the amount of elements inserted.
     * The arguments determine how many elements are inserted and to which values they are initialized:
	 * position: Position in the container where the new elements are inserted.
	 * val     : Value to be copied (or moved) to the inserted elements.
	 * n       : Number of elements to insert. Each element is initialized to a copy of val using copy constructor.
	 * first, last: Iterators specifying a range of elements. Copies of the elements in the range [first,last) are inserted at position (in the same order).
	 *              The function template argument InputIterator shall be an input iterator type that points to elements of a type from which value_type objects can be constructed.
	 */
	for(it2=list2.begin(); it2!=list2.end(); it2++){
		std::cout << YELLOW << "before insert() list2[" << std::distance(list2.begin(), it2) << "]:" << (*it2).getNumber() << WHITE << std::endl;
	}
	std::cout << GREEN << "going to list2.insert((++list2.end()), 5, MyMath(999))" << WHITE << std::endl;
	list2.insert((++list2.begin()), 5, MyMath(777));
	for(it2=list2.begin(); it2!=list2.end(); it2++){
		std::cout << YELLOW << "after insert() list2[" << std::distance(list2.begin(), it2) << "]:" << (*it2).getNumber() << WHITE << std::endl;
	}
	
	std::cout << YELLOW << "" << WHITE << std::endl;
	/**
     * std::list::erase(iterator position)
	 * std::list::erase(iterator first, iterator last)
     * Removes from the list container either a single element (position) or a range of elements ([first,last)).
     * This effectively reduces the container size by the number of elements removed, which are destroyed.
     * position   : Iterator pointing to a single element to be removed from the list.
     * first, last: Iterators specifying a range within the list to be removed: [first,last).
	 * return value: An iterator pointing to the element that followed the last element erased by the function call. 
	 *               This is the container end if the operation erased the last element in the sequence.
	 */
	std::cout << GREEN << "going to std::list<MyMath>::iterator it_tmp = list2.end()" << WHITE << std::endl;
	std::list<MyMath>::iterator it_tmp = list2.end();
	std::cout << GREEN << "going to std::advance(it_tmp, -2)" << WHITE << std::endl;
	std::advance(it_tmp, -2);
	std::cout << YELLOW << "(*it_tmp).getNumber():" << (*it_tmp).getNumber() << " and &(*it_tmp) :" << &(*it_tmp) << WHITE << std::endl;
	for(it2=list2.begin(); it2!=list2.end(); it2++){
		std::cout << YELLOW << "before erase() list2[" << std::distance(list2.begin(), it2) << "]:" << (*it2).getNumber() << WHITE << std::endl;
	}
	std::cout << GREEN << "going to list2.erase(it_tmp, --list2.end())" << WHITE << std::endl;
	std::list<MyMath>::iterator it_return =  list2.erase(it_tmp, --list2.end());
	std::cout << YELLOW << "it_return points the element followed the last element erased:" << (*it_return).getNumber() << " and &(*it_return) :" << &(*it_return) << WHITE << std::endl;
	for(it2=list2.begin(); it2!=list2.end(); it2++){
		std::cout << YELLOW << "after erase() list2[" << std::distance(list2.begin(), it2) << "]:" << (*it2).getNumber() << WHITE << std::endl;
	}
	
	std::cout << YELLOW << "" << WHITE << std::endl;
	/** 
	 * std::list::remove(const value_type& val) 
	 * Removes from the container all the elements that compare equal to val.
	 * This calls the destructor of these objects and reduces the container size by the number of elements removed.
	 */
	for(it2=list2.begin(); it2!=list2.end(); it2++){
		std::cout << YELLOW << "before remove() list2[" << std::distance(list2.begin(), it2) << "]:" << (*it2).getNumber() << WHITE << std::endl;
	}
	std::cout << GREEN << "going to list2.remove(MyMath(99))" << WHITE << std::endl;
	list2.remove(MyMath(555)); //call to override operator==
	for(it2=list2.begin(); it2!=list2.end(); it2++){
		std::cout << YELLOW << "after remove() list2[" << std::distance(list2.begin(), it2) << "]:" << (*it2).getNumber() << WHITE << std::endl;
	}
	
	std::cout << YELLOW << "" << WHITE << std::endl;
	/**
     * std::list::splice(iterator position, list& x) 
	 * std::list::splice (iterator position, list& x, iterator i)
	 * std::list::splice (iterator position, list& x, iterator first, iterator last)
	 * Transfers elements from x into the container, inserting them at position.
     * This effectively inserts those elements into the container and removes them from x, altering the sizes of both containers.
	 * The operation does not involve the construction or destruction of any element. They are transferred
	 * , no matter whether x is an lvalue or an rvalue, or whether the value_type supports move-construction or not.
     * The first version (1) transfers all the elements of x into the container.
     * The second version (2) transfers only the element pointed by i from x into the container.
     * The third version (3) transfers the range [first,last) from x into the container.
	 * position: Position within the container where the elements of x are inserted.
     * x: A list object of the same type (i.e., with the same template parameters, T and Alloc).
     *    This parameter may be *this if position points to an element not actually being spliced.
     * i: Iterator to an element in x. Only this single element is transferred.
     * first,last: Iterators specifying a range of elements in x. Transfers the elements in the range [first,last) to position.
	 */
	for(it1=list1.begin(); it1!=list1.end(); it1++){
		std::cout << YELLOW << "before splice() list1[" << std::distance(list1.begin(), it1) << "]:" << (*it1).getNumber() << WHITE << std::endl;
	} 
	for(it2=list2.begin(); it2!=list2.end(); it2++){
		std::cout << YELLOW << "before splice() list2[" << std::distance(list2.begin(), it2) << "]:" << (*it2).getNumber() << WHITE << std::endl;
	}
	std::cout << GREEN << "going to list2.splice(--list2.end(), list1, list1.begin(), list1.end())" << std::endl;
	list2.splice(--list2.end(), list1, list1.begin(), list1.end());
	for(it1=list1.begin(); it1!=list1.end(); it1++){
		std::cout << YELLOW << "after splice() list1[" << std::distance(list1.begin(), it1) << "]:" << (*it1).getNumber() << WHITE << std::endl;
	} 
	for(it2=list2.begin(); it2!=list2.end(); it2++){
		std::cout << YELLOW << "after splice() list2[" << std::distance(list2.begin(), it2) << "]:" << (*it2).getNumber() << WHITE << std::endl;
	}
#if 0	
	for(int i=0; i<2; i++){
		std::cout << GREEN << "going to MyMath math(i)" << WHITE << std::endl;
		MyMath math(i);
		std::cout << GREEN << "going to list1.push_back(math)" << WHITE << std::endl;
		list1.push_back(math);
	}
	for(it1=list1.begin(); it1!=list1.end(); it1++){
		std::cout << YELLOW <<  "after push_back() list1[" << std::distance(list1.begin(), it1) << "]:" << (*it1).getNumber() << WHITE << std::endl;
	}
#else	
	std::cout << GREEN << "going to for (int i=1; i<6; i++) list1.insert((list1.begin()), 1, MyMath(10*i+9))" << WHITE << std::endl;
	for (int i=1; i<6; i++) list1.insert((list1.begin()), 1, MyMath(10*i+9));
	for(it1=list1.begin(); it1!=list1.end(); it1++){
		std::cout << YELLOW << "after insert() list1[" << std::distance(list1.begin(), it1) << "]:" << (*it1).getNumber() << WHITE << std::endl;
	}
#endif
	
	std::cout << YELLOW << "" << WHITE << std::endl;
	/**
     * std::list::unique()
     * std::list::unique(BinaryPredicate binary_pred)
     * The version with no parameters (1), removes all but the first element from every consecutive group of equal elements in the container.
     * Notice that an element is only removed from the list container if it compares equal to the element immediately preceding it.
     * The second version (2), takes argument as a specific comparison function that determine the "uniqueness" of an element.
	 * In fact, any behavior can be implemented (and not only an equality comparison)
	 * , but notice that the function will call binary_pred(*i,*(i-1)) for all pairs of elements
	 * (where i is an iterator to an element, starting from the second) and remove i from the list if the predicate returns true.
     * The elements removed are destroyed.
	 */
	for(it2=list2.begin(); it2!=list2.end(); it2++){
		std::cout << YELLOW << "before unique() list2[" << std::distance(list2.begin(), it2) << "]:" << (*it2).getNumber() << WHITE << std::endl;
	}
#if 1	
	std::cout << GREEN << "going to list2.unique(PredicateMyMathEqual())" << WHITE << std::endl;
	list2.unique(PredicateMyMathEqual()); //using PredicateMyMathEqual::operator()(MyMath&,MyMath&) to compare elements if equal
#else	
	std::cout << GREEN << "going to list2.unique()" << WHITE << std::endl;
	list2.unique(); //using MyMath::operator==(const MyMath&) to compare elements if equal
#endif	
	for(it2=list2.begin(); it2!=list2.end(); it2++){
		std::cout << YELLOW << "after unique() list2[" << std::distance(list2.begin(), it2) << "]:" << (*it2).getNumber() << WHITE << std::endl;
	}
	
	std::cout << YELLOW << "" << WHITE << std::endl;
	/**
     * std::list::sort()
     * std::list::sort(Compare comp)
	 * Sorts the elements in the list, altering their position within the container.
     * The sorting is performed by applying an algorithm that uses either operator< (in version (1)) or comp (in version (2)) to compare elements.
	 * This comparison shall produce a strict weak ordering of the elements (i.e., a consistent transitive comparison, without considering its reflexiveness).
     * The resulting order of equivalent elements is stable: i.e., equivalent elements preserve the relative order they had before the call.
     * The entire operation does not involve the construction, destruction or copy of any element object. Elements are moved within the container.
	 * comp: Binary predicate that, taking two values of the same type of those contained in the list
	 *       , returns true if the first argument goes before the second argument in the strict weak ordering it defines, and false otherwise.
     *       This shall be a function pointer or a function object.
	 */
	for(it2=list2.begin(); it2!=list2.end(); it2++){
		std::cout << YELLOW << "before sort() list2[" << std::distance(list2.begin(), it2) << "]:" << (*it2).getNumber() << WHITE << std::endl;
	} 
#if 0
	std::cout << GREEN << "going to list2.sort(PredicateMyMathLess())" << WHITE << std::endl;
	list2.sort(PredicateMyMathLess()); //using PredicateMyMathLess::operator()(MyMath&,MyMath&) to compare elements if equal
#else
	std::cout << GREEN << "going to list2.sort()" << WHITE << std::endl;
	list2.sort(); //using MyMath::operator<(const MyMath&) to compare elements if equal
#endif	
	for(it2=list2.begin(); it2!=list2.end(); it2++){
		std::cout << YELLOW << "after sort() list2[" << std::distance(list2.begin(), it2) << "]:" << (*it2).getNumber() << WHITE << std::endl;
	} 
	
	std::cout << YELLOW << "" << WHITE << std::endl;
	/**
     * std::list::merge(list& x)
     * std::list::merge(list& x, Compare comp)
	 * Merges x into the list by transferring all of its elements at their respective ordered positions into the container (both containers shall already be ordered).
	 * This effectively removes all the elements in x (which becomes empty), and inserts them into their ordered position within container.
	 * (which expands in size by the number of elements transferred). 
	 * The operation is performed without constructing nor destroying any element: they are transferred.
	 * The function does nothing if (&x == this).
	 */
	for(it1=list1.begin(); it1!=list1.end(); it1++){
		std::cout << YELLOW << "before merge() list1[" << std::distance(list1.begin(), it1) << "]:" << (*it1).getNumber() << WHITE << std::endl;
	} 
	for(it2=list2.begin(); it2!=list2.end(); it2++){
		std::cout << YELLOW << "before merge() list2[" << std::distance(list2.begin(), it2) << "]:" << (*it2).getNumber() << WHITE << std::endl;
	} 
#if 1
	std::cout << GREEN << "going to list2.merge(list1, PredicateMyMathLess()))"<< WHITE << std::endl;
	list2.merge(list1, PredicateMyMathLess()); //using PredicateMyMathLess::operator()(MyMath&,MyMath&) to compare elements if equal
#else
	std::cout << GREEN << "going to list2.merge(list1)" << WHITE << std::endl;
	list2.merge(list1); //using MyMath::operator<(const MyMath&) to compare elements if equal
#endif
	for(it1=list1.begin(); it1!=list1.end(); it1++){
		std::cout << YELLOW << "after merge() list1[" << std::distance(list1.begin(), it1) << "]:" << (*it1).getNumber() << WHITE << std::endl;
	} 
	for(it2=list2.begin(); it2!=list2.end(); it2++){
		std::cout << YELLOW << "after merge() list2[" << std::distance(list2.begin(), it2) << "]:" << (*it2).getNumber() << WHITE << std::endl;
	}

	std::cout << YELLOW << "" << WHITE << std::endl;
	/**
	 * std::list::reverse() 
	 * Reverses the order of the elements in the list container.
	 */
	for(it2=list2.begin(); it2!=list2.end(); it2++){
		std::cout << YELLOW << "before reverse() list2[" << std::distance(list2.begin(), it2) << "]:" << it2->getNumber() << WHITE << std::endl;
	}
	std::cout << GREEN << "going to list2.reverse()" << WHITE << std::endl;
	list2.reverse();
	for(it2=list2.begin(); it2!=list2.end(); it2++){
		std::cout << YELLOW << "after reverse() list2[" << std::distance(list2.begin(), it2) << "]:" << it2->getNumber() << WHITE << std::endl;
	}
	std::cout << GREEN << "\n****************** main return ******************" << WHITE << std::endl;
	return 0;
#endif

#if 0 
	/**
	 * template < class T,                     // set::key_type/value_type
     *            class Compare = less<T>,     // set::key_compare/value_compare
     *            class Alloc = allocator<T> > // set::allocator_type
     * class set; 
	 *
	 * Sets are containers that store unique elements following a specific order.
     * In a set, the value of an element also identifies it (the value is itself the key, of type T), and each value must be unique. 
	 * The value of the elements in a set cannot be modified once in the container 
	 * (the elements are always const), but they can be inserted or removed from the container.
     * Internally, the elements in a set are always sorted following a specific strict weak ordering criterion
     * indicated by its internal comparison object (of type Compare).
     * set containers are generally slower than unordered_set containers to access individual elements by their key
	 * , but they allow the direct iteration on subsets based on their order.
     * Sets are typically implemented as binary search trees.
	 */
	std::cout << GREEN << "****************** set laboratory ******************\n" << WHITE << std::endl;
	std::set<MyMath> set1;
	std::set<MyMath>::iterator it1;
	std::set<MyMath>::reverse_iterator it2;
	std::set<MyMath>::iterator it3;
	std::pair<std::set<MyMath>::iterator,bool> ret;
	/**
	 * std::set::key_comp()
	 * Returns a copy of the comparison object used by the container.
     * By default, this is a less object, which returns the same as operator<.
     * This object determines the order of the elements in the container: 
	 * it is a function pointer or a function object that takes two arguments of the same type as the container elements
	 * , and returns true if the first argument is considered to go before the second in the strict weak ordering it defines, and false otherwise.
     * Two elements of a set are considered equivalent if key_comp returns false reflexively (no matter the order in which the elements are passed as arguments).
     * In set containers, the keys to sort the elements are the values themselves, therefore key_comp and its sibling member function value_comp are equivalent.
	 * Return value: The comparison object.
     *               Member type key_compare is the type of the comparison object associated to the container
	 *               , defined in set as an alias of its second template parameter (Compare).
	 */ 
	std::set<MyMath>::key_compare comp = set1.key_comp();
	
	/**
     * pair<iterator,bool> std::set::insert(const value_type& val) - (1)
     * iterator  std::set::insert(iterator position, const value_type& val) - (2)
     * void  std::set::insert(InputIterator first, InputIterator last) - (3)
	 *
	 * Extends the container by inserting new elements, effectively increasing the container size by the number of elements inserted.
     * Because elements in a set are unique, the insertion operation checks whether each inserted element is equivalent to an element already in the container
	 * , and if so, the element is not inserted, returning an iterator to this existing element (if the function returns a value) using operator<.
     * For a similar container allowing for duplicate elements, see multiset.
     * Internally, set containers keep all their elements sorted following the criterion specified by its comparison object. 
	 * The elements are always inserted in its respective position following this ordering.
     * The parameters determine how many elements are inserted and to which values they are initialized:
	 * val: Value to be copied (or moved) to the inserted elements using copy constructor.
     *      Member type value_type is the type of the elements in the container, defined in set as an alias of its first template parameter (T).
	 * position: Hint for the position where the element can be inserted.
	 *           The function optimizes its insertion time if position points to the element that will precede the inserted element.
     * first, last: Iterators specifying a range of elements. Copies of the elements in the range [first,last) are inserted in the container.
	 * Return value:
	 * The single element versions (1) return a pair, with its member pair::first set to an iterator pointing to either the newly inserted element
	 * or to the equivalent element already in the set.
	 * The pair::second element in the pair is set to true if a new element was inserted or false if an equivalent element already existed.
     * The versions with a hint (2) return an iterator pointing to either the newly inserted element or to the element that already had its same value in the set.
     * Member type iterator is a bidirectional iterator type that points to elements.
     * pair is a class template declared in <utility> (see pair).
	 */
#if 1	
	for(int i=0; i<3; i++){
		std::cout << GREEN << "going to insert(MyMath(" << i << "))" << WHITE << std::endl;
		ret = set1.insert(MyMath(i));
		if (ret.second) std::cout << RED << "the newly inserted element:" << (*ret.first).getNumber() << WHITE << std::endl;
		else std::cout << CYAN << "the existing with same value element:" << (*ret.first).getNumber() << WHITE << std::endl;
	}
	for(int i=0; i<5; i++){
		std::cout << GREEN << "going to insert(MyMath(" << i << "))" << WHITE << std::endl;
		ret = set1.insert(MyMath(i));
		//if (ret.second) std::cout << RED << "the newly inserted element:" << (*ret.first).getNumber() << WHITE << std::endl;
		if (ret.second) std::cout << RED << "the newly inserted element:" << (ret.first)->getNumber() << WHITE << std::endl;
		//else std::cout << CYAN << "the existing with same value element:" << (*ret.first).getNumber() << WHITE << std::endl;
		else std::cout << CYAN << "the existing with same value element:" << (ret.first)->getNumber() << WHITE << std::endl;
	}
	for(it1=set1.begin(); it1!=set1.end(); ++it1){
		std::cout << YELLOW << "set1[" << distance(set1.begin(), it1) << "]:" << (*it1).getNumber() << WHITE << std::endl;
	}
#else
	std::set<int> set_int;
	std::pair<std::set<int>::iterator,bool> result;
	for(int i=0; i<5; i++){
		std::cout << GREEN << "going to insert " << i%2 << "))" << WHITE << std::endl;
		result = set_int.insert(i%2);
		if (result.second) std::cout << RED << "the newly inserted element:" << *(result.first) << WHITE << std::endl;
		else std::cout << CYAN << "the existing with same value element:" << *(result.first) << WHITE << std::endl;
	}
	for(std::set<int>::iterator it1=set_int.begin(); it1!=set_int.end(); ++it1){
		std::cout << YELLOW << "set_int[" << distance(set_int.begin(), it1) << "]:" << (*it1) << WHITE << std::endl;
	}
#endif	
	
	/**
	 * reverse_iterator std::set::rend()
     * Returns a reverse iterator pointing to the theoretical element right before-the-first element in the set container (which is considered its reverse end).
     * The range between set::rbegin and set::rend contains all the elements of the container (in reverse order).
	 */
	for(it2=set1.rbegin(); it2!=set1.rend(); ++it2){
		std::cout << YELLOW << "with reverse iterator set1[" << distance(it2, set1.rend())-1 << "]:" << (*it2).getNumber() << WHITE << std::endl;
	}
	
	/* set::key_comp() */
	std::cout << "comparison object comp(*set1.begin();, *(++set1.begin())):" << (comp(*set1.begin(), *(++set1.begin()))?"true":"false") << std::endl;
	
	/**
     * iterator std::set::lower_bound(const value_type& val) const
     * Returns an iterator pointing to the first element in the container which is NOT considered to go before val (i.e., either it is equivalent or goes after).
     * The function uses its internal comparison object (key_comp) to determine this
	 * , returning an iterator to the first element for which key_comp(element,val) would return false.
     * If the set class is instantiated with the default comparison type (less), the function returns an iterator to the first element that is not less than val.
     * A similar member function, upper_bound, has the same behavior as lower_bound, except in the case that the set contains an element equivalent to val: 
     * In this case lower_bound returns an iterator pointing to that element, whereas upper_bound returns an iterator pointing to the next element.
	 * val: Value to compare. 
	 *      Member type value_type is the type of the elements in the container, defined in set as an alias of its first template parameter (T).
	 * Return value:
     * An iterator to the the first element in the container which is not considered to go before val, or set::end if all elements are considered to go before val.
     * Member types iterator and const_iterator are bidirectional iterator types pointing to elements.
	 */
	for(set<MyMath>::iterator it=set1.begin(); it!=set1.end(); it++){
		std::cout << YELLOW << "before lower_bound() set1[" << std::distance(set1.begin(), it) << "]:" << (*it).getNumber() << WHITE << std::endl;
	}
	std::cout << YELLOW << "going to lower_bound()" << WHITE << std::endl;
	int bound = 2;
	set<MyMath>::iterator dest = set1.lower_bound(MyMath(3));
	cout << YELLOW << "(*dest).getNumber():" << (*dest).getNumber()  << WHITE << endl;
	for (set<MyMath>::iterator it=set1.begin();it!=dest;it++) {
		cout << YELLOW << "lower bound:" << bound <<" set1[" << distance(set1.begin(), it) << "]:" << (*it).getNumber()  << WHITE << endl;
	}
		
	
	/**
     * iterator std::set::upper_bound(const value_type& val) const
	 * Returns an iterator pointing to the first element in the container which is considered to go after val.
     * The function uses its internal comparison object (key_comp) to determine this
	 *, returning an iterator to the first element for which key_comp(val,element) would return true.
     * If the set class is instantiated with the default comparison type (less)
	 * , the function returns an iterator to the first element that is greater than val.
     * A similar member function, lower_bound, has the same behavior as upper_bound, except in the case that the set contains an element equivalent to val:
	 * In this case lower_bound returns an iterator pointing to that element, whereas upper_bound returns an iterator pointing to the next element.
	 * val: Value to compare. 
	 *      Member type value_type is the type of the elements in the container, defined in set as an alias of its first template parameter (T).
	 * Return value:
     * An iterator to the the first element in the container which is considered to go after val, or set::end if no elements are considered to go after val.
     */
	for(set<MyMath>::iterator it=set1.begin(); it!=set1.end(); it++){
		std::cout << YELLOW << "before upper_bound() set1[" << std::distance(set1.begin(), it) << "]:" << (*it).getNumber() << WHITE << std::endl;
	} 
	std::cout << YELLOW << "going to upper_bound()" << WHITE << std::endl;
	set<MyMath>::iterator begin = set1.upper_bound(bound);
	for (set<MyMath>::iterator it=begin;it!=set1.end();it++) {
		cout << YELLOW << "upper bound:" << bound <<" set1[" << distance(set1.begin(), it) << "]:" << (*it).getNumber()  << WHITE << endl;
	}
	
	/**
	 * void std::set::erase(iterator position)
	 * size_type std::set::erase(const value_type& val)
	 * void std::set::erase(iterator first, iterator last)
	 * Removes from the set container either a single element or a range of elements ([first,last)).
	 * This effectively reduces the container size by the number of elements removed, which are destroyed.
	 */
	for(set<MyMath>::iterator it=set1.begin(); it!=set1.end(); it++){
		std::cout << YELLOW << "before erase() set1[" << std::distance(set1.begin(), it) << "]:" << (*it).getNumber() << WHITE << std::endl;
	} 
	cout << "going to set1.erase(MyMath(222))" << endl;
	int num_removed = set1.erase(MyMath(2));
	for(set<MyMath>::iterator it=set1.begin(); it!=set1.end(); it++){
		std::cout << YELLOW << "after erase() set1[" << std::distance(set1.begin(), it) << "]:" << (*it).getNumber() << WHITE << std::endl;
	}
	
	/**
	 * iterator std::set::find(const value_type& val) const;
     * Get iterator to element
     * Searches the container for an element equivalent to val and returns an iterator to it if found, otherwise it returns an iterator to set::end.
     * Two elements of a set are considered equivalent if the container's comparison object returns false reflexively (i.e., no matter the order in which the elements are passed as arguments).
	 */
	int num_looking4 = 1;
	std::set<MyMath>::iterator it_looking4;
	if ((it_looking4=set1.find(MyMath(num_looking4)))!=set1.end()) 
		std::cout << GREEN << "after find() set has an element with value:" << num_looking4 << " at " << &(*it_looking4) << WHITE << std::endl;
	else std::cout << MAGENTA << "after find() set has no an element with value:" << num_looking4 << WHITE << std::endl;
	
	/**
	 * size_type std::set::count(const value_type& val) const
     * Count elements with a specific value
     * Searches the container for elements equivalent to val and returns the number of matches.
     * Because all elements in a set container are unique, the function can only return 1 (if the element is found) or zero (otherwise).
     * Two elements of a set are considered equivalent if the container's comparison object returns false reflexively aka. !(a<b)&&!(b<a)
	 * (i.e., no matter the order in which the elements are passed as arguments).
	 */
	if (set1.count(MyMath(num_looking4))) std::cout << GREEN << "after count() set has an element with value:" << num_looking4 << WHITE << std::endl;
	else std::cout << MAGENTA << "after count() set has no an element with value:" << num_looking4 << WHITE << std::endl;
	
	std::cout << GREEN << "\n****************** main return ******************" << WHITE << std::endl;
	return 0;
#endif

#if 0
	/**
	 * template < class Key,                                     // map::key_type
     *            class T,                                       // map::mapped_type
     *            class Compare = less<Key>,                     // map::key_compare
     *            class Alloc = allocator<pair<const Key,T>> >   // map::allocator_type
     * class map;
	 * Maps are associative containers that store elements formed by a combination of a key value and a mapped value, following a specific order.
     * In a map, the key values are generally used to sort and uniquely identify the elements, while the mapped values store the content associated to this key. 
	 * The types of key and mapped value may differ, and are grouped together in member type value_type, which is a pair type combining both:
	 * typedef pair<const Key, T> value_type;
     * Internally, the elements in a map are sorted by its key following a strict weak ordering criterion indicated by its internal comparison object (of type Compare).
     * map containers are generally slower than unordered_map containers to access individual elements by their key
	 * , but they allow the direct iteration on subsets based on their order.
     * The mapped values in a map can be accessed directly by their corresponding key using the bracket operator ((operator[]).
     * Maps are typically implemented as binary search trees.
	 */
	cout << GREEN << "****************** map laboratory ******************\n" << WHITE << endl;
	/**
	 * pair<iterator,bool> std::map::insert(const value_type& val) - (1)
	 * iterator std::map::insert(iterator position, const value_type& val) - (2)
	 * void std::map::insert(InputIterator first, InputIterator last) - (3)
	 *
	 * Extends the container by inserting new elements, effectively increasing the container size by the number of elements inserted.
     * Because element keys in a map are unique, the insertion operation checks whether each inserted element has a key equivalent to an element already in the container
	 * , and if so, the element is not inserted, returning an iterator to this existing element (if the function returns a value).
     * For a similar container allowing for duplicate elements, see multimap.
     * An alternative way to insert elements in a map is by using member function map::operator[].
     * Internally, map containers keep all their elements sorted by their key following the criterion specified by its comparison object.
	 * The elements are always inserted in its respective position following this ordering.
	 *
     * The parameters determine how many elements are inserted and to which values they are initialized:
     * val: Value to be copied to (or moved as) the inserted element.
     *      Member type value_type is the type of the elements in the container, defined in map as pair<const key_type,mapped_type> (see map member types).
     * position: Hint for the position where the element can be inserted.
	 *           The function optimizes its insertion time if position points to the element that will precede the inserted element.
     *           Notice that this is just a hint and does not force the new element to be inserted at that position within the map container 
	 *           (the elements in a map always follow a specific order depending on their key).
     * first, last: Iterators specifying a range of elements. Copies of the elements in the range [first,last) are inserted in the container.
	 *
	 * Return value:
     * The single element versions (1) return a pair, with its member pair::first set to an iterator pointing to 
	 * either the newly inserted element or to the element with an equivalent key in the map. 
	 * The pair::second element in the pair is set to true if a new element was inserted or false if an equivalent key already existed.
     * The versions with a hint (2) return an iterator pointing to either the newly inserted element or to the element that already had an equivalent key in the map.
	 */
	std::map<int, MyMath> map;
	std::pair<std::map<int,MyMath>::iterator,bool> ret;
	for (int i=0;i<3;i++) {
		cout << GREEN << "going to map.insert(std::pair<int, MyMath>(" << i<< ", MyMath(" << i << "))" << WHITE << endl; 
		std::pair<int, MyMath> val = *(new std::pair<int, MyMath>(i, MyMath(i)));
		ret = map.insert(val);
		if (ret.second) cout << CYAN << "newly inserted element:" << (ret.first->second).getNumber() << " at " << &(ret.first->second) << WHITE << endl;  
		else cout << MAGENTA << "existing equivalent key element:" << (ret.first->second).getNumber() << " at " << &(ret.first->second) << WHITE << endl; 
	}
	for (int i=0;i<3;i++) {
		cout << GREEN << "going to map.insert(std::pair<int, MyMath>(" << i<< ", MyMath(" << i << "))" << WHITE << endl; 
		std::pair<int, MyMath> val = *(new std::pair<int, MyMath>(i, MyMath(i)));
		ret = map.insert(val);
		if (ret.second) cout << CYAN << "newly inserted element:" << ret.first->second.getNumber() << " at " << &ret.first->second << WHITE << endl;  
		else cout << MAGENTA << "existing equivalent key element:" << ret.first->second.getNumber() << " at " << &ret.first->second << WHITE << endl; 
	}
	for (std::map<int, MyMath>::iterator it=map.begin();it!=map.end();it++) {
		cout << YELLOW << "after insert() map[" << distance(map.begin(),it) << "]: a pair at " << &(*it)
			<< " holding key:" << (it->first) << " at " << &it->first
			<< " => value:" << (it->second).getNumber() << " at " << &(it->second) << WHITE << endl; 
	}
	
	/**
	 * void std::map::erase(iterator position) - (1)
     * size_type std::map::erase(const key_type& k) - (2)
     * void std::map::erase(iterator first, iterator last) - (3)
	 */
	cout << "" << endl; 
	for (std::map<int,MyMath>::iterator it=map.begin();it!=map.end();it++) {
		cout << YELLOW << "before erase() map[" << distance(map.begin(),it) << "]: a pair at " << &*it
		<< " holding key:" << it->first << " at " << &it->first
		<< " => value:" <<  it->second.getNumber() << " at " << &it->second << WHITE << endl;
	}
	cout << GREEN << "going to erase()" << WHITE << endl;
	int num_erased = 0;
	num_erased = map.erase(1);
	for (std::map<int,MyMath>::iterator it=map.begin();it!=map.end();it++) {
		cout << YELLOW << "after erase() map[" << distance(map.begin(),it) << "]: a pair at " << &*it
		<< " holding key:" << it->first << " at " << &it->first
		<< " => value:" <<  it->second.getNumber() << " at " << &it->second << WHITE << endl;
	}
	
	cout << "" << endl; 
	/**
	 * iterator std::map::find(const key_type& k)
	 * const_iterator std::map::find(const key_type& k) const
	 * Searches the container for an element with a key equivalent to k and returns an iterator to it if found, otherwise it returns an iterator to map::end.
     * Two keys are considered equivalent if the container's comparison object returns false reflexively (no matter the order in which the elements are passed as arguments).
     * Another member function, map::count, can be used to just check whether a particular key exists.
     * k: Key to be searched for.
     *    Member type key_type is the type of the keys for the elements in the container, defined in map as an alias of its first template parameter (Key).
	 * Return value:
	 * An iterator to the element, if an element with specified key is found, or map::end otherwise.
     * If the map object is const-qualified, the function returns a const_iterator. Otherwise, it returns an iterator.
     * Member types iterator and const_iterator are bidirectional iterator types pointing to elements (of type value_type).
     * Notice that value_type in map containers is an alias of pair<const key_type, mapped_type>.
	 *
	 * If an element doesn’t exist with the given key in a map, the operator[] will insert a new default constructed element 
	 * which obviously can not work in a const map so C++ does not overload and define a const version of the operator[].
     * This is a nice example of the compiler’s type checker preventing a potential runtime error.
     * On the other hand, find() will never modify the map. If an item doesn’t exist, it returns an iterator to the map’s end().
	 *
	 * at() is a new method for std::map in C++11. Rather than insert a new default constructed element as operator[] does
	 * if an element with the given key does not exist, it throws a std::out_of_range exception. (This is similar to the behavior of at() for deque and vector.)
	 */
	cout << GREEN << "going to find()" << WHITE << endl; 
	std::map<int,MyMath>::iterator it_find =map.find(1);
	if (it_find!= map.end()) cout << YELLOW << "found element with key:" << it_find->first
							 << " and value:" << it_find->second.getNumber() << " at " << &it_find->second << WHITE << endl;
	else cout << YELLOW << "no such element with key:" << 1 << WHITE << endl;
	
	cout << "" << endl; 
	/**
	 * mapped_type& std::map::at(const key_type& k)
	 * const mapped_type& std::map::at(const key_type& k) const
     * Returns a reference to the mapped value of the element identified with key k.
     * If k does not match the key of any element in the container, the function throws an out_of_range exception.
	 */
	cout << GREEN << "going to at()" << WHITE << endl; 
	MyMath& m = map.at(2);
	cout << YELLOW << "element at key:" << 2 << " with mapped value:" << m.getNumber() << " at " << &m << WHITE << endl;
	
	/**
	 * mapped_type& std::map::operator[] (const key_type& k);
     * If k matches the key of an element in the container, the function returns a reference to its mapped value.
     * If k does not match the key of any element in the container, the function inserts a new element with that key and returns a reference to its mapped value. 
	 * Notice that this always increases the container size by one, even if no mapped value is assigned to the element 
	 * (the element is constructed using its default constructor).
     * A similar member function, map::at, has the same behavior when an element with the key exists, but throws an exception when it does not.
     * A call to this function is equivalent to: (*((this->insert(make_pair(k,mapped_type()))).first)).second 
     * k: Key value of the element whose mapped value is accessed.
     *    Member type key_type is the type of the keys for the elements stored in the container, defined in map as an alias of its first template parameter (Key).
     *    If an rvalue (second version), the key is moved instead of copied when a new element is inserted
     * Return value: A reference to the mapped value of the element with a key value equivalent to k.
     *               Member type mapped_type is the type of the mapped values in the container, defined in map as an alias of its second template parameter (T).
	 */
	 
	cout << "" << endl; 
	/**
	 * void std::map::clear()
	 * Removes all elements from the map container (which are destroyed), leaving the container with a size of 0.
	 */
	cout << GREEN << "going to clear()" << WHITE << endl; 
	map.clear();
	for (std::map<int,MyMath>::iterator it=map.begin();it!=map.end();it++) {
		cout << YELLOW << "after erase() map[" << distance(map.begin(),it) << "]: a pair at " << &*it
		<< " holding key:" << it->first << " at " << &it->first
		<< " => value:" <<  it->second.getNumber() << " at " << &it->second << WHITE << endl;
	}
	 
	std::cout << GREEN << "\n****************** main return ******************" << WHITE << std::endl;
	return 0;
#endif 

#if 0
	/**
	 * template <class T, class Container = deque<T> > class queue;
	 *
	 * Queues are a type of container adapter, specifically designed to operate in a FIFO context (first-in first-out)
	 * , where elements are inserted into one end of the container and extracted from the other.
     * Queues are implemented as containers adapters, which are classes that use an encapsulated object of a specific container class as its underlying container
	 * , providing a specific set of member functions to access its elements. Elements are pushed into the "back" of the specific container and popped from its "front".
     * The underlying container may be one of the standard container class template or some other specifically designed container class. 
	 * This underlying container shall support at least the following operations:
     * empty
	 * size
	 * front
	 * back
	 * push_back
	 * pop_front
     * 
	 * The standard container classes deque and list fulfill these requirements. 
	 * By default, if no container class is specified for a particular queue class instantiation, the standard container deque is used.
	 */
	cout << GREEN << "****************** queue laboratory ******************\n" << WHITE << endl;
	std::queue<MyMath> queue;
	
	/**
	 * void std::queue::push(const value_type& val)
     * Inserts a new element at the end of the queue, after its current last element. The content of this new element is initialized to val.
     * This member function effectively calls the member function push_back of the underlying container object.
	 */
	for (int i=0;i<3;i++) {
		std::cout << GREEN << "going to push(MyMath(" << 100*i << "))" << WHITE << std::endl;
		queue.push(MyMath(100*i));
	}
	/**
	 * bool std::queue::empty()
	 * Returns whether the queue is empty: i.e. whether its size is zero.
	 * Return Value:
     * true if the underlying container's size is 0, false otherwise.
	 */
	/**
	 * void std::queue::pop()
     * Removes the next element in the queue, effectively reducing its size by one.
     * The element removed is the "oldest" element in the queue whose value can be retrieved by calling member queue::front.
     * This calls the removed element's destructor.
     * This member function effectively calls the member function pop_front of the underlying container object.
	 */
	while (!queue.empty()) {
		std::cout << YELLOW << "(queue.front()).getNumber():" << (queue.front()).getNumber() << " at " <<  &(queue.front()) << WHITE << std::endl;
		std::cout << GREEN << "going to queue.pop()" << WHITE << std::endl;
		queue.pop();
	}
	
	std::cout << GREEN << "\n****************** main return ******************" << WHITE << std::endl;
	return 0;
#endif

#if 0
	/**
	 * template <class T, class Container = deque<T> > class stack;
     * Stacks are a type of container adapter, specifically designed to operate in a LIFO context (last-in first-out)
	 * , where elements are inserted and extracted only from one end of the container.
     * stacks are implemented as containers adapters, which are classes that use an encapsulated object of a specific container class as its underlying container
	 * , providing a specific set of member functions to access its elements. 
	 * Elements are pushed/popped from the "back" of the specific container, which is known as the top of the stack.
     * The underlying container may be any of the standard container class templates or some other specifically designed container class. The container shall support the following operations:
     * empty
	 * size
	 * back
	 * push_back
	 * pop_back
     * The standard container classes vector, deque and list fulfill these requirements. 
	 * By default, if no container class is specified for a particular stack class instantiation, the standard container deque is used.
	 *
	 * T: Type of the elements.
     *    Aliased as member type stack::value_type.
     * Container: Type of the internal underlying container object where the elements are stored.
     *            Its value_type shall be T.
     *            Aliased as member type stack::container_type.
	 */
	cout << GREEN << "****************** stack laboratory ******************\n" << WHITE << endl; 
	
	std::stack<MyMath> stack;
	for (int i=0;i<3;i++) {
		cout << GREEN << "going to push(MyMath(" << i << "))" << WHITE << endl;
		stack.push(MyMath(i));
	}
	
	/**
	 * value_type& std::stack::top();
     * const value_type& std::stack::top() const;
     * Returns a reference to the top element in the stack. 
     * Since stacks are last-in first-out containers, the top element is the last element inserted into the stack.
     * This member function effectively calls member back of the underlying container object.
	 */
	/**
     * void std::stack::pop()
     * Removes the element on top of the stack, effectively reducing its size by one.
     * The element removed is the latest element inserted into the stack, whose value can be retrieved by calling member stack::top.
     * This calls the removed element's destructor.
     * This member function effectively calls the member function pop_back of the underlying container object.
     */	 
	while (!stack.empty()) {
		cout << GREEN << "going to top()" << WHITE << endl;
		MyMath& m = stack.top();
		cout << YELLOW << "an element of stack with value:" << m.getNumber() << " at " << &m << WHITE << endl;
		cout << GREEN << "going to pop()" << WHITE << endl;
		stack.pop();
	}
 
	std::cout << GREEN << "\n****************** main return ******************" << WHITE << std::endl;
	return 0;
#endif	
	
#if 0
	std::cout << GREEN << "****************** my linked list queue laboratory ******************\n" << WHITE << std::endl;
	MyLinkedListQueue<MyMath> list =*(new MyLinkedListQueue<MyMath>());
	for(int i=0; i<3; i++){
		std::cout << GREEN << "going to list.offer(MyMath(" << i+100 << "))" << WHITE << std::endl;
		list.offer(MyMath(i+100));
	}

	std::cout << GREEN << "\ngoing to list.peek()" << WHITE << std::endl;
	MyMath& m_peek = list.peek();
	std::cout << YELLOW << "after peek() returned an element in container:" << m_peek.getNumber() << " at " << &m_peek << WHITE << std::endl;
	
	std::cout << GREEN << "\ngoing to list.poll()" << WHITE << std::endl;
	//MyMath m_poll = list.poll(); //using copy constructor 
	MyMath m_poll(std::move(list.poll()));  //using move constructor
	std::cout << YELLOW << "after poll() got a copy of the element in container:" << m_poll.getNumber() << " at " << &m_poll << WHITE << std::endl;
	
	std::cout << GREEN << "\ngoing to list.poll()" << WHITE << std::endl;
	MyMath m_poll2 = list.poll();
	std::cout << YELLOW << "after poll() got a copy of the element in container:" << m_poll2.getNumber() << " at " << &m_poll2 << WHITE << std::endl;
	
	std::cout << GREEN << "\ngoing to list.poll()" << WHITE << std::endl;
	MyMath m_poll3 = list.poll();
	std::cout << YELLOW << "after poll() got a copy of the element in container:" << m_poll3.getNumber() << " at " << &m_poll3 << WHITE << std::endl;
	
	std::cout << GREEN << "\n****************** main return ******************" << WHITE << std::endl;
	return 0;
#endif	

#if 0
	std::cout << GREEN << "****************** array queue laboratory ******************\n" << WHITE << std::endl;
	MyArrayQueue<MyMath> *queue = new MyArrayQueue<MyMath>(2);
	for(int i=0; i<2; i++){
		std::cout << GREEN << "going to queue->offer(MyMath(i+100))" << WHITE << std::endl;
		queue->offer(MyMath(i+100));
	}
	std::cout << GREEN << "\ngoing to queue->peek()" << WHITE << std::endl;
	MyMath& mm1 = queue->peek();
	std::cout << YELLOW << "after peek() returned an element in container:" << mm1.getNumber() << " at " << &mm1 << WHITE << std::endl;
	
	std::cout << GREEN << "\ngoing to queue->poll()" << WHITE << std::endl;
	MyMath mm2 = queue->poll();
	std::cout << YELLOW << "after poll() got a copy of the element in container:" << mm2.getNumber() << " at " << &mm2 << WHITE << std::endl;
	
	std::cout << GREEN << "\ngoing to queue->poll()" << WHITE << std::endl;
	MyMath mm3 = queue->poll();
	std::cout << YELLOW << "after poll() got a copy of the element in container:" << mm3.getNumber() << " at " << &mm3 << WHITE << std::endl;
	
	//delete[] queue;
	
	std::cout << GREEN << "\n****************** main return ******************" << WHITE << std::endl;
	return 0;
#endif

#if 0
	std::cout << GREEN << "****************** bubble sort ******************\n" << WHITE << std::endl;
	std::vector<int> vector = (amo::Sort::getInstance()).getRandomShuffledVector(100);
	clock_t clk_start, clk_end;
	double duration;
	
	std::cout << YELLOW << "got a vector at " << &vector << " and size:" << vector.size() << WHITE << std::endl;
	for (std::vector<int>::iterator it=vector.begin();it!=vector.end();it++) 
		std::cout << YELLOW << "before bubble sort vector[" << distance(vector.begin(), it) << "]:" << *it << WHITE << std::endl;
	clk_start = clock();
	std::cout << GREEN << "going to amo::Sort::getInstance().bubbleSort(vector)" << WHITE << std::endl;
	amo::Sort::getInstance().bubbleSort(vector);
	clk_end = clock();
	duration = (double) 1000*(clk_end-clk_start)/CLOCKS_PER_SEC;
	for (std::vector<int>::iterator it=vector.begin();it!=vector.end();it++) 
		std::cout << YELLOW << "after " << duration << "ms sorted vector[" << distance(vector.begin(), it) << "]:" << *it << WHITE << std::endl;
	
	std::cout << GREEN << "\n****************** main return ******************" << WHITE << std::endl;
	return 0;

#endif

#if 0
	std::cout << GREEN << "****************** merge sort ******************\n" << WHITE << std::endl;
	std::vector<int> vector = (amo::Sort::getInstance()).getRandomShuffledVector(99);
	clock_t clk_start, clk_end;
	double duration;
	
	std::cout << YELLOW << "got a vector at " << &vector << " and size:" << vector.size() << WHITE << std::endl;
	for (std::vector<int>::iterator it=vector.begin();it!=vector.end();it++) 
		std::cout << YELLOW << "before merge sort vector[" << distance(vector.begin(), it) << "]:" << *it << WHITE << std::endl;
	
	clk_start = clock();
	std::cout << GREEN << "going to amo::Sort::getInstance().mergeSort(vector)" << WHITE << std::endl;
	std::vector<int> sort = amo::Sort::getInstance().mergeSort(vector);
	
	clk_end = clock();
	duration = (double) 1000*(clk_end-clk_start)/CLOCKS_PER_SEC;
	for (std::vector<int>::iterator it=sort.begin();it!=sort.end();it++) 
		std::cout << YELLOW << "after " << duration << "ms sorted sort[" << distance(sort.begin(), it) << "]:" << *it << WHITE << std::endl;
	
	std::cout << GREEN << "\n****************** main return ******************" << WHITE << std::endl;
	return 0;

#elif 0
	std::cout << GREEN << "****************** merge sort ******************\n" << WHITE << std::endl;
	std::vector<int> vector = (amo::Sort::getInstance()).getRandomShuffledVector(8);
	clock_t clk_start, clk_end;
	double duration;
	
	std::cout << YELLOW << "got a vector at " << &vector << " and size:" << vector.size() << WHITE << std::endl;
	for (std::vector<int>::iterator it=vector.begin();it!=vector.end();it++) 
		std::cout << YELLOW << "before merge sort vector[" << distance(vector.begin(), it) << "]:" << *it << WHITE << std::endl;
	
	clk_start = clock();
	std::cout << GREEN << "going to amo::Sort::getInstance().mergeSort(vector)" << WHITE << std::endl;
	amo::Sort::getInstance().mergeSort(vector, 0, vector.size()-1);
	
	clk_end = clock();
	duration = (double) 1000*(clk_end-clk_start)/CLOCKS_PER_SEC;
	for (std::vector<int>::iterator it=vector.begin();it!=vector.end();it++) 
		std::cout << YELLOW << "after " << duration << "ms sorted vector[" << distance(vector.begin(), it) << "]:" << *it << WHITE << std::endl;
	
	std::cout << GREEN << "\n****************** main return ******************" << WHITE << std::endl;
	return 0;	

#endif

#if 0
	std::cout << GREEN << "****************** selection sort ******************\n" << WHITE << std::endl;
	std::vector<int> vector = (amo::Sort::getInstance()).getRandomShuffledVector(9);
	clock_t clk_start, clk_end;
	double duration;
	
	std::cout << YELLOW << "got a vector at " << &vector << " and size:" << vector.size() << WHITE << std::endl;
	for (std::vector<int>::iterator it=vector.begin();it!=vector.end();it++) 
		std::cout << YELLOW << "before selection sort vector[" << distance(vector.begin(), it) << "]:" << *it << WHITE << std::endl;
	
	clk_start = clock();
	std::cout << GREEN << "going to amo::Sort::getInstance().selectionSort(vector)" << WHITE << std::endl;
	amo::Sort::getInstance().selectionSort(vector);
	
	clk_end = clock();
	duration = (double) 1000*(clk_end-clk_start)/CLOCKS_PER_SEC;
	for (std::vector<int>::iterator it=vector.begin();it!=vector.end();it++) 
		std::cout << YELLOW << "after " << duration << "ms sorted vector[" << distance(vector.begin(), it) << "]:" << *it << WHITE << std::endl;
	
	std::cout << GREEN << "\n****************** main return ******************" << WHITE << std::endl;
	return 0;
#endif

#if 0
	std::cout << GREEN << "****************** insertion sort ******************\n" << WHITE << std::endl;
	std::vector<int> vector = (amo::Sort::getInstance()).getRandomShuffledVector(8);
	clock_t clk_start, clk_end;
	double duration;
	
	std::cout << YELLOW << "got a vector at " << &vector << " and size:" << vector.size() << WHITE << std::endl;
	for (std::vector<int>::iterator it=vector.begin();it!=vector.end();it++) 
		std::cout << YELLOW << "before insertion sort vector[" << distance(vector.begin(), it) << "]:" << *it << WHITE << std::endl;
	
	clk_start = clock();
	std::cout << GREEN << "going to amo::Sort::getInstance().insertionSort(vector)" << WHITE << std::endl;
	amo::Sort::getInstance().insertionSort(vector);
	
	clk_end = clock();
	duration = (double) 1000*(clk_end-clk_start)/CLOCKS_PER_SEC;
	for (std::vector<int>::iterator it=vector.begin();it!=vector.end();it++) 
		std::cout << YELLOW << "after " << duration << "ms sorted vector[" << distance(vector.begin(), it) << "]:" << *it << WHITE << std::endl;
	
	std::cout << GREEN << "\n****************** main return ******************" << WHITE << std::endl;
	return 0;
#endif

#if 0
	std::cout << GREEN << "****************** quick sort ******************\n" << WHITE << std::endl;
	std::vector<int> vector = (amo::Sort::getInstance()).getRandomShuffledVector(8);
	clock_t clk_start, clk_end;
	double duration;
	
	std::cout << YELLOW << "got a vector at " << &vector << " and size:" << vector.size() << WHITE << std::endl;
	for (std::vector<int>::iterator it=vector.begin();it!=vector.end();it++) 
		std::cout << YELLOW << "before quick sort vector[" << distance(vector.begin(), it) << "]:" << *it << WHITE << std::endl;
	
	clk_start = clock();
	std::cout << GREEN << "going to amo::Sort::getInstance().quickSort(vector)" << WHITE << std::endl;
	amo::Sort::getInstance().quickSort(vector);
	
	clk_end = clock();
	duration = (double) 1000*(clk_end-clk_start)/CLOCKS_PER_SEC;
	for (std::vector<int>::iterator it=vector.begin();it!=vector.end();it++) 
		std::cout << YELLOW << "after " << duration << "ms sorted vector[" << distance(vector.begin(), it) << "]:" << *it << WHITE << std::endl;
	
	std::cout << GREEN << "\n****************** main return ******************" << WHITE << std::endl;
	return 0;
#elif 0
	std::cout << GREEN << "****************** quick sort ******************\n" << WHITE << std::endl;
	std::vector<int> vector = (amo::Sort::getInstance()).getRandomShuffledVector(8);
	clock_t clk_start, clk_end;
	double duration;
	
	std::cout << YELLOW << "got a vector at " << &vector << " and size:" << vector.size() << WHITE << std::endl;
	for (std::vector<int>::iterator it=vector.begin();it!=vector.end();it++) 
		std::cout << YELLOW << "before quick sort vector[" << distance(vector.begin(), it) << "]:" << *it << WHITE << std::endl;
	
	clk_start = clock();
	std::cout << GREEN << "going to amo::Sort::getInstance().quickSort(vector)" << WHITE << std::endl;
	amo::Sort::getInstance().quickSort(vector, 0, vector.size()-1);
	
	clk_end = clock();
	duration = (double) 1000*(clk_end-clk_start)/CLOCKS_PER_SEC;
	for (std::vector<int>::iterator it=vector.begin();it!=vector.end();it++) 
		std::cout << YELLOW << "after " << duration << "ms sorted vector[" << distance(vector.begin(), it) << "]:" << *it << WHITE << std::endl;
	
	std::cout << GREEN << "\n****************** main return ******************" << WHITE << std::endl;
	return 0;	
#endif
	
#if 0
	std::cout << GREEN << "****************** binary count ******************\n" << WHITE << std::endl;
	int count = (amo::Number::getInstance()).getBinCount(441);
	std::cout << YELLOW << "binary 1 count:" << count << WHITE << std::endl;
	
	std::cout << GREEN << "\n****************** main return ******************" << WHITE << std::endl;
	return 0;

#endif 	 

#if 0
	std::cout << GREEN << "****************** power count ******************\n" << WHITE << std::endl;
	long long pow = (amo::Number::getInstance()).power2(8);
	std::cout << YELLOW << "pow:" << pow << WHITE << std::endl;
	
	std::cout << GREEN << "\n****************** main return ******************" << WHITE << std::endl;
	return 0;

#endif 		

#if 0
	std::cout << GREEN << "****************** hanoi ******************\n" << WHITE << std::endl;
	
	std::stack<int> stackA, stackB, stackC;
	/*
	for (int i=0;i<3;i++) {
		cout << GREEN << "stackA going to push(" << i << ")" << WHITE << endl;
		stackA.push(i);
	}
	*/
	for (int i=5;i>0;i--) {
		cout << GREEN << "stackA going to push(" << i << ")" << WHITE << endl;
		stackA.push(i);
	}
	
	(amo::Move::getInstance()).hanoi(5, stackA, stackB, stackC);

	while (!stackA.empty()) {
		cout << GREEN << "stackA going to top()" << WHITE << endl;
		int val = stackA.top();
		cout << YELLOW << "an element of stackA with value:" << val << " at " << &val << WHITE << endl;
		cout << GREEN << "going to pop()" << WHITE << endl;
		stackA.pop();
	}
	
	while (!stackC.empty()) {
		cout << GREEN << "stackC going to top()" << WHITE << endl;
		int val = stackC.top();
		cout << YELLOW << "an element of stackC with value:" << val << " at " << &val << WHITE << endl;
		cout << GREEN << "going to pop()" << WHITE << endl;
		stackC.pop();
	}
	
	std::cout << GREEN << "\n****************** main return ******************" << WHITE << std::endl;
	return 0;

#endif 	

#if 0
	std::cout << GREEN << "****************** akermann ******************\n" << WHITE << std::endl;
	cout << GREEN << "going to (amo::Number::getInstance()).akermann()" << WHITE << endl;
	int aker = (amo::Number::getInstance()).akermann(3, 1);
	cout << YELLOW << "akermann:" << aker << WHITE << endl;
	
	std::cout << GREEN << "\n****************** main return ******************" << WHITE << std::endl;
	return 0;

#endif 	

#if 0
	std::cout << GREEN << "****************** hailstone ******************\n" << WHITE << std::endl;
	cout << GREEN << "going to (amo::Number::getInstance()).hailstone()" << WHITE << endl;
	int run = (amo::Number::getInstance()).hailstone(77);
	cout << YELLOW << "run:" << run << WHITE << endl;
	
	std::cout << GREEN << "\n****************** main return ******************" << WHITE << std::endl;
	return 0;

#endif 

#if 0
	std::cout << GREEN << "****************** sum ******************\n" << WHITE << std::endl;
	std::vector<int> vector;
	for(int i=0; i<5; i++){
		//std::cout << GREEN << "going to vector.push_back(" << i << ")" << WHITE << std::endl;
		vector.push_back(i+1);
	}
	for(std::vector<int>::iterator it=vector.begin(); it!=vector.end(); it++){
		std::cout << YELLOW << "before sum() vector[" << std::distance(vector.begin(), it) << "]:" << *it << WHITE << std::endl;
	}
	
	cout << GREEN << "going to (amo::Number::getInstance()).sum()" << WHITE << endl;
	int sum = (amo::Number::getInstance()).sum(vector);
	cout << YELLOW << "sum:" << sum << WHITE << endl;
	
	std::cout << GREEN << "\n****************** main return ******************" << WHITE << std::endl;
	return 0;

#endif 

#if 0
	std::cout << GREEN << "****************** reverse ******************\n" << WHITE << std::endl;
	std::list<int> list;
	for(int i=0; i<8; i++){
		//std::cout << GREEN << "going to list.push_back(" << i << ")" << WHITE << std::endl;
		list.push_back(i+1);
	}
	for(std::list<int>::iterator it=list.begin(); it!=list.end(); it++){
		std::cout << YELLOW << "before reverse list[" << std::distance(list.begin(), it) << "]:" << *it << " at " << &*it << WHITE << std::endl;
	}
	std::cout << YELLOW << "before reverse past-the-end list.end(): at " << &*list.end() << WHITE << std::endl;
	
	cout << GREEN << "going to (amo::Sort::getInstance()).reverse()" << WHITE << endl;
	int exchange = (amo::Sort::getInstance()).reverse(list);
	cout << YELLOW << "exchange:" << exchange << WHITE << endl;
	
	for(std::list<int>::iterator it=list.begin(); it!=list.end(); it++){
		std::cout << YELLOW << "after reverse list[" << std::distance(list.begin(), it) << "]:" << *it << " at " << &*it << WHITE << std::endl;
	}
	
	std::cout << GREEN << "\n****************** main return ******************" << WHITE << std::endl;
	return 0;

#endif 

#if 0
	std::cout << GREEN << "****************** fibonacci ******************\n" << WHITE << std::endl;
	
	cout << GREEN << "going to (amo::Number::getInstance()).fibonacci(5)" << WHITE << endl;
	int n = 11;
	int dummy = 0;
	//int fib = (amo::Number::getInstance()).fibonacci(n);
	int fib = (amo::Number::getInstance()).fibonacci(n, dummy);
	cout << YELLOW << "n:" << n <<" and fibonacci:" << fib << WHITE << endl;
	
	std::cout << GREEN << "\n****************** main return ******************" << WHITE << std::endl;
	return 0;

#endif 

#if 0
	std::cout << GREEN << "****************** test ******************\n" << WHITE << std::endl;
	
	std::vector<int> vector_int;
	std::vector<int> vector_copy;
	for(int i=0; i<10; i++){
		vector_int.push_back(i);
	}
	vector_copy.assign(std::next(vector_int.begin(),1), std::next(vector_int.begin(),1));
	for(std::vector<int>::iterator it=vector_copy.begin(); it!=vector_copy.end(); it++){
		std::cout << YELLOW << "after assign() vector_copy[" << std::distance(vector_copy.begin(), it) << "]:" << *it << WHITE << std::endl;
	}
	
	int n;
	n = 5;
	while (n-->0) std::cout << "while (n-->0) n:" << n << WHITE << std::endl;
	n = 5;
	while (--n>0) std::cout << "while (--n>0) n:" << n << WHITE << std::endl;
	n = 5;
	while (0<n--) std::cout << "while (0<n--) n:" << n << WHITE << std::endl;
	n = 5;
	while (0<--n) std::cout << "while (0<--n) n:" << n << WHITE << std::endl;
	n = 0;
	while (5>n++) std::cout << "while (5>n++) n:" << n << WHITE << std::endl;
	n = 5;
	while (n--) std::cout << "while (n--) n:" << n << WHITE << std::endl;
	n = 0;
	while (++n<5) std::cout << "while (++n<5) n:" << n << WHITE << std::endl;
	n = 0;
	while (n++<5) std::cout << "while (n++<5) n:" << n << WHITE << std::endl;

	std::cout << GREEN << "\n****************** main return ******************" << WHITE << std::endl;
	return 0;
#endif 

#if 0
	std::cout << GREEN << "****************** list ******************\n" << WHITE << std::endl;
	
	cout << GREEN << "going to create a list" << WHITE << endl;
	amo::List<int> list;
	
	cout << GREEN << "going to list.insertFirst(10)" << WHITE << endl;
	list.insertFirst(10);
	cout << GREEN << "going to list.insertLast(20)" << WHITE << endl;
	list.insertLast(20);
	cout << GREEN << "going to list.insertAfter(30, *list.last())" << WHITE << endl;
	list.insertAfter(30, *list.last());
	cout << GREEN << "going to list.insertBefore(40, *list.first())" << WHITE << endl;
	list.insertBefore(40, *list.first());
	for (int i=0;i<list.size();i++) 
		cout << YELLOW << "list[" << i <<"]:" << list[i] << WHITE << endl;
	cout << YELLOW << "first:" << list.first()->data << WHITE << endl;
	cout << YELLOW << "last:" << list.last()->data << WHITE << endl;
	
	cout << GREEN << "going to list.indexOf()" << WHITE << endl;
	int index = list.indexOf(list.first()->succ);
	cout << YELLOW << "index of list.first()->succ:" << index << WHITE << endl;
	
	cout << GREEN << "going to list.find()" << WHITE << endl;
	//Node<int>* target = list.find(5,list.size(),*list.last()); //n should be the index of last
	Node<int>* target = list.find(5, list.indexOf(list.last())+1, *list.last()); //n should be the index of last
	if (target != NULL) cout << YELLOW << "found target.data:" << target->data << WHITE << endl;
	else cout << YELLOW << "found nothing" << WHITE << endl;
		
	cout << GREEN << "going to create a list2" << WHITE << endl;	
	amo::List<int> list2;
	cout << GREEN << "going to list2.assign()" << WHITE << endl;
	list2.assign(list.first(), list.size()+100);
	for (int i=0;i<list2.size();i++) 
		cout << YELLOW << "list2[" << i <<"]:" << list2[i] << WHITE << endl;
	
	cout << GREEN << "going to create a list3 by copy constructor" << WHITE << endl;	
	amo::List<int> list3(list2);
	for (int i=0;i<list3.size();i++) 
		cout << YELLOW << "list3[" << i <<"]:" << list3[i] << WHITE << endl;
	
	cout << GREEN << "going to create a list4 by copy constructor" << WHITE << endl;	
	amo::List<int> list4(list2, 1, 2);
	for (int i=0;i<list4.size();i++) 
		cout << YELLOW << "list4[" << i <<"]:" << list4[i] << WHITE << endl;
	
	cout << GREEN << "going to next() on a node" << WHITE << endl;	
	//Node<int>* node = (list3.first())->next(3);
	Node<int>* node = (list3.last())->next(-3);
	if (node != NULL) cout << YELLOW << "node:" << node->data << " at " << node << WHITE << endl;
	else cout << YELLOW << "node is NULL" << WHITE << endl;
	
	cout << GREEN << "going to remove a element from list3" << WHITE << endl;	
	Node<int>* removed = list3.remove(1);
	for (int i=0;i<list3.size();i++) 
		cout << YELLOW << "list3[" << i <<"]:" << list3[i] << WHITE << endl;
	delete removed;
	
	cout << GREEN << "going to deduplicate" << WHITE << endl;	
	for (int i=0;i<3;i++) 
		list3.insertLast(66);
	list3.insertLast(77);
	for (int i=0;i<3;i++) 
		list3.insertLast(88);
	list3.deduplicate();
	for (int i=0;i<list3.size();i++) 
		cout << YELLOW << "list3[" << i <<"]:" << list3[i] << WHITE << endl;
	
	//cout << GREEN << "going to unique" << WHITE << endl;	
	for (int i=0;i<3;i++) 
		list3.insertLast(333);
	list3.insertLast(222);
	for (int i=0;i<3;i++) 
		list3.insertLast(111);
	//list3.unique();
	for (int i=0;i<list3.size();i++) 
		cout << YELLOW << "list3[" << i <<"]:" << list3[i] << WHITE << endl;
	
	cout << GREEN << "going to search" << WHITE << endl;
	Node<int>* s = list3.search(-100, list3.indexOf(list3.last()), *list3.last());
	if (!list3.valid(s)) cout << YELLOW << "searched nothing" << WHITE << endl;
	else cout << YELLOW << "searched:" << s->data << " at " << s << WHITE << endl;
	
	//cout << GREEN << "going to insertion sort" << WHITE << endl;
	//list3.insertionSort();
	
	//cout << GREEN << "going to selection sort" << WHITE << endl;
	//list3.selectionSort();
	
	cout << GREEN << "going to merge sort" << WHITE << endl;
	list3.mergeSort();
	
	std::cout << GREEN << "\n****************** main return ******************" << WHITE << std::endl;
	return 0;
#endif 

#if 0
	std::cout << GREEN << "****************** stack ******************\n" << WHITE << std::endl;
	
#if 0	
	amo::Stack<int> stack;
	cout << GREEN << "going to push" << WHITE << endl;
	for (int i=0;i<5;i++) stack.push(i);
	stack.traverse();
	cout << GREEN << "going to pop" << WHITE << endl;
	for (int i=0;i<4;i++) stack.pop();
	stack.traverse();
	
	cout << GREEN << "going to convert" << WHITE << endl;
	amo::Stack<char> s;
	(amo::Char::getInstance()).convert(s, 4321, 0);
	s.traverse();
	

	cout << GREEN << "going to check parenthesis" << WHITE << endl;
	char express[] = "_(ab(cd)e(rrrf()))_";
	//int lo=0, hi;
	//hi = sizeof(express)/sizeof(express[0]);
	//amo::Char::getInstance().paren(express, lo, hi);
	int len = sizeof(express)/sizeof(express[0]);
	amo::Char::getInstance().paren(express, len);
	
	amo::Stack<float> resolves;
	resolves.push(999);
	amo::Char::getInstance().resolve("321.123", resolves);
	resolves.traverse();	

	//cout << GREEN << "isCal:" << amo::Number::getInstance().isCal('(') << WHITE << endl;
	//cout << GREEN << "isPrior:" << amo::Number::getInstance().isPrior('*', '+') << WHITE << endl;
	//cout << GREEN << "power:" << amo::Number::getInstance().power(5, 3) << WHITE << std::endl;
	//cout << GREEN << "factory:" << amo::Number::getInstance().factory(5) << WHITE << std::endl;
	
	char exp[] = "( 6 *((2+3)+4))";
	//char exp[] = "1+2";
	amo::Char::getInstance().append(exp, '/');
	amo::Char::getInstance().append(exp, 5);
	amo::Char::getInstance().append(exp, '+');
	amo::Char::getInstance().append(exp, '!');
	amo::Char::getInstance().append(exp, 3);
	amo::Char::getInstance().append(exp, '+');
	amo::Char::getInstance().append(exp, 3);
	amo::Char::getInstance().append(exp, '^');
	amo::Char::getInstance().append(exp, 2);
	
	
	std::vector<char> infix;
	for (int i=0;i<strlen(exp);i++) infix.push_back(exp[i]);
	std::cout << GREEN << "Original infix:";
		for (std::vector<char>::iterator it=infix.begin(); it!=infix.end(); it++) {
		std::cout << *it;
	}
	std::cout << WHITE << std::endl;
	
	std::vector<char> postfix = amo::Number::getInstance().rePolish(infix);
	char rpn[32] = "";
	char *p = rpn;
	for (std::vector<char>::iterator it=postfix.begin(); it!=postfix.end(); it++) {
		std::cout << YELLOW << "Reverse polish notation char:" << *it << WHITE << std::endl;
		*(p++) = *it;
	}
	std::cout << GREEN << "strlen of rpn:" << strlen(rpn) << " and size of rpn:" << sizeof(rpn)/sizeof(rpn[0]) << WHITE << std::endl;
	rpn[strlen(rpn)] = '\0';
	std::cout << GREEN << "Reverse polish notation:" << rpn << WHITE << std::endl;
	std::cout << GREEN << "Evaluation:" << amo::Number::getInstance().evaluate(rpn) << WHITE << std::endl;

	std::cout << GREEN << "****************** Eight queens puzzle ******************\n" << WHITE << std::endl;

	amo::Queen::getInstance().place(0,8);
	std::cout << GREEN << "Answer of Eight queens puzzle:" << amo::Queen::getInstance().answer() << WHITE << std::endl;
#endif
	
	std::cout << GREEN << "****************** Maze ******************\n" << WHITE << std::endl;
	amo::Maze::getInstance(4, 4).labyrinth(1, 1, 1, 1);
	
	
	std::cout << GREEN << "\n****************** main return ******************" << WHITE << std::endl;
	return 0;
#endif

#if 0
	std::cout << GREEN << "****************** tree node ******************\n" << WHITE << std::endl;
 
#if 1
	amo::BinNode<int> root(0);
	amo::BinNode<int>* lchild1 = root.insertLeftChild(1);
	amo::BinNode<int>* rchild2 = root.insertRightChild(2);
	amo::BinNode<int>* lchild3 = lchild1->insertLeftChild(3);
	amo::BinNode<int>* rchild4 = lchild1->insertRightChild(4);
	amo::BinNode<int>* lchild5 = rchild2->insertLeftChild(5);
	amo::BinNode<int>* rchild6 = rchild2->insertRightChild(6);
	amo::BinNode<int>* lchild7 = lchild3->insertLeftChild(7);
	amo::BinNode<int>* rchild8 = lchild3->insertRightChild(8);
	amo::BinNode<int>* lchild9 = rchild6->insertLeftChild(9);
	amo::BinNode<int>* rchild10 = rchild6->insertRightChild(10);
	amo::BinNode<int>* lchild11 = rchild8->insertLeftChild(11);
	amo::BinNode<int>* rchild12 = rchild8->insertRightChild(12);
	
#if 1
	std::cout << GREEN << "going to root.traversePre()" << WHITE << std::endl;
	root.traversePre();
	std::cout << GREEN << "going to root.traversePreLoop()" << WHITE << std::endl;
	root.traversePreLoop();
	std::cout << GREEN << "going to root.traversePreLoop2()" << WHITE << std::endl;
	root.traversePreLoop2();
#elif 0
	std::cout << GREEN << "going to root.traverseIn()" << WHITE << std::endl;
	root.traverseIn();
	std::cout << GREEN << "going to root.traverseInLoop()" << WHITE << std::endl;
	root.traverseInLoop();
	std::cout << GREEN << "going to root.traverseInLoop2()" << WHITE << std::endl;
	root.traverseInLoop2();
	std::cout << GREEN << "going to root.traverseInLoop3()" << WHITE << std::endl;
	root.traverseInLoop3();
#elif 0
	std::cout << GREEN << "going to root.traversePost()" << WHITE << std::endl;
	root.traversePost();
	root.traversePostLoop();
#elif 0
	std::cout << GREEN << "going to root.traverseLevel()" << WHITE << std::endl;
	root.traverseLevel();
#else
#endif
	std::cout << GREEN << "\n****************** main return ******************" << WHITE << std::endl;
	return 0;
#endif	

#if 0
	std::cout << GREEN << "****************** tree ******************\n" << WHITE << std::endl;
	amo::BinTree<int> tree;
	tree.insertRoot(0);
	tree.insertLeftChild(tree.root(), 1);
	tree.insertRightChild(tree.root(), 2);
	std::cout << GREEN << "going to traverse tree" << WHITE << std::endl;
	tree.traverse();		
#endif
#endif
#if 0
	std::cout << GREEN << "****************** Huffman tree ******************\n" << WHITE << std::endl;
	amo::HuffmanTree<amo::Model> tree;
	tree.encode("source", "encode");
	tree.decode("encode", "decode");
 
	std::cout << GREEN << "\n****************** main return ******************" << WHITE << std::endl;
	return 0;
#endif  

#if 0
	std::cout << GREEN << "****************** Graph tree ******************\n" << WHITE << std::endl;

#if 0
	//amo::Graph<int, int> graph;
	amo::AdjaMatrix<char, string> matrix;
	matrix.insert('S'); //0
	matrix.insert('A'); //1
	matrix.insert('B'); //2
	matrix.insert('C'); //3
	matrix.insert('D'); //4
	matrix.insert('E'); //5
	matrix.insert('F'); //6
	matrix.insert('G'); //7
	matrix.insert("SA", 0, 1, 0);
	matrix.insert("SC", 0, 3, 0);
	matrix.insert("SD", 0, 4, 0);
	matrix.insert("AC", 1, 3, 0);
	matrix.insert("AE", 1, 5, 0);
	matrix.insert("CB", 3, 2, 0);
	matrix.insert("DB", 4, 2, 0);
	matrix.insert("EF", 5, 6, 0);
	matrix.insert("EG", 5, 7, 0);
	matrix.insert("GB", 7, 2, 0);
	matrix.insert("GF", 7, 6, 0);
	
	//std::cout << GREEN << "going to matrix.remove(0)" << WHITE << endl;
	//matrix.remove(0);
	//std::cout << GREEN << "going to matrix.remove(1, 0)" << WHITE << endl;
	//matrix.remove(1, 0);
	
	std::cout << GREEN << "--- AdjaMatrix information start ---" << WHITE << endl;
	std::cout << matrix;
	std::cout << GREEN << "--- AdjaMatrix information end ---" << WHITE << endl;
	
	std::cout << GREEN << "going to BFS" << WHITE << endl;
	matrix.BFS(0);
#endif	

#if 0
	amo::AdjaMatrix<char, string> matrix;
	matrix.insert('A'); //0
	matrix.insert('B'); //1
	matrix.insert('C'); //2
	matrix.insert('D'); //3
	matrix.insert('E'); //4
	matrix.insert('F'); //5
	matrix.insert('G'); //6
	matrix.insert('H'); //7
	matrix.insert("A-B", 0, 1, 0);
	matrix.insert("A-C", 0, 2, 0);
	matrix.insert("B-D", 1, 3, 0);
	matrix.insert("C-B", 2, 1, 0);
	matrix.insert("C-F", 2, 5, 0);
	matrix.insert("D-E", 3, 4, 0);
	matrix.insert("D-F", 3, 5, 0);
	matrix.insert("F-B", 5, 1, 0);
	matrix.insert("G-E", 6, 4, 0);	
	matrix.insert("G-H", 6, 7, 0);
	matrix.insert("H-G", 7, 6, 0);
	
	std::cout << GREEN << "--- AdjaMatrix information start ---" << WHITE << endl;
	std::cout << matrix << WHITE << endl;
	std::cout << GREEN << "--- AdjaMatrix information end ---" << WHITE << endl;
	
	std::cout << GREEN << "going to DFS" << WHITE << endl;
	matrix.DFS(0);
#endif	

#if 0
	amo::AdjaMatrix<char, string> matrix;
	matrix.insert('0'); //0
	matrix.insert('1'); //1
	matrix.insert('2'); //2
	matrix.insert('3'); //3
	matrix.insert('4'); //4
	matrix.insert('5'); //5
	matrix.insert('6'); //6
	matrix.insert('7'); //7
	matrix.insert('8'); //8
	matrix.insert("0-1", 0, 1, 0);
	matrix.insert("1-0", 1, 0, 0);
	matrix.insert("1-4", 1, 4, 0);
	matrix.insert("4-1", 4, 1, 0);
	matrix.insert("4-5", 4, 5, 0);
	matrix.insert("5-4", 5, 4, 0);
	matrix.insert("5-7", 5, 7, 0);
	matrix.insert("7-5", 7, 5, 0);
	matrix.insert("3-6", 3, 6, 0);
	matrix.insert("6-3", 6, 3, 0);
	matrix.insert("6-8", 6, 8, 0);
	matrix.insert("8-6", 8, 6, 0);
	
	std::cout << GREEN << "--- AdjaMatrix information start ---" << WHITE << endl;
	std::cout << matrix << WHITE << endl;
	std::cout << GREEN << "--- AdjaMatrix information end ---" << WHITE << endl;
	
	std::cout << GREEN << "going to BFS" << WHITE << endl;
	matrix.BFS(0);
#endif	

#if 0
	amo::AdjaMatrix<char, string> matrix;
	matrix.insert('0'); //0
	matrix.insert('1'); //1
	matrix.insert('2'); //2
	matrix.insert('3'); //3
	matrix.insert('4'); //4
	matrix.insert('5'); //5
	matrix.insert('6'); //6
	matrix.insert('7'); //7
	matrix.insert('8'); //8
	matrix.insert("0-1", 0, 1, 0);
	matrix.insert("1-0", 1, 0, 0);
	matrix.insert("1-4", 1, 4, 0);
	matrix.insert("4-1", 4, 1, 0);
	matrix.insert("4-5", 4, 5, 0);
	matrix.insert("5-4", 5, 4, 0);
	matrix.insert("5-7", 5, 7, 0);
	matrix.insert("7-5", 7, 5, 0);
	matrix.insert("3-6", 3, 6, 0);
	matrix.insert("6-3", 6, 3, 0);
	matrix.insert("6-8", 6, 8, 0);
	matrix.insert("8-6", 8, 6, 0);
	
	std::cout << GREEN << "--- AdjaMatrix information start ---" << WHITE << endl;
	std::cout << matrix << WHITE << endl;
	std::cout << GREEN << "--- AdjaMatrix information end ---" << WHITE << endl;
	
	std::cout << GREEN << "going to DFS" << WHITE << endl;
	matrix.DFS(0);
#endif	

#if 0
	amo::AdjaMatrix<char, string> matrix;
	matrix.insert('0'); //0
	matrix.insert('1'); //1
	matrix.insert('2'); //2
	matrix.insert('3'); //3
	matrix.insert('4'); //4
	matrix.insert('5'); //5
	matrix.insert('6'); //6
	matrix.insert('7'); //7
	matrix.insert('8'); //8
	matrix.insert("0-1", 0, 1, 0);
	matrix.insert("1-0", 1, 0, 0);
	matrix.insert("1-4", 1, 4, 0);
	matrix.insert("4-1", 4, 1, 0);
	matrix.insert("4-5", 4, 5, 0);
	matrix.insert("5-4", 5, 4, 0);
	matrix.insert("5-7", 5, 7, 0);
	matrix.insert("7-5", 7, 5, 0);
	matrix.insert("3-6", 3, 6, 0);
	matrix.insert("6-3", 6, 3, 0);
	matrix.insert("6-8", 6, 8, 0);
	matrix.insert("8-6", 8, 6, 0);
	
	std::cout << GREEN << "--- AdjaMatrix information start ---" << WHITE << endl;
	std::cout << matrix << WHITE << endl;
	std::cout << GREEN << "--- AdjaMatrix information end ---" << WHITE << endl;
	
	std::cout << GREEN << "going to CCDFS" << WHITE << endl;
	matrix.CCDFS(0);
#endif

#if 0
	amo::AdjaMatrix<char, string> matrix;
	matrix.insert('0'); //0
	matrix.insert('1'); //1
	matrix.insert('2'); //2
	matrix.insert('3'); //3
	matrix.insert('4'); //4
	matrix.insert('5'); //5
	matrix.insert('6'); //6
	matrix.insert('7'); //7
	matrix.insert('8'); //8
	matrix.insert("0-1", 0, 1, 0);
	matrix.insert("1-2", 1, 2, 0);
	matrix.insert("1-4", 1, 4, 0);
	matrix.insert("2-0", 2, 0, 0);
	matrix.insert("2-3", 2, 3, 0);
	matrix.insert("2-5", 2, 5, 0);
	matrix.insert("3-2", 3, 2, 0);
	matrix.insert("4-5", 4, 5, 0);
	matrix.insert("4-6", 4, 6, 0);
	matrix.insert("5-4", 5, 4, 0);
	matrix.insert("5-6", 5, 6, 0);
	matrix.insert("5-7", 5, 7, 0);
	matrix.insert("6-7", 6, 7, 0);
	matrix.insert("7-8", 7, 8, 0);
	matrix.insert("8-6", 8, 6, 0);
	
	std::cout << GREEN << "--- AdjaMatrix information start ---" << WHITE << endl;
	std::cout << matrix << WHITE << endl;
	std::cout << GREEN << "--- AdjaMatrix information end ---" << WHITE << endl;
	
#if 0	
	amo::AdjaMatrix<char, string> matrixT = matrix.transpose();
	std::cout << MAGENTA << "--- Transpose information start ---" << WHITE << endl;
	std::cout << matrixT << WHITE << endl;
	std::cout << MAGENTA << "--- Transpose information end ---" << WHITE << endl;
#endif
	
	std::cout << GREEN << "going to SCCDFS" << WHITE << endl;
	matrix.SCCDFS(0);
#endif
	
#if 0
	amo::AdjaMatrix<char, string> matrix;
	matrix.insert('0'); //0
	matrix.insert('1'); //1
	matrix.insert('2'); //2
	matrix.insert('3'); //3
	matrix.insert('4'); //4
	matrix.insert('5'); //5
	matrix.insert('6'); //6
	matrix.insert('7'); //7
	matrix.insert('8'); //8
	matrix.insert('9'); //9
	matrix.insert('a'); //10
	matrix.insert('b'); //11
	matrix.insert('c'); //12
	matrix.insert('d'); //13
	matrix.insert('e'); //14
	matrix.insert("0-2", 0, 2, 0);
	matrix.insert("1-2", 1, 2, 0);
	matrix.insert("2-6", 2, 6, 0);
	matrix.insert("2-7", 2, 7, 0);
	matrix.insert("3-4", 3, 4, 0);
	matrix.insert("4-5", 4, 5, 0);
	matrix.insert("5-6", 5, 6, 0);
	matrix.insert("5-14", 5, 14, 0);
	matrix.insert("6-8", 6, 8, 0);
	matrix.insert("6-9", 6, 9, 0);
	matrix.insert("6-11", 6, 11, 0);
	matrix.insert("6-12", 6, 12, 0);
	matrix.insert("7-8", 7, 8, 0);
	matrix.insert("9-10", 9, 10, 0);
	matrix.insert("12-13", 12, 13, 0);
#if 0//DAG of not	
	matrix.insert("13-3", 13, 3, 0);
#endif	
	std::cout << GREEN << "going to topological sort from 0" << WHITE << endl;
	matrix.TopoSort(0);
	
	std::cout << GREEN << "going to topological sort from 4" << WHITE << endl;
	matrix.reset();
	matrix.TopoSort(4);
#endif

#if 0
	amo::AdjaMatrix<char, string> matrix;
	matrix.insert('A'); //0
	matrix.insert('B'); //1
	matrix.insert('C'); //2
	matrix.insert('D'); //3
	matrix.insert('E'); //4
	matrix.insert('F'); //5
	matrix.insert('G'); //6
	matrix.insert('H'); //7
	matrix.insert('I'); //8
	matrix.insert('J'); //9
	
	matrix.insert("A-B", 0, 1, 0);
	matrix.insert("B-A", 1, 0, 0);
	
	matrix.insert("A-I", 0, 8, 0);
	matrix.insert("I-A", 8, 0, 0);
	
	matrix.insert("B-C", 1, 2, 0);
	matrix.insert("C-B", 2, 1, 0);
	
	matrix.insert("C-D", 2, 3, 0);
	matrix.insert("D-C", 3, 2, 0);
	
	matrix.insert("C-H", 2, 7, 0);
	matrix.insert("H-C", 7, 2, 0);
	
	matrix.insert("D-E", 3, 4, 0);
	matrix.insert("E-D", 4, 3, 0);
	
	matrix.insert("E-G", 4, 6, 0);
	matrix.insert("G-E", 6, 4, 0);
	
	matrix.insert("G-D", 6, 3, 0);
	matrix.insert("D-G", 3, 6, 0);
	
	matrix.insert("G-F", 6, 5, 0);
	matrix.insert("F-G", 5, 6, 0);
	
	matrix.insert("H-A", 7, 0, 0);
	matrix.insert("A-H", 0, 7, 0);
	
	matrix.insert("I-J", 8, 9, 0);
	matrix.insert("J-I", 9, 8, 0);
	
	matrix.insert("J-A", 9, 0, 0);
	matrix.insert("A-J", 0, 9, 0);
	
	std::cout << GREEN << "going to BCC for articulation vertices" << WHITE << endl;
	matrix.BCC(0);
#endif

#if 0
	amo::AdjaMatrix<char, string> matrix;
	matrix.insert('0'); //0
	matrix.insert('1'); //1
	matrix.insert('2'); //2
	matrix.insert('3'); //3
	matrix.insert('4'); //4
	matrix.insert('5'); //5
	matrix.insert('6'); //6
	matrix.insert('7'); //7
	matrix.insert('8'); //8
	matrix.insert("0-1", 0, 1, 0);
	matrix.insert("1-0", 1, 0, 0);
	matrix.insert("1-4", 1, 4, 0);
	matrix.insert("4-1", 4, 1, 0);
	matrix.insert("4-5", 4, 5, 0);
	matrix.insert("5-4", 5, 4, 0);
	matrix.insert("5-7", 5, 7, 0);
	matrix.insert("7-5", 7, 5, 0);
	matrix.insert("3-6", 3, 6, 0);
	matrix.insert("6-3", 6, 3, 0);
	matrix.insert("6-8", 6, 8, 0);
	matrix.insert("8-6", 8, 6, 0);
	
	std::cout << GREEN << "going to DFS" << WHITE << endl;
	matrix.DFS(0);

	std::cout << GREEN << "going to PFS for DFS" << WHITE << endl;
	matrix.reset();
	matrix.PFS_DFS(0);
#endif	

#if 0
	amo::AdjaMatrix<char, string> matrix;
	matrix.insert('0'); //0
	matrix.insert('1'); //1
	matrix.insert('2'); //2
	matrix.insert('3'); //3
	matrix.insert('4'); //4
	matrix.insert('5'); //5
	matrix.insert('6'); //6
	matrix.insert('7'); //7
	matrix.insert('8'); //8
	matrix.insert("0-1", 0, 1, 0);
	matrix.insert("1-0", 1, 0, 0);
	matrix.insert("1-4", 1, 4, 0);
	matrix.insert("4-1", 4, 1, 0);
	matrix.insert("4-5", 4, 5, 0);
	matrix.insert("5-4", 5, 4, 0);
	matrix.insert("5-7", 5, 7, 0);
	matrix.insert("7-5", 7, 5, 0);
	matrix.insert("3-6", 3, 6, 0);
	matrix.insert("6-3", 6, 3, 0);
	matrix.insert("6-8", 6, 8, 0);
	matrix.insert("8-6", 8, 6, 0);
	
	std::cout << GREEN << "going to BFS" << WHITE << endl;
	matrix.BFS(0);
	
	std::cout << GREEN << "going to PFS for DFS" << WHITE << endl;
	matrix.reset();
	matrix.PFS_BFS(0);
#endif	

#if 0
	amo::AdjaMatrix<char, string> matrix;
	matrix.insert('A'); //0
	matrix.insert('B'); //1
	matrix.insert('C'); //2
	matrix.insert('D'); //3
	matrix.insert('E'); //4
	matrix.insert('F'); //5
	matrix.insert('G'); //6
	matrix.insert('H'); //7
	matrix.insert("A-B", 0, 1, 4);
	matrix.insert("A-D", 0, 3, 6);
	matrix.insert("B-A", 1, 0, 4);
	matrix.insert("B-C", 1, 2, 12);
	matrix.insert("C-D", 2, 3, 9);
	matrix.insert("C-E", 2, 4, 1);
	matrix.insert("C-F", 2, 5, 2);
	matrix.insert("D-A", 3, 0, 6);
	matrix.insert("D-C", 3, 2, 9);
	matrix.insert("D-E", 3, 4, 13);
	matrix.insert("D-G", 3, 6, 2);
	matrix.insert("E-C", 4, 2, 1);
	matrix.insert("E-D", 4, 3, 13);
	matrix.insert("E-F", 4, 5, 5);
	matrix.insert("E-G", 4, 6, 11);
	matrix.insert("E-H", 4, 7, 8);
	matrix.insert("F-C", 5, 2, 2);
	matrix.insert("F-E", 5, 4, 5);
	matrix.insert("F-H", 5, 7, 7);
	matrix.insert("G-D", 6, 3, 2);
	matrix.insert("G-E", 6, 4, 11);
	matrix.insert("G-H", 6, 7, 14);
	
	std::cout << GREEN << "going to prim for MST" << WHITE << endl;
	matrix.PFS_Prim(0);
#endif

#if 0
	amo::AdjaMatrix<char, string> matrix;
	matrix.insert('S'); //0
	matrix.insert('A'); //1
	matrix.insert('B'); //2
	matrix.insert('C'); //3
	matrix.insert('D'); //4
	matrix.insert('E'); //5
	matrix.insert('F'); //6
	matrix.insert('G'); //7
	matrix.insert("S-A", 0, 1, 9);
	matrix.insert("S-C", 0, 3, 14);
	matrix.insert("S-F", 0, 6, 15);
	matrix.insert("A-B", 1, 2, 25);
	matrix.insert("B-D", 2, 4, 2);
	matrix.insert("C-B", 3, 2, 18);
	matrix.insert("C-D", 3, 4, 30);
	matrix.insert("C-F", 3, 6, 5);
	matrix.insert("D-E", 4, 5, 11);
	matrix.insert("D-G", 4, 7, 16);
	matrix.insert("E-B", 5, 2, 6);
	matrix.insert("E-G", 5, 7, 6);
	matrix.insert("F-D", 6, 4, 20);
	matrix.insert("F-G", 6, 7, 40);
	
	std::cout << GREEN << "going to Dijkstra for the shortest path" << WHITE << endl;
	int s = 0;
	
	matrix.priority(s) = 0;
	matrix.Dijkstra(s);
#endif
#endif

#if 0
	std::cout << GREEN << "****************** binary search tree ******************\n" << WHITE << std::endl;
	amo::BST<int> bst;
	bst.insert(36);
	bst.insert(27);
	bst.insert(6);
	bst.insert(58);
	bst.insert(53);
	bst.insert(69);
	bst.insert(40);
	bst.insert(46);
	bst.insert(64);

	bst.remove(36);
	bst.remove(27);
	bst.remove(6);
	bst.remove(58);
	bst.remove(53);
	bst.remove(69);
	bst.remove(40);
	bst.remove(46);
	//bst.remove(64);

	cout << bst << endl;
	bst.traverseIn();	
#endif

#if 0
	std::cout << GREEN << "****************** AVL tree ******************\n" << WHITE << std::endl;
	amo::AVL<int> avl;
	
	/*
	avl.insert(36);
	std::cout << std::endl;
	avl.insert(27);
	std::cout << std::endl;
	avl.insert(58);
	std::cout << std::endl;
	
	avl.insert(53);
	std::cout << std::endl;
	
	avl.insert(69);
	std::cout << std::endl;
	
	avl.insert(40);
	std::cout << std::endl;
	
	avl.insert(46);
	std::cout << std::endl;
	
	avl.insert(64);
	std::cout << std::endl;
	
	avl.insert(66); //err
	std::cout << std::endl;
	*/
	int i = 5;
	while (0<i--) avl.insert(i);
	std::cout << avl << std::endl;
	amo::BinNode<int>* r = avl.root();
	amo::BinNode<int>* node = r;
	std::stack<amo::BinNode<int>*> stack;
	while (true) {
		if (node) {
			stack.push(node);
			node = node->lchild;
		}
		else {
			if (stack.empty()) break;
			node = stack.top();
			stack.pop();
			if (!(avl.balanceAVL(node))) {
				std::cout << RED << node->data << " is not balanced:" << avl.balanceFactor(node) << std::endl;
			}
			else {
				std::cout << WHITE << node->data << " is balanced" << std::endl;
			}
			node = node->rchild;
		}
	}
	
#if 1
	i = 5;
	while (!stack.empty()) stack.pop();
	while (0<i--) {
		std::cout << WHITE <<"----------REMOVE " << i << " START ----------------------" << std::endl;
		avl.remove(i);
		if (avl.empty()) {
			std::cout << WHITE <<"----------REMOVE " << i << " END   ----------------------" << std::endl;
			break;
		}
		r = avl.root();
		stack.push(r);
		while (true) {
			if (stack.empty()) break;
			node = stack.top();
			stack.pop();
			if (!(avl.balanceAVL(node))) {
				std::cout << RED << node->data << " is not balanced:" << avl.balanceFactor(node) << std::endl;
			}
			else {
				std::cout << node->data << " is balanced" << std::endl;
			}
			if (node->hasRightChild()) stack.push(node->rchild);
			if (node->hasLeftChild()) stack.push(node->lchild);
		}
		std::cout << WHITE <<"----------REMOVE " << i << " END   ----------------------" << std::endl;
	}
#endif	
	/*
	int e = 36;
	BinNode<int>* node = avl.search(e);
	int bal_fac = avl.balanceFactor(node);
	BinNode<int>* taller = BST<int>::tallerChild(node);
	cout << YELLOW << "Stature of element:" << e << " is " << amo::BST<int>::stature(node) <<  WHITE << endl;
	cout << YELLOW << "Balance factor of element:" << e << " is " << bal_fac <<  WHITE << endl;
	cout << YELLOW << "Taller child of element:" << e << " is " << taller->data <<  WHITE << endl;
	*/
	
	std::cout << avl << std::endl;
	//avl.traversePre();	
	//avl.traverseIn();	
	//avl.traversePost();	
	avl.traverseLevel();	
#endif

#if 0
	std::cout << GREEN << "****************** Dictionary ******************\n" << WHITE << std::endl;
	amo::SkipList<int, int> dict;
	/*
	amo::Entry<int, int> e1(0, 10);
	amo::Entry<int, int> e2(1, 20);
	amo::QuadListNode<Entry<int, int>> n1(e1);
	n1.insertSuccAbove(e2, NULL);
	std::cout << "n1:" << n1;
	std::cout << "n2:" << *n1.succ;
	std::cout << "n1:" << *((*n1.succ).pred);
	*/
	int amount = 10;
	dict._height = (int) sqrt(amount) - 1;
	for (int i=1; i<=amount; i++) {
		dict.put(10+i, 30+i);
		std::cout << std::endl;
	}
	
	/*
	for (int i=1; i<=amount; i++) {
		std::cout << GREEN << "GET " << 10+i << "..." << WHITE << std::endl;
		dict.get(10+i);
	}
	*/
	
	for (int i=1; i<=amount; i++) {
		if (!dict.put(10+i, 99-i)) {
			dict.remove(10+i);
			if (!dict.put(10+i, 99-i)) {
				std::cout << RED << "FAILED PUT:" << 10+i << WHITE << std::endl;
			}
		}
		std::cout << std::endl;
	}
	
	dict.traverseTower();
	
#endif


#if 1
	std::cout << GREEN << "****************** Bitmap ******************\n" << WHITE << std::endl;
	amo::BMP bmp;
	bmp.load("finger.bmp");
	cout << bmp << endl;
	
	
	
#endif
	std::cout << GREEN << "\n****************** main return ******************" << WHITE << std::endl;
	return 0;
}