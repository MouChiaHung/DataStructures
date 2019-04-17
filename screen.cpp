 /*************************
  *  screen.cpp
  *  
  *
  *  editor: amo
  *************************/
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <screen.h>

/* -------------------------------------------------------------------- */
/* my define macro                                                     */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* global variables                                                     */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* implements                                                           */
/* -------------------------------------------------------------------- */
MyScreen::MyScreen(int x, int y){
	std::cout << "[MyScreen::MyScreen(int, int)]: ... pixelX:" << pixelX << " and pixelY:" << pixelY << std::endl;
	pixelX = x;
	pixelY = y;
}

MyScreen::MyScreen(){
	std::cout << "[MyScreen::MyScreen()]: ... pixelX:" << pixelX << " and pixelY:" << pixelY << std::endl;
	pixelX = 0;
	pixelY = 0;
}

MyScreen::~MyScreen(){
	std::cout << "[MyScreen::~MyScreen()]: ... pixelX:" << pixelX << " and pixelY:" << pixelY << std::endl;
}

void MyScreen::showSize(){
	std::cout << "[MyScreen::showSize()]: ... pixelX:" << pixelX << " and pixelY:" << pixelY << std::endl;
}	

void MyScreen::setX(int x){
	pixelX = x;
}

void MyScreen::setY(int y){
	pixelY = y;
}

int MyScreen::getPixelX(){
	return pixelX;
}

int MyScreen::getPixelY(){
	return pixelY;
}
	