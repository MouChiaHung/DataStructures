#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <fstream>
#include <stdio.h>
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
	Tv data;
	int inDegree;
	int outDegree;
	VStatus status;
	int dTime;
	int fTime;
	int parent;
	int priority;
public:
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
	os << WHITE << "[status]   :" << vertex.status << endl;
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
		os << RED << "no edge instance";
		return os;
	}
	os << WHITE << "[this]  :" << &edge << endl;
	os << WHITE << "[data]  :" << edge.data << endl;
	os << WHITE << "[weight]:" << edge.weight << endl;
	os << WHITE << "[type]  :" << edge.type << endl;
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
public:
	int n;
	int e;
	Graph() {
		std::cout << "[Graph::Graph()]: this:" << this << ", Tv type:" << typeid(Tv).name() << ", Te type:" << typeid(Te).name() << WHITE << std::endl;
	}
	~Graph() {
		std::cout << "[Graph::~Graph()]: this:" << this << WHITE << std::endl;
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
	VStatus status(int i);
	int dTime(int i);
	int fTime(int i);
	int parent(int i);
	int priority(int i);
	//edge
	bool exist(int i, int j);
	void insert(const Te& d, int i, int j, int weight);
	Te remove(int i, int j);
	EType type(int i, int j);
	Te& edge(int i, int j);
	int weight(int i, int j);
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
	std::vector<Vertex<Tv>*> vertexes;
	std::vector<std::vector<Edge<Te>*>> edges;
	AdjaMatrix(): Graph<Tv, Te>() {
		std::cout << "[AdjaMatrix::AdjaMatrix()]: this:" << this << ", Tv type:" << typeid(Tv).name() << ", Te type:" << typeid(Te).name() << WHITE << std::endl;
	}
	~AdjaMatrix() {
		std::cout << "[AdjaMatrix::~AdjaMatrix()]: this:" << this << WHITE << std::endl;
		//doing something...
	}
	//overload for vertexes
	Tv& vertex(int i) { return vertexes[i].data; }
	int inDegree(int i) { return vertexes[i].inDegree; }
	int outDegree(int i) { return vertexes[i].outDegree; }
	int firstNbr(int i) { return nextNbr(i, this->n-1); }
	int nextNbr(int i, int j) {
		while (j >= 0) {
			if (exist(i, j)) break;
			j--;
		}
		std::cout << "next nbr:" << j << WHITE << std::endl;
		return j;
	}
	VStatus status(int i) { return vertexes[i].status; }
	int dTime(int i) { return vertexes[i].dTime; }
	int fTime(int i) { return vertexes[i].fTime; }
	int parent(int i) { return vertexes[i].parent; }
	int priority(int i) { return vertexes[i].priority; }
	int insert(const Tv& d);
	Tv remove(int i); //[0, n)
	//overload for edges
	void insert(const Te& d, int i, int j, int weight); //[0, e)
	Te remove(int i, int j);
	bool exist(int i, int j);
	EType type(int i, int j);
	Te& edge(int i, int j);
	int weight(int i, int j);
	//extend
	void print(std::ostream& os);

friend std::ostream& operator<<(std::ostream& os, AdjaMatrix<Tv,Te>& matrix) {
	matrix.print(os);
	return os;
}	
};

template<typename Tv, typename Te>
void amo::AdjaMatrix<Tv, Te>::print(std::ostream& os) {
	typename std::vector<Vertex<Tv>*>::iterator it_vertexes; //points to vertexes[i]
	typename std::vector<std::vector<Edge<Te>*>>::iterator it_edges; //points to edges
	typename std::vector<Edge<Te>*>::iterator it_adjs; //points to edges[i]
	os << GREEN << "[AdjaMatrix::print()]: size of vertexes:" << vertexes.size() << WHITE << std::endl;
	os << GREEN << "[AdjaMatrix::print()]: size of edges:" << edges.size() << WHITE << std::endl;
	for (it_edges=edges.begin(); it_edges!=edges.end(); it_edges++) {
		os << GREEN << "[AdjaMatrix::print()]: size of edges["<< distance(edges.begin(), it_edges) << "]:" << it_edges->size() << WHITE << std::endl;
	}
	os << GREEN << "\n--- VERTEX TOP ------" << WHITE << std::endl;
	for (it_vertexes=vertexes.begin(); it_vertexes!=vertexes.end(); it_vertexes++) {
		os << **it_vertexes; //prints vertex 
		os << endl;
	}
	os << GREEN << "--- VERTEX BOTTOM ------" << WHITE << std::endl;
	os << GREEN << "\n--- EDGE TOP ------" << WHITE << std::endl;
	for (it_edges=edges.begin(); it_edges!=edges.end(); it_edges++) {
		for (it_adjs=it_edges->begin(); it_adjs!=it_edges->end(); it_adjs++) {
			os << **it_adjs;
			os << endl;
		}
	}
	os << GREEN << "--- EDGE BOTTOM ------" << WHITE << std::endl;
}

//For vertexes
/**
 * When a class template derives from a base class template, the base members are not visible in the derived class template definition.
 * (This makes sense, until you specialize, there is no class, and so there are no members. 
 * Explicit specializations can always change the meaning of any given template class.)
 */
