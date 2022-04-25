#ifndef _MY_MAP_

#define _MY_MAP_

#include "RedBlackTree.hpp"

#include <list>
#include <stdexcept>
#include <iostream>

template <typename T, typename U>
class Map
{
public:
	Map() = default;

	Map(const Map&) = default;
	Map(Map&&) = default;
	~Map() = default;

	bool insert(T key, U value);
	bool remove(T key);
	bool find(T key) const;

	//U& operator[](T key);
	//const U& operator[](T key) const;

	void clear();

	std::list<T> get_keys() const;
	std::list<U> get_values() const;

	void print() const;

private:
	struct Pair {
		Pair();
		Pair(T key, U value);
		T key;
		U value;

		bool operator<(const Pair& other) const;
		bool operator>(const Pair& other) const;
		bool operator<=(const Pair& other) const;
		bool operator>=(const Pair& other) const;
		bool operator==(const Pair& other) const;
		bool operator!=(const Pair& other) const;
	};
private:
	RedBlackTree<Pair> tree; //RedBlackTree<Pair<T, U>> tree; 
};

#endif //!_MY_MAP_