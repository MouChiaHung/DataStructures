#ifndef _MY_LIST_H_
#define _MY_LIST_H_

#include <list_node.h>

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

template<class T>
class List{
private:
	int _size;
	Node<T>* header;
	Node<T>* trailer;
public:
	List() {
		std::cout << "[List::List()]: this:" << this << WHITE << std::endl;
		init();
	}
	List(amo::List<T> const& list) {
		std::cout << "[List::List(List&)]: this:" << this << " going to assign()" << WHITE << std::endl;
		assign(list.first(), list.size());
	}
	List(amo::List<T> const& list, int rank, int n) {
		std::cout << "[List::List(List&,int,int)]: this:" << this << " going to assign()" << WHITE << std::endl;
		Node<T>* node = list.first();
		int i = rank;
		while (0<i--) {
			node = node->succ;
			std::cout << "[List::List(List&,int,int)]: node:" << node->data << " at " << node << WHITE << std::endl;
		}
		std::cout << "[List::List(List&,int,int)]: going to assign() from node:" << node << " for " << n << " nodes" << WHITE << std::endl;
		assign(node, n);
	}
	
	~List() {
		std::cout << "[List::~List()]: this:" << this << WHITE << std::endl;
		//for (int i=0;i<size();i++) cout << "[List::~List()]: going to destruct list[" << i <<"]:" << (*this)[i] << " at " << first()->next(i) << WHITE << endl;
		clear();
		delete header;
		delete trailer;
	}
	T& operator[] (int rank);
	int size() const { return _size; }
	bool empty() const { return _size <= 0; }
	bool valid(Node<T>* node) { return (node) && (node!=header) && (node!=trailer);}
	Node<T>* first() const { return header->succ; }
	Node<T>* last() const { return trailer->pred; }
	void init();
	void assign(Node<T>* node, int n);
	int indexOf(Node<T>* e);
	Node<T>* find(T const& t, int n, Node<T>& node);
	Node<T>* search(T const& t, int n, Node<T>& boundary);
	Node<T>* insertFirst(T const& t);
	Node<T>* insertLast(T const& t);
	Node<T>* insertAfter(T const& t, Node<T>& node);
	Node<T>* insertBefore(T const& t, Node<T>& node);
	Node<T>* remove(int rank);
	int deduplicate();
	int unique();
	int clear();
	typedef struct functor_traverse {
		void operator() (Node<T>* n) {
			std::cout << "[List::functor_traverse(Node<T>*)]: node:" << n->data << " at " << n << WHITE << std::endl;
		}
	} VST;
	
	typedef struct functor_traverse_index {
		void operator() (Node<T>* n, Node<T>* trailer, int size) {
			int index = size;
			Node<T>* node = trailer;
			while (0<index--) {
				node = node->pred;
				if (node == n) 	break;
			}
		std::cout << "[List::functor_traverse(Node<T>*)]: node:" << n->data << " at " << n << " and index:" << index << WHITE << std::endl;
		}
	} VST_INDEX;
	void traverse(VST& functor);
	void traverse(VST_INDEX& functor);
	void insertionSort();
	void selectionSort();
	void mergeSort();
	void mergeSort(Node<T>* node, int n);
	void merge(Node<T>** sorted_left, int nl, List<T>* list, Node<T>** sorted_right, int nr);
};

template<class T>
T& amo::List<T>::operator[] (int rank) {
	Node<T>* node = first();
	while(0<rank--) node = node->succ;
	return node->data;
}

template<class T>
void amo::List<T>::init() {
	header = new Node<T>();
	trailer = new Node<T>();
	_size = 0;
	header->succ = trailer;
	header->pred = NULL;
	trailer->pred = header;
	trailer->succ = NULL;
	std::cout << "[List::init()]: this:" << this
		      << "\n                header :" << header
		      << "\n                trailer:" << trailer
		      << "\n                first():" << first()
	          << "\n                last() :" << last() << WHITE << std::endl;
}

