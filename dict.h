#ifndef _DICT_H_
#define _DICT_H_

#include <iostream>
#include <stdio.h>

#include <entry.h>

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

template<typename K, typename V>
class Dictionary {
protected:	

public:
	Dictionary() {}
	~Dictionary() {}
	//virtual int size() const = 0;
	//virtual bool put(K, V) = 0;
	//virtual bool remove(K k) = 0;
	//virtual V* get(K k) = 0;

friend std::ostream& operator<<(std::ostream& os, const Dictionary<K, V>& dictionary) {
	return os;
}
};

template<typename E>
class QuadListNode {
private:

public:
	E entry;
	QuadListNode<E>* pred;
	QuadListNode<E>* succ;
	QuadListNode<E>* above;
	QuadListNode<E>* below;
	QuadListNode(E e = E(), QuadListNode<E>* p = NULL, QuadListNode<E>* s = NULL, QuadListNode<E>* a = NULL, QuadListNode<E>* b = NULL) : entry(e), pred(p), succ(s), above(a), below(b) {}
	QuadListNode<E>* insertSuccAbove(E const& e, QuadListNode<E>* b);
friend std::ostream& operator<<(std::ostream& os, const QuadListNode<E>& node) {
	os << "[" << node.entry.key;
	os << "/" << node.entry.val << "] ";
	return os;
}		
};

template<typename E>
class QuadList {
private:
	
protected:
	void init();
	
public:
	int _size;
	QuadListNode<E>* head;
	QuadListNode<E>* tail;
	QuadList() { 
		init(); 
	}
	~QuadList() {
		//clear();
		if (head) delete head;
		if (tail) delete tail;
	}
	int size() {
		return _size;
	}
	bool empty() {
		return _size <= 0;
	}
	QuadListNode<E>* first() {
		if (head) return head->succ;
		else return NULL;
	}
	QuadListNode<E>* last() {
		if (tail) return tail->pred;
		return NULL;	
	}
	bool valid(QuadListNode<E>* node) {
		return (node && (node != head) && (node != tail));
	}
	QuadListNode<E>* insert(E const& e, QuadListNode<E>* p, QuadListNode<E>* b);
	E remove(QuadListNode<E>* node);
	int clear();
	void traverse();
	
friend std::ostream& operator<<(std::ostream& os, QuadList<E>& dict) {
	QuadListNode<E>* node = dict.first();
	while (node && dict.valid(node)) {
		os << *node;
		node = node->succ;
	}
	return os;
}	
};

