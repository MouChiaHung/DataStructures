 /*************************
  *  sort.cpp
  *  editor: amo
  *************************/
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#include <algorithm>    // std::shuffle
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

#include <sort.h>
#include <iterator>     // std::advance
#include <limits> 
using namespace amo;

/* -------------------------------------------------------------------- */
/* my define macro                                                     */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* global variables                                                     */
/* -------------------------------------------------------------------- */
// Allocating and initializing Class's static data member
Sort* Sort::instance = 0;

/* -------------------------------------------------------------------- */
/* implements                                                           */
/* -------------------------------------------------------------------- */
amo::Sort::Sort() {
	std::cout << "[Sort::Sort()]:" << this << std::endl;
}

amo::Sort::~Sort() {
	std::cout << "[Sort::~Sort()]:" << this << std::endl;
}

Sort& amo::Sort::getInstance() {
	if (instance == nullptr) {
		std::cout << "[Sort::getInstance()]:going to 'instance = new Sort()':" << &instance << std::endl;
		instance = new Sort();
	} 
	std::cout << "[Sort::getInstance()]:returns:" << instance << std::endl;
	return *instance;
} 	

std::vector<int> amo::Sort::getRandomShuffledVector(int n) {
	std::vector<int> vector;
	for (int i=0;i<n;i++) vector.push_back(i);
	random_shuffle(vector.begin(), vector.end());
	std::cout << "[Sort::getRandomShuffledVector()]:returns a vector at " << &vector << std::endl;
	return vector;
}

void amo::Sort::bubbleSort(std::vector<int>& vector) {
	bool is_sorted = false;
	int n = 0;
	while (!is_sorted) {
		n++;
		std::cout << "[Sort::bubbleSort(std::vector<int>&)]:while-loop for " << n << " times"<< std::endl;
		is_sorted = true;
		for (int i=1;i<vector.size()-(n-1);i++) {
		//for (int i=1;i<vector.size();i++) {
			std::cout << "[Sort::bubbleSort(std::vector<int>&)]:for-loop for " << i << " runs"<< std::endl;
			if (vector.at(i) < vector.at(i-1)) {
				std::cout << "[Sort::bubbleSort(std::vector<int>&)]:going to swap(vector[" << i-1 << "]:" << vector.at(i-1) 
						  << " and vector[" << i << "]:" << vector.at(i) << std::endl;
				std::swap(vector.at(i-1), vector.at(i));
				is_sorted = false;
			}
		}
	}
}

#if 1
int amo::Sort::reverse(std::list<int>& list) {
	int exchange = 0;
	int move = 0;
	int distance_lo = 0;
	int distance_hi = 0;
	std::list<int>::iterator it_lo = list.begin();
	std::list<int>::iterator it_hi = --list.end();
	while (1) {
		it_lo = list.begin();
		it_hi = --list.end();
		std::advance(it_lo, move);
		std::advance(it_hi, -move);
		distance_lo = std::distance(list.begin(), it_lo);
		distance_hi = std::distance(list.begin(), it_hi);
		//std::cout << "[Sort::reverse(std::list<int>&)]: distance_lo:" << distance_lo << " and distance_hi:" << distance_hi << std::endl;
		std::cout << "\n[Sort::reverse(std::list<int>&)]: before swap  &*it_lo:" << &*it_lo << " and &*it_hi:" << &*it_hi << std::endl;
		if (distance_lo < distance_hi) {
			std::cout << "[Sort::reverse(std::list<int>&)]: swap " << *it_lo << " and " << *it_hi  << std::endl;
			std::swap(*it_lo, *it_hi);
			exchange++;
		} else {
			std::cout << "[Sort::reverse(std::list<int>&)]: lo >= hi and break from while-loop" << std::endl;
			break;
		}
		std::cout << "[Sort::reverse(std::list<int>&)]: after swap   &*it_lo:" << &*it_lo << " and &*it_hi:" << &*it_hi << std::endl;
		move++;
	}
	return exchange;
} 

