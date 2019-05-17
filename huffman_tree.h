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

class Model {
public:
	char c;
	int prob;
	Model():c(0),  prob(0) {}
	Model(int character, int probability):c(character),  prob(probability) {}
	~Model() {}
	bool operator==(Model& node) {
		bool ret = (prob == node.prob) ? true : false;
		//std::cout << "[Model::operator==()]:" << ret << WHITE << std::endl;
		return ret;
	}
	bool operator<(Model& node) {
		bool ret = (prob < node.prob) ? true : false;
		//std::cout << "[Model::operator<()]:" << ret << WHITE << std::endl;
		return ret;
	}
	bool operator>(Model& node) {
		bool ret = (prob > node.prob) ? true : false;
		//std::cout << "[Model::operator>()]:" << ret << WHITE << std::endl;
		return ret;
	}
	
friend std::ostream& operator<<(std::ostream& os, const Model& node) {
	os  << WHITE << "" << endl;
	//os  << WHITE << "[this]:" << &node << endl;
	os  << WHITE << "[char]:" << node.c << endl;
	os  << WHITE << "[prob]:" << node.prob << endl;
	return os;
}
};

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
	void grow(std::list<Model*>& list);
	
friend std::ostream& operator<<(std::ostream& os, const HuffmanTree<T>& tree) {
	os  << WHITE << "[this]:" << &tree << endl;
	os  << WHITE << "[root]:" << tree.root << endl;
	os  << WHITE << "[size]:" << tree.size << endl;
	return os;
}


};

bool compare(amo::Model* first, amo::Model* second)
{
  amo::Model& f = *first;
  amo::Model& s = *second;
  return f < s;
}

template<typename T>
void amo::HuffmanTree<T>::encode(const char* inputFilePath, const char* outputFilePath) {
	std::map<char, int> probs;
	std::list<Model*> table;
	//std::stack<Model*> stack;
	std::ifstream fis(inputFilePath, std::ios::binary|std::ios::in);
	char c;
	int len;
	int len_tmp;
	
	while(fis.get(c)) {
		std::cout << "got char:" << c << std::endl;
		if (c < 32) continue; //space is 32
		probs[c]++;
		len++;
	}

	if(fis.eof()) std::cout << "EOF reached" << std::endl;
	else std::cout << "error read:" << fis.fail() << std::endl;

	for (std::map<char,int>::iterator it=probs.begin();it!=probs.end();it++) {
		cout << YELLOW << "probs[" << distance(probs.begin(),it) << "]: a pair at " << &(*it)
			<< " holding key:" << it->first << " at " << &it->first
			<< " => value:" << it->second << WHITE << endl; 
	}

	fis.clear();
	fis.seekg(0, fis.end);
	len_tmp = fis.tellg();
	fis.seekg(0, fis.beg);
	if (len == len_tmp) std::cout << "completed to read" << ", len:" << len << " and len_tmp:" << len_tmp << std::endl;
	else std::cout << "not completed to read:" << ", len:" << len << " and len_tmp:" << len_tmp << std::endl;
	
	for (std::map<char,int>::iterator it=probs.begin();it!=probs.end();it++) {
		Model* node = new Model(it->first, it->second);
		table.push_back(node);
	}
	
	std::cout << GREEN << "going to sort" << WHITE << std::endl;
	table.sort(compare);
	for (std::list<Model*>::iterator it=table.begin();it!=table.end();it++) {
		cout << CYAN << "table[" << distance(table.begin(),it) << "]:" << **it;
		//stack.push(*it);
	}
	
#if 0	
	int i = 0;
	int size = stack.size();	
	while (!stack.empty()) {
		cout << GREEN <<  "stack[" << (size-1)-i << "]:" << *stack.top();
		i++;
		stack.pop();
	}
#endif
	std::cout << GREEN << "going to grow" << WHITE << std::endl;
	grow(table);
}

template<typename T> 
void amo::HuffmanTree<T>::grow(std::list<Model*>& list) { //ascendantly sorted list
	Model* l;
	Model* r;
	Model* m;
	BinNode<T>* lchild;
	BinNode<T>* rchild;
	BinNode<T>* vertex;
	std::list<Model*>::iterator it = list.begin();
	while (it!=list.end()) {
		if (std::next(it,1) == list.end()) { //a tail
			r = *it;
			m = new Model('*', (this->_root->data.prob)+(r->prob));
			lchild = this->_root;
			rchild = new BinNode<T>(*r);
			vertex = new BinNode<T>(*m);
			lchild->parent = vertex;
			rchild->parent = vertex;
			vertex->lchild = lchild;
			vertex->rchild = rchild;
			this->_root = vertex;
			break;
		}
		else {
			l = *it;
			it++;
			r = *it;
			m = new Model('*', l->prob+r->prob);		
			if (this->_root!=NULL && *l == (this->_root)->data) {
				lchild = this->_root;
			}
			else {
				lchild = new BinNode<T>(*l);
			}
			if (this->_root!=NULL && *r == (this->_root)->data) {
				rchild = this->_root;
			}
			else {
				rchild = new BinNode<T>(*r);
			}
			
			vertex = new BinNode<T>(*m);
			std::cout << CYAN << "lchild" << *lchild << WHITE;
			std::cout << CYAN << "rchild" << *rchild << WHITE;
			std::cout << CYAN << "vertex" << *vertex << WHITE;
			lchild->parent = vertex;
			rchild->parent = vertex;
			vertex->lchild = lchild;
			vertex->rchild = rchild;
			this->_root = vertex;
			for (std::list<Model*>::iterator itt=it;itt!=list.end();itt++) {
				if ((*m < **itt) || (*m == **itt)) {
					list.insert(itt, m);
					break;
				}
				else if (std::next(itt,1) == list.end()) {
					list.push_back(m);
					break;
				}
			}
			it++;
		}
		this->traverseLevel();
	}
	for (std::list<Model*>::iterator iterator=list.begin();iterator!=list.end();iterator++) cout << CYAN << "list[" << distance(list.begin(),iterator) << "]:" << **iterator;
	this->traverseLevel();
	
}






};
#endif