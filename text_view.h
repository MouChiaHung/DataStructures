#ifndef _TEXT_VIEW_H_
#define _TEXT_VIEW_H_

#include <view.h>
#include <text.h>
#include <screen.h>

class MyScreen;

class MyTextView:private MyView, public MyText {
	MyText mText;
	MyScreen mScreen;
public:
	void 	onLayout(int changed, int l, int r, int t, int b);
	int 	addViewOnScreen(MyScreen &);
	void 	show();
	void 	showSuperField();
	void 	showPosition();
	void 	displayLayout(int l, int r, int t, int b);
	MyTextView():MyView(0,0,0,0), MyText(), mScreen(), mText(){
		std::cout << "[MyTextView::MyTextView()]: >>> id:" << id << ", text:" << text << std::endl;
	};
	MyTextView(char *src, int l, int r, int t, int b):MyView(l, r, t, b), MyText(src), mScreen(), mText(src){
	//MyTextView(char *src, int l, int r, int t, int b):MyView(l, r, t, b), MyText(src){
		std::cout << "[MyTextView::MyTextView(char, int, int, int, int)]: >>> id:" << id << ", text:" << text << std::endl;
	};
	~MyTextView();
};

#endif