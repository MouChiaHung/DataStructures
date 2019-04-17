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
#include <view.h>

/* -------------------------------------------------------------------- */
/* my define macro                                                     */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* global variables                                                     */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* implements                                                           */
/* -------------------------------------------------------------------- */
MyView::MyView(int l, int r, int t, int b){
	std::cout << "[MyView::MyView()]: >>> MyView()" << std::endl;
	left = l;
	right = r;
	top = t;
	bottom = b;
	id = 5566;
}

MyView::~MyView(){
#if 0	
	std::cout << "[MyView::~MyView()]: >>> ~MyView()" << std::endl;
	std::cout << "[MyView::~MyView()]: release at left   :" << left << std::endl;
	std::cout << "[MyView::~MyView()]: release at right  :" << right << std::endl;
	std::cout << "[MyView::~MyView()]: release at top    :" << top << std::endl;
	std::cout << "[MyView::~MyView()]: release at bottom :" << bottom << std::endl;
#endif
}

void MyView::showPosition(){
	std::cout << "[MyView]::showPosition(): >>> showPosition()" << std::endl;
	std::cout << "[MyView]::showPosition(): now at left   :" << left << std::endl;
	std::cout << "[MyView]::showPosition(): now at right  :" << right << std::endl;
	std::cout << "[MyView]::showPosition(): now at top    :" << top << std::endl;
	std::cout << "[MyView]::showPosition(): now at bottom :" << bottom << std::endl;
}	

void MyView::setLeft(int l){
	left = l;
}

void MyView::setRight(int r){
	right = r;
}

void MyView::setTop(int t){
	top = t;
}

void MyView::setBottom(int b){
	bottom = b;
}

int MyView::getLeft(){
	return left;
}

int MyView::getRight(){
	return right;
}

int MyView::getTop(){
	return top;
}

int MyView::getBottom(){
	return bottom;
}

void MyView::layout(int l, int r, int t, int b){
	std::cout << "[MyView]::layout(): >>> layout()" << std::endl;
	int changed = 1;
	onLayout(changed, l, r, t, b);
}