template<class T>
void amo::List<T>::assign(Node<T>* node, int n) {
	init();
	while (0<n--) {
		if (node->succ == NULL) { 
			std::cout << "[List::assign(Node<T>*,int)]: met trailer and breaks from loop:" << n << WHITE << std::endl;
			break;
		}
		std::cout << "[List::assign(Node<T>*,int)]: going to insert new node:" << node->data << " at " << node << WHITE << std::endl;
		insertLast(node->data);
		node = node->succ;
	}
}

template<class T>
int amo::List<T>::indexOf(Node<T>* e) {
	Node<T>* node = trailer;
	int n = size();
	while (0<n--) {
		node = node->pred;
		if (node == e) {
			//std::cout << "[List::indexOf(Node*)]: node(" << node << "):" << node->data << " has index:" << n << WHITE << std::endl;
			return n;
		} 
		//else std::cout << "[List::indexOf(Node*)]: not node(" << node << "):" << node->data << " and n:" << n << WHITE << std::endl;
	}
	std::cout << RED << "[List::indexOf(Node*)]: err returns:" << -1 << WHITE << std::endl;
	return -1;
}

/**
 * finds the elements in [(index_of_node-(n-1)), index_of_node] if any one matches first met from the tail.
 */
template<class T>
Node<T>* amo::List<T>::find(T const& t, int n, Node<T>& node) {
	Node<T>* p = node.succ;
	while (0<n--) {
		if (p->pred->pred == NULL) {
			std::cout << RED <<  "[List::find(T&,int,Node&)]: met header and returns NULL" << WHITE << std::endl;
			return NULL;
		}
		if (t == (p=p->pred)->data) { 
			std::cout << CYAN << "[List::find(T&,int,Node&)]: found and returns node:" << p << WHITE << std::endl;
			return p;
		} else std::cout << "[List::find(T&,int,Node&)]: not node:" << p << " and data:" << p->data << WHITE << std::endl;
	}
	std::cout << RED <<  "[List::find(T&,int,Node&)]: found nothing and returns NULL" << WHITE << std::endl;
	return NULL;
}

template<class T>
Node<T>* amo::List<T>::search(T const& t, int n, Node<T>& boundary) {
	Node<T>* node = &boundary; 
	while (0<=n--) {
		node = node->pred;
		if (node == header) {
			std::cout << CYAN << "[List::search(T&,int,Node&)]: met header and returns node:" << node << " which is the header:" << header << WHITE << std::endl;			
			return node;
		}
		if (node->data <= t) {
			std::cout << CYAN << "[List::search(T&,int,Node&)]: searched and returns node:" << node->data << " at " << node << WHITE << std::endl;			
			return node;
		}
	}
	std::cout << CYAN << "[List::search(T&,int,Node&)]: not searched and returns node:" << node << " which is the header:" << header << WHITE << std::endl;			
	return node;
}

template<class T>
Node<T>* amo::List<T>::insertAfter(T const& t, Node<T>& node) {
	_size++;
	Node<T>* inserted = node.insertSucc(t);
	std::cout << "[List::insertAfter(T&, Node&)]: returns new node at " << inserted << WHITE << std::endl;
	return inserted;
}

template<class T>
Node<T>* amo::List<T>::insertBefore(T const& t, Node<T>& node) {
	_size++;
	Node<T>* inserted = node.insertPred(t);
	std::cout << "[List::insertAfter(T&, Node&)]: returns new node at " << inserted << WHITE << std::endl;
	return inserted;
}

template<class T>
Node<T>* amo::List<T>::insertFirst(T const& t) {
	_size++;
	Node<T> *inserted = header->insertSucc(t);
	std::cout << "[List::insertFirst(T&)]: returns new node at " << inserted << WHITE << std::endl;
	return inserted;
}

