#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <stack.h>
#include <map>
#include <typeinfo> 
#include <climits>

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

#define ERROR_CODE -1

typedef enum {UNDISCOVERED, DISCOVERED, VISITED} VStatus;
typedef enum {UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD} EType;


template<typename Tv>
class Vertex {
typedef struct functor_traverse {
	void operator() (Vertex<Tv> const& v) {
		std::cout << v << WHITE << std::endl;
	}
} FUNCTOR_TRAVERSER;
private:

public:
	Tv data;
	int inDegree;
	int outDegree;
	VStatus status;
	int dTime;
	int fTime;
	int parent;
	int priority;
	Vertex(const Tv& d = (Tv) 0) : data(d), inDegree(0), outDegree(0), status(UNDISCOVERED), dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {
		std::cout << "[Vertex::Vertex()]: this:" << this << ", Tv type:" << typeid(Tv).name() << WHITE << std::endl;
	}
	Vertex(const Vertex& v) : data(v.data), inDegree(v.inDegree), outDegree(v.outDegree), status(v.status), dTime(v.dTime), fTime(v.fTime), parent(v.parent), priority(v.priority) {
		std::cout << "[Vertex::Vertex(Vertex&)]: this:" << this << ", Tv type:" << typeid(Tv).name() << WHITE << std::endl;
	}
	Vertex& operator=(const Vertex& vertex) {
		std::cout << "[Vertex::operator=()]: data:" << vertex.data << WHITE << std::endl;
		data = vertex.data;
		inDegree = vertex.inDegree;
		outDegree = vertex.outDegree;
		status = vertex.status;
		dTime = vertex.dTime;
		fTime = vertex.fTime;
		parent = vertex.parent;
		priority = vertex.priority;
		return *this;
	}
	~Vertex() {
		std::cout << "[Vertex::~Vertex()]: this:" << this << WHITE << std::endl;
	}
	
friend std::ostream& operator<<(std::ostream& os, const Vertex& vertex) {
	if (&vertex == NULL) {
		os << RED << "no vertex instance";
		return os;
	}
	os << WHITE << "[this]     :" << &vertex << endl;
	os << WHITE << "[data]     :" << vertex.data << endl;
	os << WHITE << "[inDegree] :" << vertex.inDegree << endl;
	os << WHITE << "[outDegree]:" << vertex.outDegree << endl;
	switch (vertex.status) {
		case UNDISCOVERED:
			os << WHITE << "[status]   :" << "UNDISCOVERED" << endl;
			break;
		case DISCOVERED:
			os << WHITE << "[status]   :" << "DISCOVERED" << endl;
			break;
		case VISITED:
			os << WHITE << "[status]   :" << "VISITED" << endl;
			break;	
	}
	os << WHITE << "[dTime]    :" << vertex.dTime << endl;
	os << WHITE << "[fTime]    :" << vertex.fTime << endl;
	os << WHITE << "[parent]   :" << vertex.parent << endl;
	os << WHITE << "[priority] :" << vertex.priority << endl;
	return os;
}		
};

template<typename Te>
class Edge {
private:	

public:	
	EType type;
	Te data;
	int weight;
	Edge(const Te& d = (Te) 0, int w = 0) : data(d), weight(w), type(UNDETERMINED) {
		std::cout << "[Vertex::Vertex()]: this:" << this << ", Te type:" << typeid(Te).name() << WHITE << std::endl;
	}
	~Edge() {
		std::cout << "[Edge::~Edge()]: this:" << this << WHITE << std::endl;
	}
friend std::ostream& operator<<(std::ostream& os, const Edge& edge) {
	if (&edge == NULL) {
		os << BLUE << "null" << endl;
		return os;
	}
	os << WHITE << "[this]  :" << &edge << endl;
	os << WHITE << "[data]  :" << edge.data << endl;
	os << WHITE << "[weight]:" << edge.weight << endl;
	switch (edge.type) {
		case UNDETERMINED:
			os << WHITE << "[type]  :" << "UNDETERMINED" << endl;
			break;
		case TREE:
			os << WHITE << "[type]  :" << "TREE" << endl;
			break;
		case CROSS:
			os << WHITE << "[type]  :" << "CROSS" << endl;
			break;	
		case FORWARD:
			os << WHITE << "[type]  :" << "FORWARD" << endl;
			break;	
		case BACKWARD:
			os << WHITE << "[type]  :" << "BACKWARD" << endl;
			break;		
	}
	
	return os;
}		
};

