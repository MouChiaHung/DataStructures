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
	os  << WHITE << "[this]     :" << &vertex << endl;
	os  << WHITE << "[data]     :" << vertex.data << endl;
	os  << WHITE << "[inDegree] :" << vertex.inDegree << endl;
	os  << WHITE << "[outDegree]:" << vertex.outDegree << endl;
	os  << WHITE << "[status]   :" << vertex.status << endl;
	os  << WHITE << "[dTime]    :" << vertex.dTime << endl;
	os  << WHITE << "[fTime]    :" << vertex.fTime << endl;
	os  << WHITE << "[parent]   :" << vertex.parent << endl;
	os  << WHITE << "[priority] :" << vertex.priority << endl;
	return os;
}		
};

template<typename Te>
class Edge {
private:	
	Te data;
	int weight;
public:	
	EType type;
	Edge(const Te& d = (Te) 0, int w = 0) : data(d), weight(w), type(UNDETERMINED) {
		std::cout << "[Vertex::Vertex()]: this:" << this << ", Te type:" << typeid(Te).name() << WHITE << std::endl;
	}
	~Edge() {
		std::cout << "[Edge::~Edge()]: this:" << this << WHITE << std::endl;
	}
friend std::ostream& operator<<(std::ostream& os, const Edge& edge) {
	os  << WHITE << "[this]  :" << &edge << endl;
	os  << WHITE << "[data]  :" << edge.data << endl;
	os  << WHITE << "[weight]:" << edge.weight << endl;
	os  << WHITE << "[type]  :" << edge.type << endl;
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
	int insert(const Tv& data);
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
	void insert(const Te& e, int i, int j, int weight);
	Te remove(int i, int j);
	EType& type(int i, int j);
	Te& edge(int i, int j);
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
	std::vector<Vertex<Tv>*> vertexes;
	std::vector<std::vector<Edge<Te>*>> edges;
	AdjaMatrix(): Graph<Tv, Te>() {
		std::cout << "[AdjaMatrix::AdjaMatrix()]: this:" << this << ", Tv type:" << typeid(Tv).name() << ", Te type:" << typeid(Te).name() << WHITE << std::endl;
	}
	~AdjaMatrix() {
		std::cout << "[AdjaMatrix::~AdjaMatrix()]: this:" << this << WHITE << std::endl;
		//doing something...
	}
	int insert(const Tv& v);
	void print();

friend std::ostream& operator<<(std::ostream& os, const AdjaMatrix<Tv,Te>& matrix) {
	os  << WHITE << "[this]:" << &matrix << endl;
	return os;
}	
};

template<typename Tv, typename Te>
int amo::AdjaMatrix<Tv, Te>::insert(const Tv& data) {
	std::cout << YELLOW <<"[AdjaMatrix::insert()]: data:" << data << WHITE << std::endl;
	Vertex<Tv>* vertex = new Vertex<Tv>(data);
	//std::vector<Edge<Te>*> adjs = new std::vector<Edge<Te>*>();
	std::vector<Edge<Te>*> adjs;
	std::cout << YELLOW <<"[AdjaMatrix::insert()]: going to insert edge" << WHITE << std::endl;
	//typename std::vector<std::vector<Edge<Te>*>>::iterator it_edges = this->edges.insert(std::next(edges.end(), -1), adjs);
	edges.insert(std::next(edges.end(), 0), adjs);
	//std::cout << YELLOW <<"[AdjaMatrix::insert()]: going to insert vertex" << WHITE << std::endl;
	//typename std::vector<Vertex<Tv>*>::iterator it_vertexes = this->vertexes.insert(std::next(vertexes.end(), -1), vertex);
	//return distance(vertexes.begin(), it_vertexes);
	return 0;
}


template<typename Tv, typename Te>
void amo::AdjaMatrix<Tv, Te>::print() {
#if 0
	std::cout << "[AdjaMatrix::print()]: size of vertexes" << vertexes.size() << WHITE << std::endl;
	typename std::vector<amo::Vertex<Tv>*>::iterator it_vertexes;
	typename std::vector<std::vector<amo::Edge<Te>*>>::iterator it_edges;
	typename std::vector<amo::Edge<Te>*>::iterator it_adjs;
	for (it_vertexes=vertexes.begin(); it_vertexes!=vertexes.end(); it_vertexes++) {
		cout << **it_vertexes; //prints vertex 
		cout << endl;
	}
	
	for (it_edges=edges.begin(); it_edges!=edges.end(); it_edges++) {
		for (it_adjs=it_edges->begin(); it_adjs!=it_edges->end(); it_adjs++) {
			cout << **it_adjs;
			cout << endl;
		}
	}
#endif
}












};
#endif