template<class T>
Node<T>* amo::List<T>::insertLast(T const& t) {
	_size++;
	Node<T>* inserted = trailer->insertPred(t);
	std::cout << "[List::insertLast(T&)]: returns new node at " << inserted << WHITE << std::endl;
	return inserted;
}

template<class T>
Node<T>* amo::List<T>::remove(int rank) {
	Node<T>* node = first()->next(rank);
	node->pred->succ = node->succ;
	node->succ->pred = node->pred;
	_size -= 1;
	std::cout << "[List::remove(int)]: returns removed node:" << node->data << " at " << node << WHITE << std::endl;
	return node;
}

template<class T>
int amo::List<T>::clear() {
	int removed = size();
	while(0<size()) 
		delete remove(0);
	std::cout << "[List::clear()]: returns remove count:" << removed << WHITE << std::endl;
	return removed;
}

template<class T>
int amo::List<T>::deduplicate() {
	if (size()<2) return 0;
	int old_size = size();
	Node<T>* node = first();
	Node<T>* denode;
 	while (trailer != node) {
		std::cout << YELLOW << "[List::deduplicate()]: while-loop node:" << node->data << " at " << node << WHITE << std::endl;
		while (denode = find(node->data, indexOf(node->pred)+1, *node->pred)) {
			if (denode != NULL) {
				std::cout << RED << "[List::deduplicate()]: found a duplicate:" << denode << " and going to remove it" << WHITE << std::endl;
				delete remove(indexOf(denode));
			} else {
				std::cout << "[List::deduplicate()]: no duplicate:" << node->data << " at " << node << WHITE << std::endl;
				break;
			}
		}
		node = node->succ;
	}
	VST vst;
	traverse(vst);
	return old_size - size();
}

template<class T>
int amo::List<T>::unique() {
	if (size()<2) return 0;
	int old_size = size();
	Node<T>* node;
	Node<T>* next;
	for (node=first(), next=node->succ;trailer!=next;node=next, next=next->succ) {
		std::cout << YELLOW << "[List::unique()]: while-loop node:" << node->data << " at " << node << WHITE << std::endl;
		if (node->data == next->data) {
			std::cout << RED << "[List::unique()]: going to remove a node holding same data:" << node << " and going to remove it" << WHITE << std::endl;
			delete remove(indexOf(node));
		} else {
			
		}
	}
	VST vst;
	traverse(vst);
	return old_size - size();
}

template<class T>
void amo::List<T>::traverse(VST& functor) {
	for (Node<T>* node=first(); node!=trailer; node=node->succ) functor(node);
}

template<class T>
void amo::List<T>::traverse(VST_INDEX& functor) {
	for (Node<T>* node=first(); node!=trailer; node=node->succ) functor(node, trailer, size());
}

template<class T>
void amo::List<T>::insertionSort() {
	if (size()<=1) return;
	Node<T>* node;
	Node<T>* p;
	Node<T>* insert;
	for (node=first(); node!=trailer; node=node->succ) {
		std::cout << YELLOW << "[List::insertionSort()]: for-loop node:" << node->data << " at " <<  node << " and index:" << indexOf(node) << WHITE << std::endl;
		p = search(node->data, indexOf(node), *node);
		if (valid(p)) {
			if (indexOf(p) == indexOf(node)-1) {
				//std::cout << YELLOW << "[List::insertionSort()]: do nothing if iterated node is nearby the first less one" << WHITE << std::endl;
				continue;
			}
			std::cout << YELLOW << "[List::insertionSort()]: going to sort after the node:" << p->data << " at " <<  p << " to index:" << indexOf(p) << WHITE << std::endl;
			insert = insertAfter(node->data, *p);
			//std::cout << YELLOW << "[List::insertionSort()]: after sort the new inserted:" << insert->data << " at " <<  insert << " and index:" << indexOf(insert) << WHITE << std::endl;
			//std::cout << YELLOW << "[List::insertionSort()]: going to remove the old redundant node:" << node->data << " at " <<  node << " and index:" << indexOf(node) << WHITE << std::endl;
			delete remove(indexOf(node));
			node = insert;
		} else {
			
		}
	}
	VST vst;
	traverse(vst);
}