template<typename Tv, typename Te> 
class Graph { 
typedef struct functor_traverse {
	void operator() (Graph<Tv,Te> const& tree) {
		std::cout << tree << WHITE << std::endl;
	}
} FUNCTOR_TRAVERSER;
private:
	
public:
	int n;
	int e;
	Graph(): n(0), e(0) {
		std::cout << "[Graph::Graph()]: this:" << this << ", Tv type:" << typeid(Tv).name() << ", Te type:" << typeid(Te).name() << WHITE << std::endl;
	}
	~Graph() {
		std::cout << "[Graph::~Graph()]: this:" << this << WHITE << std::endl;
	}
	void reset() {
		for (int i=0; i<n; i++) {
			status(i) = UNDISCOVERED;
			dTime(i) = -1;
			fTime(i) = -1;
			parent(i) = -1;
			priority(i) = INT_MAX;
			for (int j=0; j<n; j++) {
				if (exist(i, j)) {
					type(i, j) = UNDETERMINED;
				}
			}
		}
	}
#if 0 //to be an abstract class
	//vertex
	virtual int insert(const Tv& data) = 0;
	virtual Tv remove(int i) = 0;
	virtual Tv& vertex(int i) = 0;
	virtual int inDegree(int i) = 0;
	virtual int outDegree(int i) = 0;
	virtual int firstNbr(int i) = 0;
	virtual int nextNbr(int i, int j) = 0;
	virtual VStatus& status(int i) = 0;
	virtual int& dTime(int i) = 0;
	virtual int& fTime(int i) = 0;
	virtual int& parent(int i) = 0;
	virtual int& priority(int i) = 0;
	//edge
	virtual bool exist(int i, int j) = 0;
	virtual void insert(const Te& e, int i, int j, int weight) = 0;
	virtual Te remove(int i, int j) = 0;
	virtual EType& type(int i, int j) = 0;
	virtual Te& edge(int i, int j) = 0;
	virtual int& weight(int i, int j) = 0;
#else 	
	//vertex
	int insert(const Tv& d);
	Tv remove(int i);
	Tv& vertex(int i);
	int inDegree(int i);
	int outDegree(int i);
	int firstNbr(int i);
	int nextNbr(int i, int j);
	VStatus& status(int i);
	int& dTime(int i);
	int& fTime(int i);
	int& parent(int i);
	int& priority(int i);
	//edge
	bool exist(int i, int j);
	void insert(const Te& d, int i, int j, int weight);
	Te remove(int i, int j);
	Te& edge(int i, int j);
	EType& type(int i, int j);
	int& weight(int i, int j);
#endif
	
friend std::ostream& operator<<(std::ostream& os, const Graph<Tv,Te>& graph) {
	os  << WHITE << "[this]:" << &graph << endl;
	return os;
}
};

