 /*************************
  *  text_view.cpp
  *  
  *
  *  editor: amo
  *************************/
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <text_view.h>
#include <screen.h>
#include <view.h>
#include <text.h>

/* -------------------------------------------------------------------- */
/* my define macro                                                     */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* global variables                                                     */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* implements                                                           */
/* -------------------------------------------------------------------- */
MyTextView::~MyTextView(){
	std::cout << "[MyTextView::~MyTextView()]: >>>" << std::endl;
}

void MyTextView::onLayout(int changed, int l, int r, int t, int b)
{	
	int width;
	int height;
	std::cout << "[MyTextView::onLayout()]: >>> " << "text:" << text << std::endl;
	
	if(l == getLeft()) {
		std::cout << "[MyTextView::onLayout()]: ... no move on left" << std::endl;
		if(r == getRight()){
			std::cout << "[MyTextView::onLayout()]: ... no move on right" << std::endl;
			if(t == getTop()){
				std::cout << "[MyTextView::onLayout()]: ... no move on top" << std::endl;
				if(b == getBottom()){
					std::cout << "[MyTextView::onLayout()]: ... no move on bottom" << std::endl;
					return;
				} 
			} 
		} 
	}	
	
	setLeft(l);
	setRight(r);
	setTop(t);
	setBottom(b);
	
	width = r - l;
	height = b - t;
	if(changed) std::cout << "[MyTextView::onLayout()]: ... width:" << width << " and height:" << height << std::endl;
}

int MyTextView::addViewOnScreen(MyScreen &screen)
{
	std::cout << "[MyTextView::addViewOnScreen()]: >>>" << std::endl;
	return screen.getPixelX() - (getRight() - getLeft()) + screen.getPixelY() - (getBottom() - getTop());
}

void MyTextView::show()
{
	std::cout << "[MyTextView::show()]: >>>" << std::endl;
	showPosition();
}

void MyTextView::showSuperField()
{
	std::cout << "[MyTextView::showSuperField()]: now at left   :" << left << std::endl;
	std::cout << "[MyTextView::showSuperField()]: now at right  :" << right << std::endl;
	std::cout << "[MyTextView::showSuperField()]: now at top    :" << top << std::endl;
	std::cout << "[MyTextView::showSuperField()]: now at bottom :" << bottom << std::endl;
}

/* Override */
void MyTextView::showPosition(){
	std::cout << "[MyTextView::showPosition()]: >>>" << std::endl;
	std::cout << "[MyTextView::showPosition()]: now at left   :" << left << std::endl;
	std::cout << "[MyTextView::showPosition()]: now at right  :" << right << std::endl;
	std::cout << "[MyTextView::showPosition()]: now at top    :" << top << std::endl;
	std::cout << "[MyTextView::showPosition()]: now at bottom :" << bottom << std::endl;
}	

void MyTextView::displayLayout(int l, int r, int t, int b)
{
	std::cout << "[MyTextView::displayLayout()]: >>>" << std::endl;
	layout(l, r, t, b);
}