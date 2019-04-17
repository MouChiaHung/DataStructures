#ifndef _SPACE_H_
#define _SPACE_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

namespace mystd{
	int group;
namespace myfstream{
	class ifstream {
		private:
			int user;
			char 	path[32];
			int 	pos; //position of the character to be extracted from filebuf
			char 	filebuf[32];
		public:
			ifstream(char* src){
				//std::cout << "[mystd::myfstream::ifstream::ifstream(char*)]: strlen(amo):" << strlen("amo") << std::endl;
				if(strlen(src) <= sizeof(path) )strncpy(path, src, strlen(src)+1);
				pos = 0;
				memset(filebuf, 'X', sizeof(filebuf));
				std::cout << "[mystd::myfstream::ifstream::ifstream(char*)]: >>> ifstream file path:" << path << std::endl;
			}
			void read(char *src, int length){
				std::cout << "[mystd::myfstream::ifstream::read(char*,int)]: >>> pos:" << pos << ", length:" << length << std::endl;
				if(!path[0]){
					std::cout << "[mystd::myfstream::ifstream::read(char*,int)]: !!! file path is null" << std::endl;
					return;
				}
				if(length <= sizeof(filebuf)-pos){
					std::cout << "[mystd::myfstream::ifstream::read(char*,int)]: going to memcpy() for " << length << "bytes" << std::endl;
					memcpy(filebuf+pos, src, length);
					std::cout << "[mystd::myfstream::ifstream::read(char*,int)]: data extracted from filebuf:" << std::endl;
					for(int i=pos; i<length; i++) std::cout << filebuf[i] << std::endl;
					std::cout << std::endl;
				}else{
					std::cout << "[mystd::myfstream::ifstream::read(char*,int)]: going to memcpy() for only " << sizeof(filebuf)-pos << "bytes" << std::endl;
					memcpy(filebuf+pos, src, sizeof(filebuf)-pos);
					std::cout << "[mystd::myfstream::ifstream::read(char*,int)]: data extracted from filebuf:" << std::endl;
					for(int i=pos; i<sizeof(filebuf); i++) std::cout << filebuf[i] << std::endl;
					std::cout << std::endl;
				}
			}
			void seekg(int offset, int mode){
				if(offset >= sizeof(filebuf)){
					std::cout << "offset is beyond file buffer size" << std::endl;
					return;
				}
				switch(mode){
					case 0: { //current
						pos = offset;
						break;
					}
					case 1: { //begin
						pos = 0;
						break;
					}
					case 2: {
						pos = sizeof(filebuf)-1; //end
						break;
					}
				}
			}
			int tellg(){
				return pos;
			}
			void setUser(int user_id){
				user = user_id;
			}
			int getUser(){
				return user;
			}
			/**
			 * The rule is that, when looking for a suitable function overload
			 * , both the current namespace and all namespaces of the argument type definitions are considered.
			 * This is called Argument Dependent Lookup (ADL).
			 */
			friend std::istream& operator>>(std::istream &stream, ifstream &fis);
			friend std::ostream& operator<<(std::ostream &stream, ifstream &fis);
	};
	class ofstream {
		private:
			int user;
			char 	path[32];
			int 	pos;
			char 	filebuf[32];
		public:	
			ofstream(char* src){
				if(strlen(src) <= sizeof(path) )strncpy(path, src, strlen(src)+1);
				pos = 0;
				memset(filebuf, 'Y', sizeof(filebuf));
				std::cout << "[mystd::myfstream::ofstream::ofstream(char*)]: >>> ofstream file path:" << path << std::endl;
			}
			void write(char *src, int length){
				std::cout << "[mystd::myfstream::ofstream::write(char*,int)]: >>> pos:" << pos << ", length:" << length << std::endl;
				if(!path[0]){
					std::cout << "[mystd::myfstream::ofstream::write(char*,int)]: !!! file path is null" << std::endl;
					return;
				}
				if(length <= sizeof(filebuf)-pos){
					std::cout << "[mystd::myfstream::ofstream::write(char*,int)]: going to memcpy() for " << length << "bytes" << std::endl;
					memcpy(filebuf+pos, src, length);
					std::cout << "[mystd::myfstream::ifstream::read(char*,int)]: data written to filebuf:" << std::endl;
					for(int i=pos;i < length; i++) std::cout << filebuf[i] << std::endl;
					std::cout << std::endl;
				}else{
					std::cout << "[mystd::myfstream::ofstream::write(char*,int)]: going to memcpy() for only " << sizeof(filebuf)-pos << "bytes" << std::endl;
					memcpy(filebuf+pos, src, sizeof(filebuf)-pos);
					std::cout << "[mystd::myfstream::ifstream::read(char*,int)]: data written to filebuf:" << std::endl;
					for(int i=pos;i < sizeof(filebuf); i++) std::cout << filebuf[i] << std::endl;
					std::cout << std::endl;
				}
			}
			void seekp(int offset, int mode){
				if(offset >= sizeof(filebuf)){
					std::cout << "offset is beyond file buffer size" << std::endl;
					return;
				}
				switch(mode){
					case 0: { //current
						pos = offset;
						break;
					}
					case 1: { //begin
						pos = 0;
						break;
					}
					case 2: {
						pos = sizeof(filebuf)-1; //end
						break;
					}
				}
			}
			int tellp(){
				return pos;
			}
			void setUser(int user_id){
				user = user_id;
			}
			int getUser(){
				return user;
			}
			friend std::ostream& operator<<(std::ostream &stream, mystd::myfstream::ofstream &fos);
			friend std::istream& operator>>(std::istream &stream, mystd::myfstream::ofstream &fos);
	};
	/*
	std::istream& operator>>(std::istream &stream, mystd::myfstream::ifstream &fis);
	std::ostream& operator<<(std::ostream &stream, mystd::myfstream::ifstream &fis);
	std::ostream& operator<<(std::ostream &stream, mystd::myfstream::ofstream &fos);
	std::istream& operator>>(std::istream &stream, mystd::myfstream::ofstream &fos);
	*/
};
};

#endif