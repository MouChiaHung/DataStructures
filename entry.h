#ifndef _ENTRY_H_
#define _ENTRY_H_

#include <stdio.h>

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
class Entry {
private:
	
public:
	K key;
	V val;
	Entry(K k = K(), V v = V()): key(k), val(v) {};
	Entry(Entry<K, V> const& e): key(e.key), val(e.val) {};
	~Entry() {};
	bool operator<(Entry<K, V> const& e) {return key < e.key;}
	bool operator>(Entry<K, V> const& e) {return key > e.key;}
	bool operator==(Entry<K, V> const& e) {return key == e.key;}
	bool operator!=(Entry<K, V> const& e) {return key != e.key;}
};



};
#endif