#else //swap nodes rather than elements which is nothing like that is possible for vector, of course, which is not node-based.
int amo::Sort::reverse(std::list<int>& list) {
	int exchange = 0;
	int move = 0;
	int distance_lo = 0;
	int distance_hi = 0;
	std::list<int>::iterator it_lo = list.begin();
	std::list<int>::iterator it_hi = --list.end();
	while (1) {
		it_lo = list.begin();
		it_hi = --list.end();
		std::advance(it_lo, move);
		std::advance(it_hi, -move);
		distance_lo = std::distance(list.begin(), it_lo);
		distance_hi = std::distance(list.begin(), it_hi);
		std::cout << "\n[Sort::reverse(std::list<int>&)]: before splice &*it_lo:" << &*it_lo << " and &*it_hi:" << &*it_hi << std::endl;
		if (distance_lo < distance_hi) {
			std::cout << "[Sort::reverse(std::list<int>&)]: splice " << *it_lo << " and " << *it_hi  << std::endl;
			std::list<int> tmp;
			tmp.splice(tmp.begin(), list, it_lo);
			tmp.splice(std::next(tmp.begin(),1), list, it_hi);
			
			for(std::list<int>::iterator it=tmp.begin(); it!=tmp.end(); it++){
				std::cout << "[Sort::reverse(std::list<int>&)]: tmp[" << std::distance(tmp.begin(), it) << "]:" << *it << std::endl;
			}
			std::cout << "[Sort::reverse(std::list<int>&)]: during splice it_lo(" << &*it_lo << "):" << *it_lo << " and it_hi(" << &*it_hi << "):" << *it_hi << std::endl;
			
			it_lo = list.begin();
			it_hi = --list.end();
			std::advance(it_lo, move); //insert before it_lo
			std::advance(it_hi, -move);
			std::advance(it_hi, 1); //insert after it_hi
			list.splice(it_lo, tmp, std::next(tmp.begin(),1));
			list.splice(it_hi, tmp, tmp.begin());
			exchange++;
		} else {
			std::cout << "[Sort::reverse(std::list<int>&)]: lo >= hi and break from while-loop" << std::endl;
			break;
		}
		std::cout << "[Sort::reverse(std::list<int>&)]: after splice it_lo(" << &*it_lo << "):" << *it_lo << " and it_hi(" << &*it_hi << "):" << *it_hi << std::endl;
		move++;
	}
	return exchange;
} 
#endif

struct functor_print {
	void operator() (int element) {
		std::cout << "element:" << element << std::endl;
	}
} my_functor_print;

std::vector<int> amo::Sort::merge(std::vector<int>& sorted_left, std::vector<int>& sorted_right) {
	std::vector<int> merge;
	int index_left=0, index_right=0;
	std::cout << "[Sort::merge(std::vector<int>&, std::vector<int>&)]: sorted_left:" << std::endl;
	for_each(sorted_left.begin(), sorted_left.end(), my_functor_print);
	std::cout << "[Sort::merge(std::vector<int>&, std::vector<int>&)]: sorted_right:" << std::endl;
	for_each(sorted_right.begin(), sorted_right.end(), my_functor_print);
	while (index_left < sorted_left.size() && index_right < sorted_right.size()) {
		if (sorted_left.at(index_left) < sorted_right.at(index_right)) {
			merge.push_back(sorted_left.at(index_left));
			index_left++;
		} else {
			merge.push_back(sorted_right.at(index_right));
			index_right++;
		}	
	} 
	while (index_left < sorted_left.size()) {
			merge.push_back(sorted_left.at(index_left));
			index_left++;
	}
	while (index_right < sorted_right.size()) {
		merge.push_back(sorted_right.at(index_right));
		index_right++;
	}
	std::cout << "[Sort::merge(std::vector<int>&, std::vector<int>&)]: merge:" << std::endl;
	for_each(merge.begin(), merge.end(), my_functor_print);
	return merge;
}

/**
 * The elements in [front, mid] and [mid+1, end] are internally sorted.
 */
void amo::Sort::merge(std::vector<int>& partial_sorted_vector, int front, int mid, int end) {	
	std::cout << "[Sort::merge(std::vector<int>&, int, int]: front:" << front << ", mid:" << mid << ", end:" << end << std::endl;
	std::vector<int> sorted_left, sorted_right;
	int index_left=0, index_right=0;
	
	sorted_left.assign(std::next(partial_sorted_vector.begin(), front), std::next(partial_sorted_vector.begin(), mid+1)); //elements in [front, mid] are sorted
	sorted_left.insert(sorted_left.end(), std::numeric_limits<int>::max());
	sorted_right.assign(std::next(partial_sorted_vector.begin(), mid+1), std::next(partial_sorted_vector.begin(), end+1)); //elements in [mid+1, end] are sorted
	sorted_right.insert(sorted_right.end(), std::numeric_limits<int>::max());
	
	std::cout << "[Sort::merge(std::vector<int>&, int, int, int)]: sorted_left:" << std::endl;
	for_each(sorted_left.begin(), sorted_left.end(), my_functor_print);
	std::cout << "[Sort::merge(std::vector<int>&, int, int, int)]: sorted_right:" << std::endl;
	for_each(sorted_right.begin(), sorted_right.end(), my_functor_print);
	
#if 1
	for (int i=front; i<=end; i++) { //selection sort
		if (sorted_left.at(index_left) <= sorted_right.at(index_right)) { 
			partial_sorted_vector.at(i) = sorted_left.at(index_left);
			index_left++;
		} else {
			partial_sorted_vector.at(i) = sorted_right.at(index_right);
			index_right++;
		}
	}
#else
	for (int i=front; i<=end; i++)
		partial_sorted_vector.at(i) = (sorted_left.at(index_left)<=sorted_right.at(index_right))?sorted_left[index_left++]:sorted_right[index_right++];
	
#endif	
	std::cout << "[Sort::merge(std::vector<int>&, std::vector<int>&)]: partial_sorted_vector:" << std::endl;
	for_each(partial_sorted_vector.begin(), partial_sorted_vector.end(), my_functor_print);
}