template<typename Tv, typename Te>
class AdjaMatrix : public Graph<Tv, Te> {
private:

public:
	//Unhide members of base class template with a using declaration
	//using amo::Graph<Tv, Te>::insert;
	std::vector<Vertex<Tv>*> V;
	std::vector<std::vector<Edge<Te>*>> E;
	AdjaMatrix(): Graph<Tv, Te>() {
		std::cout << "[AdjaMatrix::AdjaMatrix()]: this:" << this << ", Tv type:" << typeid(Tv).name() << ", Te type:" << typeid(Te).name() << WHITE << std::endl;
	}
	~AdjaMatrix() {
		std::cout << "[AdjaMatrix::~AdjaMatrix()]: this:" << this << WHITE << std::endl;
	}
	/**
	 * overload for V
	 */
	int inDegree(int i) { return V[i]->inDegree; }
	int outDegree(int i) { return V[i]->outDegree; }
#if 0 //from tail	
	int firstNbr(int i) { return nextNbr(i, this->n-1); }
	int nextNbr(int i, int j) { //next of [0, j)
		while (--j >= 0) {
			if (exist(i, j)) break;
		}
		if (j >= 0) cout << i << " -> " << j << WHITE << endl;
		return j;
	}
#else //from head
	int firstNbr(int i) { return nextNbr(i, 0); }
	int nextNbr(int i, int j) { //next of (j, n)
		while (++j < this->n) {
			if (exist(i, j)) break;
		}
		if (j < this->n) cout << i << " -> " << j << WHITE << endl;
		return j;
	}
#endif	
	VStatus& status(int i) { return V[i]->status; }
	Tv& vertex(int i) { return V[i]->data; }
	int& dTime(int i) { return V[i]->dTime; }
	int& fTime(int i) { return V[i]->fTime; }
	int& parent(int i) { return V[i]->parent; }
	int& priority(int i) { return V[i]->priority; }
	int insert(const Tv& d);
	Tv remove(int i); //[0, n)
	/**
	 * overload for E
	 */
	Te& edge(int i, int j);
	EType& type(int i, int j);
	int& weight(int i, int j);
	void insert(const Te& d, int i, int j, int weight); //[0, e)
	Te remove(int i, int j);
	bool exist(int i, int j);
	/**
	 * extend
	 */
	void print(std::ostream& os);
	/**
	 * algorithm
	 */
	void BFS(int v);
	void DFS(int v);
	void DFS(int v, int& time, int*& distance, int*& predecessor, int*& discover, int*& finish);

friend std::ostream& operator<<(std::ostream& os, AdjaMatrix<Tv,Te>& matrix) {
	matrix.print(os);
	return os;
}	
};

template<typename Tv, typename Te>
void amo::AdjaMatrix<Tv, Te>::print(std::ostream& os) {
	typename std::vector<Vertex<Tv>*>::iterator itV; //points to V[i]
	typename std::vector<std::vector<Edge<Te>*>>::iterator itE; //points to E
	typename std::vector<Edge<Te>*>::iterator it_adjs; //points to E[i]
	int n_check = 0;
	int e_check = 0;
	os << CYAN << "[AdjaMatrix::print()]: size of V:" << V.size() << WHITE << std::endl;
	os << CYAN << "[AdjaMatrix::print()]: size of E:" << E.size() << WHITE << std::endl;
	for (itE=E.begin(); itE!=E.end(); itE++) {
		os << CYAN << "[AdjaMatrix::print()]: size of E["<< distance(E.begin(), itE) << "]:" << itE->size() << WHITE << std::endl;
	}
	os << GREEN << "--- VERTEX TOP ------" << WHITE << std::endl;
	for (itV=V.begin(); itV!=V.end(); itV++) {
		os << CYAN << "V[" << distance(V.begin(), itV) << "]"  << WHITE << endl;
		os << **itV; //prints vertex 
		n_check++;
	}
	os << GREEN << "--- VERTEX BOTTOM ------" << WHITE << std::endl;
	os << GREEN << "--- EDGE TOP ------" << WHITE << std::endl;
	for (itE=E.begin(); itE!=E.end(); itE++) {
		for (it_adjs=itE->begin(); it_adjs!=itE->end(); it_adjs++) {
			os << CYAN << "E[" << distance(E.begin(), itE) << "][" << distance(itE->begin(), it_adjs) << "]" << WHITE << endl;
			os << **it_adjs;
			if (*it_adjs != NULL) e_check++;
		}
	}
	if (this->n == n_check) os << GREEN << "right n:" << this->n << WHITE << endl;
	else os << RED << "wrong n:" << this->n << " and n_check:" << n_check << WHITE << endl;
	if (this->e == e_check) os << GREEN << "right e:" << this->e << WHITE << endl;
	else os << RED << "wrong e:" << this->e << " and e_check:" << e_check << WHITE << endl;
	os << GREEN << "--- EDGE BOTTOM ------" << WHITE << std::endl;
	
	os << GREEN << "--- GRAPH TOP ------" << WHITE << std::endl;
	string bars, nbrs;
	//char c[2];
	string c;
	for (int i=0; i<this->n; i++) {
		os << CYAN << "-------" << WHITE << endl;
		//os << CYAN << "[" << i << "]" << WHITE << endl;
		os << CYAN << "[" << V[i]->data << "]" << WHITE << endl;
		bars.clear();
		nbrs.clear();
		for (int j=0; j<this->n; j++) {
			if (exist(i, j)) {
				bars.insert(bars.length(), " | ");
				nbrs.append("[");
				//sprintf(c, "%d", j);
				//nbrs.append(c);
				c.insert(c.begin(), V[j]->data);
				nbrs.append(c);
				c.clear();
				nbrs.append("]");
			}
		}
		os << CYAN << bars << WHITE << endl;
		os << CYAN << nbrs << WHITE << endl;
	}
	os << GREEN << "--- GRAPH BOTTOM ------" << WHITE << std::endl;
}