template<class T>
void amo::List<T>::selectionSort() {
	if (size()<=1) return;
	Node<T>* node;
	Node<T>* min;
	int n = size();
	while (0<n--) {
		min = first();
		for (node=first()->next(n); node!=header; node=node->pred) {
			if ((min->data) > (node->data)) {
				min = node;
			}
		}
		insertLast(min->data);
		delete remove(indexOf(min));
	}
	std::cout << YELLOW << "[List::selectionSort()]: after sort:" << WHITE << std::endl;
	VST vst;
	traverse(vst);
}

template<class T>
void amo::List<T>::mergeSort() {
	std::cout << YELLOW << "[List::mergeSort()]: before sort:" << WHITE << std::endl;
	VST_INDEX vst;
	traverse(vst);
	mergeSort(first(), size());
	std::cout << YELLOW << "[List::mergeSort()]: after sort:" << WHITE << std::endl;
	traverse(vst);
}

template<class T>
void amo::List<T>::mergeSort(Node<T>* node, int n) {
	if (n<2) {
		std::cout << YELLOW << "[List::mergeSort(Node<T>*,int)]: single node:" << node->data << " at " << node << " and n:" << n << " and return" << WHITE << std::endl;
		return;
	}
	int m = n >> 1;
	Node<T>* befor_the_begin = node->pred;
	Node<T>* left = node;
	Node<T>* right = node->next(m);
	std::cout << YELLOW << "[List::mergeSort(Node<T>*,int)]: node:" << node->data << " at " << node << " and n:" << n
			  << ", left:" << left->data << " at " << left << " and index:" << indexOf(left)
			  << ", right:" << right->data << " at " << right << " and index:" << indexOf(right) << WHITE << std::endl;
	mergeSort(left, m);
	mergeSort(right, n-m);
	left = befor_the_begin->succ;
	right = left->next(m);
	merge(&left, m, this, &right, n-m);
	std::cout << YELLOW << "[List::mergeSort(Node<T>*,int)]: after merge for [" 
	          << indexOf(left) << "," << indexOf(left->next(m-1)) << "]" << " and [" << indexOf(right) << "," << indexOf(right->next(n-m-1)) << "]" 
			  << ", left:" << left->data << " at " << left << " and index:" << indexOf(left)
			  << ", right:" << right->data << " at " << right << " and index:" << indexOf(right) << WHITE << std::endl;
	
}

template<class T>
void amo::List<T>::merge(Node<T>** sorted_left, int nl, List<T>* list, Node<T>** sorted_right, int nr) {
	int index_left=0, index_right=0;
	Node<T>* left = *sorted_left;
	Node<T>* right = *sorted_right;
	Node<T>* befor_the_begin = left->pred;
	Node<T>* tmp;
	Node<T>* insert;
	std::cout << CYAN << "[List::merge()]: left:" << left->data << " at " << left << " and nl:" << nl
					  << ", right:" << right->data << " at " << right << " and nr:" << nr << WHITE << std::endl;
	while (index_left < nl && index_right < nr) {
		if (right->data < left->data) {
			tmp = right;
			insert = list->insertBefore(right->data, *left);
			right = tmp->succ;
			std::cout << CYAN << "[List::merge()]: inserted a new node:" << insert->data << " at " << insert
					          << " and going to remove the old node:" << tmp->data << " at " << tmp << WHITE << std::endl;
			delete list->remove(indexOf(tmp));
			index_right++;
		} else {
			left = left->succ;
			index_left++;
		}
	}
	*sorted_left = befor_the_begin->succ;
	*sorted_right = befor_the_begin->succ->next(nl);
	std::cout << CYAN << "[List::merge()]: after merge:" << WHITE << std::endl;
	VST_INDEX vst;
	traverse(vst);
}

















}
#endif