template<typename K, typename V>
class SkipList : public Dictionary<K, V> {
protected:	
	
public:	
	int _size;
	int _height; //tower has _height+2 levels
	std::list<QuadList<Entry<K, V>>*> _list;
	SkipList() : Dictionary<K, V>(), _size(0), _height(2) {}
	~SkipList() {}
	int size();
	bool put(K, V);
	bool remove(K k);
	V* get(K k);
	bool empty() {
		return _size <= 0;
	}
	bool skipSearch(QuadListNode<Entry<K, V>>*& node, K k);
	int level(QuadList<Entry<K, V>>* qlist);
	int level(QuadListNode<Entry<K, V>>* node);
	void traverse() {
		for (typename std::list<QuadList<Entry<K, V>>*>::iterator it = _list.begin(); it != _list.end(); it++) {
			QuadListNode<Entry<K, V>>* node;
			std::cout << "------ QuadList LV" << level(*it) << "------" << std::endl;
			node = (*it)->first();
			while (node && (*it)->valid(node)) {
				std::cout << "LV" << level(node);
				std::cout << *node;
				node = node->succ;
			}
			std::cout << "\n--------------------------" << std::endl;
		}	
	}
	void traverseTower() {
		int h = this->_height + 2;
		int len = (*std::next(_list.end(), -1))->size();
		//std::cout << "h:" << h << ", len:" << len << std::endl;
		std::string tower[h][len];
		std::string str;
		char c[32];
		QuadListNode<Entry<K, V>>* node = (*std::next(_list.end(), -1))->first(); //node to the first node of the bottom list
		QuadListNode<Entry<K, V>>* sentry;

		for (int x=0; x<h; x++) {
			for (int y=0; y<len; y++)
				tower[x][y] = "[     ]";
		}
		int i = 0;
		int j;
		while (node != (*std::next(_list.end(), -1))->last()->succ) {
			if (i >= len) {
					std::cout << RED << __func__ << ":Exception case traversing tower i" << WHITE << std::endl;
					break;
			}
			str.clear();
			memset(c, 0, sizeof(c)*sizeof(c[0]));
			sprintf(c, "[%d/%d]", node->entry.key, node->entry.val);
			str.append(c);
			tower[(h-1)][i] = str;
			j = h-1;
			sentry = node;
			while (sentry->above) {
				j--;
				sentry = sentry->above;
				if (j < 0) {
					std::cout << RED << __func__ << ":Exception case traversing tower j" << WHITE << std::endl;
					break;
				}
				str.clear();
				memset(c, 0, sizeof(c)*sizeof(c[0]));
				sprintf(c, "[%d/%d]", sentry->entry.key, sentry->entry.val);
				str.append(c);
				tower[j][i] = str;
			}
			node = node->succ;
			i++;
		}
		int t = (len+2) * 3;
		std::cout << GREEN;
		while (t-- > 0) std::cout << "-";
		std::cout << " TOWER TOP    ";
		t = (len+2) * 3;
		while (t-- > 0) std::cout << "-";
		std::cout << WHITE << std::endl;
		for (int x=0; x<h; x++) {
			for (int y=0; y<len; y++) {
				std::cout << tower[x][y];
				if (y == (len-1)) std::cout << std::endl;
			}
		}
		t = (len+2) * 3;
		std::cout << GREEN;
		while (t-- > 0) std::cout << "-";
		std::cout << " TOWER BOTTOM ";
		t = (len+2) * 3;
		while (t-- > 0) std::cout << "-";
		std::cout << WHITE << std::endl;
	}

friend std::ostream& operator<<(std::ostream& os, SkipList<K, V>& dict) {
	for (typename std::list<QuadList<Entry<K, V>>*>::iterator it = dict._list.begin(); it != dict._list.end(); it++) {
		os << "------ QuadList LV" << dict.level(*it) << "------" << std::endl;
		os << **it;
		os << "\n--------------------------" << std::endl;
	}
	return os;
}
};

template<typename E>
QuadListNode<E>* amo::QuadListNode<E>::insertSuccAbove(E const& e, QuadListNode<E>* b) {
	QuadListNode<E>* node = new QuadListNode<E>(e, this, this->succ, NULL, b);
	if (this->succ) this->succ->pred = node;
	this->succ = node;
	if (b) b->above = node;
	return node;
}

template<typename E>
void amo::QuadList<E>::init() {
	head = new QuadListNode<E>();
	tail = new QuadListNode<E>();
	head->succ = tail;
	head->pred = NULL;
	head->above = NULL;
	head->below = NULL;
	tail->pred = head;
	tail->succ = NULL;
	tail->above = NULL;
	tail->below = NULL;
	_size = 0;
}

template<typename E>
QuadListNode<E>* amo::QuadList<E>::insert(E const& e, QuadListNode<E>* p, QuadListNode<E>* b) {
	_size++;
	return p->insertSuccAbove(e, b);
}

template<typename E>
E amo::QuadList<E>::remove(QuadListNode<E>* node) {
	node->pred->succ = node->succ;
	node->succ->pred = node->pred;
	E e = node->entry;
	delete node;
	_size--;
	return e;
}

template<typename E>
int amo::QuadList<E>::clear() {
	int num = 0;
	while (valid(first())) {
		std::cout << "removed:" << remove(first()) << std::endl;
		num++;
	}
	return num;
}

template<typename K, typename V>
int amo::SkipList<K, V>::level(QuadList<Entry<K, V>>* qlist) {
	typename std::list<QuadList<Entry<K, V>>*>::iterator it;
	int level = -1;
	for (it = _list.begin(); it != _list.end(); it++) {
		if (qlist == *it) {
			level = _list.size() - std::distance(_list.begin(), it);
			return level;
		}
	}
	return level;
}