//For V
/**
 * When a class template derives from a base class template, the base members are not visible in the derived class template definition.
 * (This makes sense, until you specialize, there is no class, and so there are no members. 
 * Explicit specializations can always change the meaning of any given template class.)
 */
template<typename Tv, typename Te>
int amo::AdjaMatrix<Tv, Te>::insert(const Tv& data) {
	std::cout << YELLOW << "[AdjaMatrix::insert()]: data:" << data << WHITE << std::endl;
	Vertex<Tv>* vertex = new Vertex<Tv>(data);
	typename std::vector<Vertex<Tv>*>::iterator itV;
	typename std::vector<std::vector<Edge<Te>*>>::iterator itE;
	typename std::vector<Edge<Te>*>::iterator it_adjs;
	
	int tmp = this->n;
	std::vector<Edge<Te>*>* adjs = new std::vector<Edge<Te>*>();
	while (0<tmp--) { 
		adjs->push_back((Edge<Te>*)0); 
	}
	itE = this->E.insert(E.end(), *adjs);	
	std::cout << YELLOW << "[AdjaMatrix::insert()]: inserted an vector at E[" << distance(E.begin(), itE) << "]" << WHITE << std::endl;
	for (itE=E.begin(); itE!=E.end(); itE++) {
		it_adjs = itE->insert(itE->end(), (Edge<Te>*)0);
		std::cout << YELLOW << "[AdjaMatrix::insert()]: inserted an dummy at E[" <<  distance(this->E.begin(), itE)
				  << "][" << distance(itE->begin(), it_adjs) << "]" 
					<< " and size of E[" << distance(E.begin(), itE) << "]:" << itE->size() << WHITE << std::endl;		  
	}
	
	itV = this->V.insert(V.end(), vertex);
	(this->n)++;
	std::cout << YELLOW << "[AdjaMatrix::insert()]: n:" << this->n << WHITE << std::endl;
	return distance(V.begin(), itV);
}

template<typename Tv, typename Te> //This implement deploys operator[] instead of iterators but now n matters 
Tv amo::AdjaMatrix<Tv, Te>::remove(int i) { 
	for (int j=0; j<this->n; j++) { //i->j
		if (exist(i, j)) {
			delete this->E[i][j]; //delete the instance of edge pointed by E[i][j]
			this->E[i][j] = NULL;
			this->V[j]->inDegree--;
			this->e--;
		}
	}
	this->E.erase(std::next(this->E.begin(), i)); //delete instance of vector of E[i], which decreases size of E by 1
	this->n--;
	for (int j=0; j<this->n; j++) { //j->i
		if (exist(j, i)) {
			delete this->E[j][i]; //delete instance of edge pointed by E[j][i]
			this->E[j][i] = NULL;
			this->V[j]->outDegree--;
			this->e--;
		}
		this->E[j].erase(std::next(this->E[j].begin(), i));
	}
	Tv data = this->V[i]->data;
	this->V.erase(std::next(this->V.begin(), i));
	return data;
}

//For E
template<typename Tv, typename Te>
void amo::AdjaMatrix<Tv, Te>::insert(const Te& d, int i, int j, int weight) { //there should have been a space prepared since inserting a vertex before
	if (exist(i, j)) {
		cout << RED << "edge between " << i << " and " << j << " already exists" << WHITE << std::endl;
		return;
	}
	Edge<Te>* edge = new Edge<Te>(d, weight);
	E[i][j] = edge;
	this->e++;
	V[i]->outDegree++;
	V[j]->inDegree++;
	cout << CYAN << "inserted edge:" << this->E[i][j] << WHITE << std::endl;
}

