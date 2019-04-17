#ifndef _SORT_H_
#define _SORT_H_

#include <vector>
#include <list>

namespace amo {

class Sort {
private:
	static Sort* instance;
	Sort();
	~Sort();
public:
	static Sort& getInstance();
	std::vector<int> getRandomShuffledVector(int n);
	void bubbleSort(std::vector<int>& vector);
	std::vector<int> merge(std::vector<int>& left, std::vector<int>& right);
	void merge(std::vector<int>& partial_sorted_vector, int front, int mid, int end);
	std::vector<int> mergeSort(std::vector<int>& vector);
	void mergeSort(std::vector<int>& vector, int front, int end);
	void selectionSort(std::vector<int>& vector);
	void insertionSort(std::vector<int>& vector);
	void quickSort(std::vector<int>& vector);	
	void quickSort(std::vector<int>& vector, int front, int end);
	int reverse(std::list<int>& list);
};

};
#endif