/**
 * using new vector which is created and sorted, instead of using indexes to sort
 * , probably costs more memory space (higher space complexity) but lower time complexity (lower time complexity:O(n*log(n)).
 */ 
std::vector<int> amo::Sort::mergeSort(std::vector<int>& vector) {
	if (vector.size() < 2) { 
		std::cout << "[Sort::mergeSort(std::vector<int>&]: returns singular element vector with " << vector.back() << std::endl;
		return vector;
	}
	std::vector<int> sort;
	int mi =  vector.size()/2;
	std::vector<int> left, right;
	left.assign(vector.begin(), std::next(vector.begin(), mi));
	right.assign(std::next(vector.begin(), mi), vector.end());
	left = mergeSort(left);
	right = mergeSort(right);
	sort = merge(left, right);
	std::cout << "[Sort::mergeSort(std::vector<int>&]: returns sort vector with (size:" << sort.size() << ")" << std::endl;
	return sort;	
}

/**
 * in-place version, using indexes to sort the elements in [front, end]
 * , probably costs less memory space (lower space complexity) but higher time complexity (higher time complexity:O(2*n*log(n)) on vector::assign()
 */ 
void amo::Sort::mergeSort(std::vector<int>& vector, int front, int end) {
	std::cout << "[Sort::mergeSort(std::vector<int>&, int, int]: front:" << front << " and end:" << end << std::endl;
	if (front < end) {
		int mid = (front+end)/2;
		mergeSort(vector, front, mid);
		mergeSort(vector, mid+1, end);
		merge(vector, front, mid, end);
		return;
	} else if (front == end) {
		std::cout << "[Sort::mergeSort(std::vector<int>&, int, int]: returns and index:" << front << std::endl;
		return;
	} else {
		std::cout << "[Sort::mergeSort(std::vector<int>&, int, int]: !!! err and returns"<< std::endl;
		return;
	}
}

void amo::Sort::selectionSort(std::vector<int>& vector) {
	int min_value;
	int min_index;
	std::vector<int> unsorted;
	unsorted.assign(vector.begin(), vector.end());
	vector.clear();
	while (!unsorted.empty()) {
		min_value = unsorted.front();
		min_index = 0;
		for (std::vector<int>::iterator it=unsorted.begin()+1; it!=unsorted.end(); it++) {
			 if (min_value > *it) {
				min_value = *it;
				min_index = std::distance(unsorted.begin(), it);
			 }
		}
		std::cout << "[Sort::selectionSort(std::vector<int>&]: temporary min value:" << min_value << " and index:" << min_index << std::endl;
		unsorted.erase(std::next(unsorted.begin(), min_index));
		vector.push_back(min_value);
	}
}

#if 0
void amo::Sort::insertionSort(std::vector<int>& vector) {
	std::vector<int> sorted;
	for (std::vector<int>::iterator it_src=vector.begin(); it_src!=vector.end(); it_src++) {
		std::cout << "\n[Sort::insertSort(std::vector<int>&]: vector[" << distance(vector.begin(), it_src) << "]:" << *it_src << std::endl;
		int tmp = *it_src;
		sorted.push_back(tmp);
		for (std::vector<int>::iterator it=std::next(sorted.end(),-1); it!=std::next(sorted.begin(), 0); it--) {
			std::cout << "[Sort::insertSort(std::vector<int>&]: before sorted[" << distance(sorted.begin(), it) << "]:" << *it << std::endl;
		}
		for (std::vector<int>::iterator it=std::next(sorted.end(),-1); it!=std::next(sorted.begin(), 0); it--) {
			if (*it < *(std::next(it,-1))) { 
				std::cout << "[Sort::insertSort(std::vector<int>&]: going to swap *it:" << *it << " and *(it-1):"<< *(it-1) << std::endl;
				std::swap(*it, *(it-1));
			}
		}
		for (std::vector<int>::iterator it=std::next(sorted.end(),-1); it!=std::next(sorted.begin(), 0); it--) {
			std::cout << "[Sort::insertSort(std::vector<int>&]: after sorted[" << distance(sorted.begin(), it) << "]:" << *it << std::endl;
		}
	}
	vector.swap(sorted);
}
#else
/**
 * in-place version
 */