template<typename Tv, typename Te>
int amo::AdjaMatrix<Tv, Te>::insert(const Tv& data) {
	std::cout << YELLOW << "[AdjaMatrix::insert()]: data:" << data << WHITE << std::endl;
	Vertex<Tv>* vertex = new Vertex<Tv>(data);
	std::vector<Edge<Te>*>* adjs = new std::vector<Edge<Te>*>();
	typename std::vector<Vertex<Tv>*>::iterator it_vertexes;
	typename std::vector<std::vector<Edge<Te>*>>::iterator it_edges;
	typename std::vector<Edge<Te>*>::iterator it_adjs;
	
	std::cout << YELLOW << "[AdjaMatrix::insert()]: going to push a dummy edge to edges(size:" << this->edges.size() << ")" << WHITE << std::endl;
	int tmp = this->n;
	while (0<tmp--) adjs->push_back(NULL);
	it_edges = this->edges.insert(edges.end(), *adjs);
	std::cout << YELLOW << "[AdjaMatrix::insert()]: inserted an edges[" << distance(edges.begin(), it_edges) << "]" << WHITE << std::endl;
	for (it_edges=edges.begin(); it_edges!=edges.end(); it_edges++) {
		it_adjs = it_edges->insert(it_edges->end(), (Edge<Te>*)0);
		std::cout << YELLOW << "[AdjaMatrix::insert()]: inserted an edges[" <<  distance(this->edges.begin(), it_edges)
				  << "][" << distance(it_edges->begin(), it_adjs) << "]" << WHITE << std::endl;
	}
	
	std::cout << YELLOW << "[AdjaMatrix::insert()]: going to insert a vertex into vertexes(size:" << this->vertexes.size() << ")" << WHITE << std::endl;
	it_vertexes = this->vertexes.insert(vertexes.end(), vertex);
	this->n++;	

	return distance(vertexes.begin(), it_vertexes);
}

template<typename Tv, typename Te>
Tv amo::AdjaMatrix<Tv, Te>::remove(int i) { 




}

//For edges
template<typename Tv, typename Te>
void amo::AdjaMatrix<Tv, Te>::insert(const Te& d, int i, int j, int weight) {
	if (exist(i, j)) {
		cout << RED << "edge between " << i << " and " << j << " already exists" << WHITE << std::endl;
		return;
	}
	Edge<Te>* e = new Edge<Te>(d, weight);
	edges[i][j] = e;
	e++;
	vertexes[i]->outDegree++;
	vertexes[j]->inDegree++;
}

template<typename Tv, typename Te>
Te amo::AdjaMatrix<Tv, Te>::remove(int i, int j) {
	if (!exist(i, j)) {
		cout << RED << "edge between " << i << " and " << j << " doesn't exist" << WHITE << std::endl;
		return NULL;
	}
	typename std::vector<std::vector<Edge<Te>*>>::iterator it_edges;
	typename std::vector<Edge<Te>*>::iterator it_adjs;
	it_edges = std::next(this->edges.begin(), i);
	it_adjs = std::next(it_edges->begin(), j);
		
	Te e = it_adjs->data;
	cout << RED << "going to erase an edge form edges(data:" << e << ")" << WHITE << std::endl;
	it_edges.erase(it_adjs);
	e--;
	vertexes[i]->outDegree--;
	vertexes[j]->inDegree--;
	return e;
}

template<typename Tv, typename Te>
bool amo::AdjaMatrix<Tv, Te>::exist(int i, int j) {
	bool ret = true;
	ret &= (0<=i);
	//'this' is always implicitly dependent in a template and the lookup is therefore deferred until the template is actually instantiated.
	if (!ret) { 
		cout << RED << "out of limit, i < 0" << WHITE << std::endl;
		return ret;
	}
	ret &= i<this->n;
	if (!ret) {
		cout << RED << "out of limit, i >= " << this->n << WHITE << std::endl;
		return ret;
	}
	ret &= (0<=j);
	if (!ret) {
		cout << RED << "out of limit, j < 0" << WHITE << std::endl;
		return ret;
	}
	ret &= (j<this->n);
	if (!ret) {
		cout << RED << "out of limit, j >= " << this->n << WHITE << std::endl;
		return ret;
	}
	ret &= (this->edges[i][j] != NULL);
	if (!ret) {
		cout << RED << "edges[" << i << "][" << j << "] is NULL" << WHITE << std::endl;
		return ret;
	}
	return ret;
}

template<typename Tv, typename Te>
EType amo::AdjaMatrix<Tv, Te>::type(int i, int j) {
	if (!exist(i, j)){
		cout << RED << "no edge exists and return UNDETERMINED" << WHITE << std::endl;
		return UNDETERMINED;
	}
	Edge<Te>* edge = edges[i][j];
	return edge->type;
}

template<typename Tv, typename Te>
Te& amo::AdjaMatrix<Tv, Te>::edge(int i, int j) {
	if (!exist(i, j)){
		cout << RED << "no edge exists and return NULL" << WHITE << std::endl;
		Te* dummy = new Te();
		return *dummy;
	}
	Edge<Te>* edge = edges[i][j];
	return edge->data;
}

template<typename Tv, typename Te>
int amo::AdjaMatrix<Tv, Te>::weight(int i, int j) {
	if (!exist(i, j)){
		cout << RED << "no edge exists and return NULL" << WHITE << std::endl;
		return ERROR_CODE;
	}
	Edge<Te>* edge = edges[i][j];
	return edge->weight;
}











};
#endif