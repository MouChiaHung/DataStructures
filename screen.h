#ifndef _SCREEN_H_
#define _SCREEN_H_

//#include <text_view.h>
//class MyTextView;

class MyScreen {
	int pixelX;
	int pixelY;
public:
	int 	getPixelX();
	int 	getPixelY();
	void 	setX(int x);
	void 	setY(int y);
	void 	showSize();
	friend int layout(MyScreen screen);
	//friend int MyTextView::addViewOnScreen(MyScreen &); //a interface would be implemented by MyTextView, MyScreen passes itself as parameter to MyTextView.
	MyScreen(int x, int y);
	MyScreen();
	~MyScreen();
};

#endif