void amo::Sort::insertionSort(std::vector<int>& vector) {
	for (std::vector<int>::iterator it=vector.begin(); it!=vector.end(); it++) {
		int element = *it;
		int index_element = std::distance(vector.begin(), it);
		for (int j = index_element-1; j>=0; j--) {
			if (element < vector.at(j)) {
				vector.at(j+1) = vector.at(j);
				index_element = j;
			}
		}
		vector.at(index_element) = element;
		std::cout << "for element:" << element << std::endl;
		for (std::vector<int>::iterator it=vector.begin(); it!=vector.end(); it++) {
			std::cout << "[Sort::insertSort(std::vector<int>&]: sorting for " << std::distance(vector.begin(), it) 
					  << " vector[" << distance(vector.begin(), it) << "]:" << *it << std::endl;
		}
	}
}
#endif

void amo::Sort::quickSort(std::vector<int>& vector) {
	if (vector.size() <=1) return;
	std::cout << "" << std::endl;
	for (std::vector<int>::iterator it=vector.begin();it!=vector.end();it++) {
		std::cout << "[Sort::quickSort(std::vector<int>&]: before vector[" << distance(vector.begin(), it) << "]:" << *it << std::endl;
	}
	std::vector<int> left, right;
	int pivot = vector.back();
	
	//partition
	for (std::vector<int>::iterator it=vector.begin(); it!=std::next(vector.end(),-1); it++) {
		if ((*it) < pivot) {
			left.push_back(*it);
		} else {
			right.push_back(*it);
		}
	}
	
	//print elements
	for (std::vector<int>::iterator it=left.begin();it!=left.end();it++) {
		std::cout << "[Sort::quickSort(std::vector<int>&]: left[" << distance(left.begin(), it) << "]:" << *it << std::endl;
	}
	std::cout << "[Sort::quickSort(std::vector<int>&]: pivot:" << pivot << std::endl;
	for (std::vector<int>::iterator it=right.begin();it!=right.end();it++) {
		std::cout << "[Sort::quickSort(std::vector<int>&]: right[" << distance(right.begin(), it) << "]:" << *it << std::endl;
	}
	
	quickSort(left);
	quickSort(right);
	vector.clear();
	vector.insert(vector.end(), left.begin(), left.end());
	vector.insert(vector.end(), pivot);
	vector.insert(vector.end(), right.begin(), right.end());
	std::cout << "" << std::endl;
	for (std::vector<int>::iterator it=vector.begin();it!=vector.end();it++) {
		std::cout << "[Sort::quickSort(std::vector<int>&]: after vector[" << distance(vector.begin(), it) << "]:" << *it << std::endl;
	}
}

/**
 * in-place version, using indexes to sort the elements in [front, end]
 * , probably costs less memory space (lower space complexity)
 */
void amo::Sort::quickSort(std::vector<int>& vector, int front, int end) {
	if (front >= end) return;
	std::cout << "" << std::endl;
	
	//partition
	int pivot = vector.at(end);
	int index_pivot = end;
	int l=front-1;
	std::cout << "[Sort::quickSort(std::vector<int>&]: before partition front:" << front << ", index_pivot:" << index_pivot << "(=" << pivot << ")" << " and end:" << end << std::endl;
	for (int r=front; r<end; r++) {
		if (vector.at(r) < pivot) {
			l++;
			std::swap(vector.at(l), vector.at(r));
		}
	}
	l++;
	std::swap(vector.at(l), vector.at(index_pivot));
	index_pivot = l;
	
	for (std::vector<int>::iterator it=vector.begin();it!=vector.end();it++) {
		std::cout << "[Sort::quickSort(std::vector<int>&]: after partition front:" << front << " to end:" << end << " vector[" << distance(vector.begin(), it) << "]:" << *it << std::endl;
	}
	
	quickSort(vector, front, index_pivot-1);
	quickSort(vector, index_pivot+1, end);
	
	for (std::vector<int>::iterator it=vector.begin();it!=vector.end();it++) {
		std::cout << "[Sort::quickSort(std::vector<int>&]: after quick sort front:" << front << " to end:" << end << " vector[" << distance(vector.begin(), it) << "]:" << *it << std::endl;
	}
	std::cout << "" << std::endl;
}