template<typename K, typename V>
int amo::SkipList<K, V>::level(QuadListNode<Entry<K, V>>* node) {
	typename std::list<QuadList<Entry<K, V>>*>::iterator it;
	int level = -1;
	QuadListNode<Entry<K, V>>* sentry;
	for (it = _list.begin(); it != _list.end(); it++) {
		sentry = (*it)->first()->pred;
		while (sentry != NULL) {
			if (node == sentry) {
				level = _list.size() - std::distance(_list.begin(), it);
				return level;
			}
			sentry = sentry->succ;
		}
	}
	return level;
}

template<typename K, typename V>
V* amo::SkipList<K, V>::get(K k) {
	typename std::list<QuadList<Entry<K, V>>*>::iterator it = _list.begin();
	if (*it) {
		QuadListNode<Entry<K, V>>* node = (*it)->first();
		return skipSearch(node, k) ? &(node->entry.val) : NULL;		
	}
	else {
		std::cout << "list is empty" << std::endl;
		return NULL;
	}
}

template<typename K, typename V>
bool amo::SkipList<K, V>::skipSearch(QuadListNode<Entry<K, V>>*& node, K k) {
	QuadList<Entry<K, V>>* qlist = *_list.begin();
	int level = 0;
	int n = 0;
	std::cout << CYAN << "[" << __func__ << "]: key:" << k << WHITE << std::endl;
	while (true) {
		if (node == NULL) {
			std::cout << RED << __func__ << ":Exception case searching null" << WHITE << std::endl;
			return false;
		}
		else {
			//std::cout << "searches at level " << std::distance(_list.end(), (std::next(_list.begin(), level))) << WHITE << std::endl;
		}
		//searches in quad list
		while (true) {
			n++;
			if (node->succ == NULL || node->entry.key > k) {
				break;
			}
			node = node->succ;
		}
		//checks if found
		node = node->pred;
		if (node->entry.key == k) {
			if (qlist->valid(node)) std::cout << GREEN << "searched " << *node << " after " << n << " times searching "<< WHITE << std::endl;
			else if (node == qlist->head) std::cout << GREEN << "searched head:" << *node << " after " << n << " times searching "<< WHITE << std::endl;
			else if (node == qlist->tail) std::cout << GREEN << "searched tail:" << *node << " after " << n << " times searching "<< WHITE << std::endl;
			else {
				std::cout << RED << __func__ << ":Exception case unknown search" << WHITE << std::endl;
				return false;
			}
			return true;
		}
		//probes to next level of quad list
		level++;
		//checks if beyond
		if (std::next(_list.begin(), level) == _list.end()){
			std::cout << "not searched " << *node << " after " << n << " times searching "<< WHITE << std::endl;
			return false;
		}
		//positions the node which is a sentry
		qlist = *(std::next(_list.begin(), level));
		if (node->below) {
			node = node->below;
		}
		else {
			node = qlist->first();	
		}
		//checks if link lost
		if (node == NULL) {
			std::cout << RED << __func__ << ":Exception case searching lower level:" 
							 << std::distance(_list.end(), (std::next(_list.begin(), level))) << WHITE << std::endl;
			return false;
		}
	}

	return false;
}