template<typename Tv, typename Te>
Te amo::AdjaMatrix<Tv, Te>::remove(int i, int j) { //keeps the space of but replaces E[i][j] with NULL 
	if (!exist(i, j)) {
		cout << RED << "edge between " << i << " and " << j << " doesn't exist" << WHITE << std::endl;
		return NULL;
	}
#if 1	
	typename std::vector<std::vector<Edge<Te>*>>::iterator itE;
	typename std::vector<Edge<Te>*>::iterator it_adjs;
	itE = std::next(this->E.begin(), i);
	it_adjs = std::next(itE->begin(), j);
		
	Te data = (*it_adjs)->data;
	cout << CYAN << "going to delete an edge form E and replace with NULL:" << data << WHITE << std::endl;
	delete *it_adjs;
	*it_adjs = NULL;
#else	
	Te data = E[i][j]->data;
	cout << CYAN << "going to delete an edge form E and replace with NULL:" << data << WHITE << std::endl;
	delete E[i][j];
	E[i][j] = NULL;
#endif	
	this->e--;
	V[i]->outDegree--;
	V[j]->inDegree--;
	return data;
}

template<typename Tv, typename Te>
bool amo::AdjaMatrix<Tv, Te>::exist(int i, int j) {
	bool ret = true;
	ret &= (0<=i);
	//'this' is always implicitly dependent in a template and the lookup is therefore deferred until the template is actually instantiated.
	if (!ret) { 
		//cout << RED << "out of limit, i < 0" << WHITE << std::endl;
		return ret;
	}
	ret &= i<this->n;
	if (!ret) {
		//cout << RED << "out of limit, i >= " << this->n << WHITE << std::endl;
		return ret;
	}
	ret &= (0<=j);
	if (!ret) {
		//cout << RED << "out of limit, j < 0" << WHITE << std::endl;
		return ret;
	}
	ret &= (j<this->n);
	if (!ret) {
		//cout << RED << "out of limit, j >= " << this->n << WHITE << std::endl;
		return ret;
	}
	ret &= (this->E[i][j] != NULL);
	if (!ret) {
		//cout << RED << "E[" << i << "][" << j << "] is NULL" << WHITE << std::endl;
		return ret;
	}
	return ret;
}

template<typename Tv, typename Te>
EType& amo::AdjaMatrix<Tv, Te>::type(int i, int j) {
	if (!exist(i, j)){
		cout << RED << "no edge exists and return UNDETERMINED" << WHITE << std::endl;
		Edge<Te>* edge = E[i][j];
		edge->type = UNDETERMINED;
		return edge->type;
	}
	Edge<Te>* edge = E[i][j];
	return edge->type;
}

template<typename Tv, typename Te>
Te& amo::AdjaMatrix<Tv, Te>::edge(int i, int j) {
	if (!exist(i, j)){
		cout << RED << "no edge exists and return NULL" << WHITE << std::endl;
		Te* dummy = new Te();
		return *dummy;
	}
	Edge<Te>* edge = E[i][j];
	return edge->data;
}

template<typename Tv, typename Te>
int& amo::AdjaMatrix<Tv, Te>::weight(int i, int j) {
	if (!exist(i, j)){
		cout << RED << "no edge exists and return NULL" << WHITE << std::endl;
		return ERROR_CODE;
	}
	Edge<Te>* edge = E[i][j];
	return edge->weight;
}

