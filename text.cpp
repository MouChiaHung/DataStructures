 /*************************
  *  text.cpp
  *  
  *
  *  editor: amo
  *************************/
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
MyText::MyText(char *src){
	if(strlen(src) > 127){
		std::cout << "[MyText]: !!! limit of text is 127" << std::endl;
	}
	memset(text, 0, 128);
	strncpy(text, src, strlen(src)+1);
	length =  strlen(text);
	std::cout << "[MyText::MyText(char*)]: >>> " << this << ", text:" << text << ", length:" << length << std::endl;
}

MyText::MyText(){
	std::cout << "[MyText::MyText()]: >>> " << this << ", text:" << text << ", length:" << length << std::endl;
}

MyText::~MyText(){
	std::cout << "[MyText::~MyText()]: >>> " << this << ", release text:" << text << ", release length:" << length << std::endl;
}

void MyText::showText(){
	std::cout << "[MyText::showText()]: >>> showText()" << std::endl;
	std::cout << "[MyText::showText()]: now text:" << text << " and arg:" << arg << std::endl;
}	

void MyText::setText(char *src){
	std::cout << "[MyText::setText()]: >>> setText()" << std::endl;
	strncpy(text, src, strlen(src)+1);
	length =  strlen(text);
	std::cout << "[MyText::setText()]: text:" << text << std::endl;
	std::cout << "[MyText::setText()]: length:" << length << std::endl;
}

void MyText::getText(char *dest){
	strncpy(dest, text, strlen(text)+1);
	std::cout << "[MyText::getText()]: text" << text << " to dest:" << dest << std::endl;
}