template<typename K, typename V>
bool amo::SkipList<K, V>::put(K k, V v) {
	std::cout << CYAN << "[" << __func__ << "]: key:" << k << " and value:" << v << WHITE << std::endl;
	Entry<K, V> e = Entry<K, V>(k, v); //cloned and release
	if (empty()) {
		std::cout << "inserts first quad list into skip list" << std::endl;
		_list.push_back(new QuadList<Entry<K, V>>());
	}
	QuadList<Entry<K, V>>* qlist = *_list.begin();
	QuadListNode<Entry<K, V>>* node = qlist->first(); //searches from the top
	//searches if exists and positions node to the matched or the predecessor
	if (skipSearch(node, k)) { //key exists
		while (node->below) { //inserts after a node which is at the bottom
			node = node->below;
		}
		//std::cout << GREEN << "searched p:" << *node << WHITE << std::endl;		
	}
	//else std::cout << "p:" << *node << std::endl;
	
	//inserts after p which is pointing the same one being pointed by node
	QuadListNode<Entry<K, V>>* p = node;
	QuadListNode<Entry<K, V>>* x = NULL;
	QuadListNode<Entry<K, V>>* b = NULL;
	qlist = *std::next(_list.end(), -1); //inserts at the bottom
	std::cout << "BASE INSERT e:" << e.val << ", p" << *p << ", b:NULL" << " at the LV"<< level(qlist) << " base:\n" << *qlist << std::endl;
	x = qlist->insert(e, p, NULL);
	b = x;
	
	//builds tower from the bottom
	qlist = *std::next(_list.end(), -1);
	int lv = 0; //1 if bottom
	bool flag = true;
	//while ((k+1) % 2 && flag) {
	int dice = (std::rand()+1)%2;
	std::cout << GREEN << "dice:" << dice << WHITE << std::endl;
	//while ((std::rand()%2||std::rand()%2||std::rand()%2)  && flag) {
	//while ((std::rand()%2 ||std::rand()%2)&& flag) {
	while (std::rand()%2 && flag) {
		std::cout << GREEN << "WHILE-LOOP, level of qlist:" << (this->level(qlist))
						   << ", LV" << level(p) << " p:" << *p
						   << ", LV" << level(b) << " b:" << *b << WHITE << std::endl;
		lv++;
		//positions the p which is closest to this inserted node and has a clone at the one level higher
		while (qlist->valid(p) && !(p->above)) {
			p = p->pred;
			std::cout << WHITE << "positioning... ";
			if (p->pred == NULL) {
				std::cout << "LV" << level(p) << " (head) p:" << *p << WHITE << std::endl;
			}
			else if (p->succ == NULL) {
				std::cout << "LV" << level(p) << " (tail) p:" << *p << WHITE << std::endl;
			}
			else {
				std::cout << "LV" << level(p) << " p:" << *p << WHITE << std::endl;
			}
		}
			
		//adds a clone after the p and above this inserted node
		if (!qlist->valid(p)) { //first clone at such level
			if (qlist == *(_list.begin())) {
				std::cout << MAGENTA << "ONE MORE QUAD LIST ABOVE LV" << (this->level(qlist)) << WHITE <<std::endl;
				qlist = *(_list.insert(std::next(_list.end(), -lv), new QuadList<Entry<K, V>>()));
			}
			p = qlist->first()->pred; //p points to the above
			if (p->pred == NULL) {
				std::cout << GREEN << "Positioned LV" << level(p) << " (head) p:" << *p << WHITE << std::endl;
			}
			else if (p->succ == NULL) {
				std::cout << GREEN << "Positioned LV" << level(p) << " (tail) p:" << *p << WHITE << std::endl;
			}
			else {
				std::cout << RED << __func__ << ":Exception case unknown predecessor" << WHITE << std::endl;
				return false;
			}
			flag = false;
		}
		else { //normal clone at such level
			p = p->above; //p points to the above
			std::cout << GREEN << "Positioned LV" << level(p) << " p:" << *p << WHITE << std::endl;
			qlist = *std::next(_list.end(), -(lv+1)); 		
		}
		//inserts
		if (qlist) {
			std::cout << "TOWER INSERT e:" << e.val 
					  << ", at LV" << level(p) << " p" << *p 
					  << ", at LV" << level(b) << " b:" << *b 
					  << "at LV" << level(qlist) << " qlist:\n" << *qlist << WHITE << std::endl;
			b = qlist->insert(e, p, b);
		}
		else {
			std::cout << RED << __func__ << ":Exception case inserting null quad list" << WHITE << std::endl;
			return false;
		}
		std::cout << YELLOW << "AFTER TOWER INSERT [" << k << "/" << v << "], SKIP LIST:\n" << *this << WHITE << std::endl;
		if (lv > _height) flag = false;
	}
	_size++;
	std::cout << CYAN << "AFTER INSERT [" << k << "/" << v << "], SKIP LIST:" << WHITE << std::endl;
	traverse();
	return true;
}









};

#endif