template<typename Tv, typename Te>
void amo::AdjaMatrix<Tv, Te>::BFS(int v) {
#if 1 //info
	string str;
	char c[2]; //for a char and a null-terminated character
#endif
	int distance[this->n];
	int predecessor[this->n];
	std::queue<int> queue;
	queue.push(v);
	distance[v] = 0;
	predecessor[v] = -1;
	while (!queue.empty()) {
		int i = queue.front();
		queue.pop();
#if 0 //from tail		
		for (int u=firstNbr(i); u>=0; u=nextNbr(i, u)) {
#else //from head			
		for (int u=firstNbr(i); u<this->n; u=nextNbr(i, u)) {
#endif			
#if 1 //info	
			str.clear();	
			c[0] = vertex(i);
			str.append(c, 1);
			str.append(" - ");
			c[0] = vertex(u);
			str.append(c, 1);
			cout << YELLOW << str << WHITE << endl;
#endif		
			if (status(u) == UNDISCOVERED) {
				queue.push(u);
				status(u) = DISCOVERED;
				type(i, u) = TREE;
				parent(u) = i;
				distance[u] = distance[i]+1;
				predecessor[u] = i;
			} else {
				type(i, u) = CROSS;
			}
		}
		status(i) = VISITED;
	}
	for (int i=0; i<this->n; i++) {
		cout << YELLOW << "distance[" << vertex(i) << "]:" << distance[i] << WHITE << endl;
	}
	for (int i=0; i<this->n; i++) {
		int p = predecessor[i];
		if (p >= 0) cout << YELLOW << "predecessor[" << vertex(i) << "]:" << vertex(p) << WHITE << endl;
		else cout << YELLOW << "predecessor[" << vertex(i) << "]:NULL(root)" << WHITE << endl;
	}
}

template<typename Tv, typename Te>
void amo::AdjaMatrix<Tv, Te>::DFS(int v) {
	int root = v;
	int time = 0;
	int* distance = new int[this->n];
	int* predecessor = new int[this->n] {-1,-1,-1,-1,-1,-1,-1,-1};
	int* discover = new int[this->n]; //all of dTime of V
	int* finish = new int[this->n]; //all of fTime of V
	do {
		if (status(v) == UNDISCOVERED) {
			cout << YELLOW << "going to DFS of sub-graph of v:" << v << WHITE << endl;
			DFS(v, time, distance, predecessor, discover, finish);
		}
	} while (root!=(v=(++v%this->n)));
	for (int i=0; i<this->n; i++) {
		int p = predecessor[i];
		if (p >= 0) cout << YELLOW << "predecessor[" << vertex(i) << "]:" << vertex(p) << WHITE << endl;
		else cout << YELLOW << "predecessor[" << vertex(i) << "]:NULL" << WHITE << endl;
	}
	for (int i=0; i<this->n; i++) {
		cout << YELLOW << "discover[" << vertex(i) << "]:" << discover[i] << WHITE << endl;
	}
	for (int i=0; i<this->n; i++) {
		cout << YELLOW << "finish[" << vertex(i) << "]:" << finish[i] << WHITE << endl;
	}
}

template<typename Tv, typename Te>
void amo::AdjaMatrix<Tv, Te>::DFS(int v, int& time, int*& distance, int*& predecessor, int*& discover, int*& finish) {
	status(v) = DISCOVERED;
	dTime(v) = ++time;
	discover[v] = dTime(v);
	for (int u=firstNbr(v); u<this->n; u=nextNbr(v, u)) {
		if (status(u) == UNDISCOVERED) {
			cout << vertex(v) << " discover " << vertex(u) << endl;
			type(v, u) = TREE;
			parent(u) = v;
			predecessor[u] = v;
			DFS(u, time, distance, predecessor, discover, finish);
		}
		else if (status(u) == DISCOVERED) {
			cout << vertex(v) << " backward " << vertex(u) << endl;
			type(v, u) = BACKWARD;
		}
		else if (status(u) == VISITED) {
			if (dTime(v) > dTime(u)) {
				cout << vertex(v) << " cross " << vertex(u) << endl;
				type(v, u) = CROSS;
			}
			else if (dTime(v) < dTime(u)) {
				cout << vertex(v) << " forward " << vertex(u) << endl;
				type(v, u) = FORWARD;
			}
			else cout << RED << "Exception of dTime of v:" << v << WHITE << endl;
		}
		else cout << RED << "Exception of status of v:" << v << WHITE << endl;
	}
	status(v) = VISITED;
	fTime(v) = ++time;
	finish[v] = fTime(v);
}




};
#endif