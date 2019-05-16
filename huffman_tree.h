#ifndef _HUFFMAN_TREE_H_
#define _HUFFMAN_TREE_H_

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stack.h>
#include <map>
#include <typeinfo> 

#include <bin_node.h>
#include <bin_tree.h>

namespace amo {

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

template<typename T>
class HuffmanTree : public BinTree<T> { 
typedef struct functor_traverse {
	void operator() (HuffmanTree<T> const& tree) {
		std::cout << tree << WHITE << std::endl;
	}
} FUNCTOR_TRAVERSER;
private:

public:
	HuffmanTree() : BinTree<T>() {
		std::cout << "[HuffmanTree::HuffmanTree()]: this:" << this << ", type:" << typeid(T).name() << WHITE << std::endl;
	}
	HuffmanTree(BinNode<T>* node) : BinTree<T>(node) {
		std::cout << "[HuffmanTree::HuffmanTree(BinNode<T>*)]: this:" << this << ", root:" << this->_root->data << ", size:" << this->_size << WHITE << std::endl;
	}
	~HuffmanTree() {
		std::cout << "[HuffmanTree::~HuffmanTree()]: size:" << this->_size << WHITE << std::endl;
		if (0<this->size() && this->_root!=NULL) this->remove(this->_root);
	}
	void encode(const char* inputFilePath, const char* outputFilePath);
	
	
friend std::ostream& operator<<(std::ostream& os, const HuffmanTree<T>& tree) {
	os  << WHITE << "[this]:" << &tree << endl;
	os  << WHITE << "[root]:" << tree.root << endl;
	os  << WHITE << "[size]:" << tree.size << endl;
	return os;
}
};

template<typename T>
void amo::HuffmanTree<T>::encode(const char* inputFilePath, const char* outputFilePath) {
	std::map<char, int> probs;
	std::ifstream fis(inputFilePath, std::ios::binary|std::ios::in);
	char c;
	int len;
	int len_tmp;
	
	while(fis.get(c)) {
		std::cout << "got char:" << c << std::endl;
		probs[c]++;
		len++;
	}

	if(fis.eof()) std::cout << "EOF reached" << std::endl;
	else std::cout << "error read:" << fis.fail() << std::endl;

	for (std::map<char, int>::iterator it=probs.begin();it!=probs.end();it++) {
		cout << YELLOW << "probs[" << distance(probs.begin(),it) << "]: a pair at " << &(*it)
			<< " holding key:" << it->first << " at " << &it->first
			<< " => value:" << it->second << " at " << &it->second << WHITE << endl; 
	}

	fis.clear();
	fis.seekg(0, fis.end);
	len_tmp = fis.tellg();
	fis.seekg(0, fis.beg);
	
	if (len == len_tmp) std::cout << "completed to read" << ", len:" << len << " and len_tmp:" << len_tmp << std::endl;
	else std::cout << "not completed to read:" << ", len:" << len << " and len_tmp:" << len_tmp << std::endl;
}








};
#endif