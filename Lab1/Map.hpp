#ifndef _MY_MAP_HPP_

#define _MY_MAP_HPP_

#include "Map.h"

template <typename T, typename U>
Map<T, U>::Pair::Pair() :key(), value()
{}

template <typename T, typename U>
Map<T, U>::Pair::Pair(T key, U value) :key(key), value(value)
{}

template <typename T, typename U>
bool Map<T, U>::insert(T key, U value) {
	return tree.insert(Pair(key, value));
}

template <typename T, typename U>
bool Map<T, U>::remove(T key) {
	return tree.remove(Pair(key, U()));
}

template <typename T, typename U>
bool Map<T, U>::find(T key) const {
	for (typename RedBlackTree<Pair>::Iterator i = tree.begin(); i != tree.end(); ++i)
		if (i->key == key)
			return true;

	return false;
}

//U& Map::operator[](T key) {
//	tree.insert(Pair(key, U()));
//
//	for (RedBlackTree::iterator i = tree.begin(); i != tree.end(); ++i)
//		if (i->key == key)
//			return i.value;
//}

//const U& Map::operator[](T key) const {
//	for (RedBlackTree::const_iterator i = tree.begin(); i != tree.end(); ++i)
//		if (i->key == key)
//			return i.value;
//
//	throw std::invalid_argument("Key is absent in map.\n");
//}

template <typename T, typename U>
void Map<T, U>::clear() {
	tree.clear();
}

template <typename T, typename U>
std::list<T> Map<T, U>::get_keys() const {
	std::list<T> keys;

	for (typename RedBlackTree<Pair>::Iterator i = tree.begin(); i != tree.end(); ++i)
		keys.push_back(i->key);

	return keys;
}

template <typename T, typename U>
std::list<U> Map<T, U>::get_values() const {
	std::list<U> values;

	for (typename RedBlackTree<Pair>::Iterator i = tree.begin(); i != tree.end(); ++i)
		values.push_back(i->value);

	return values;
}

template <typename T, typename U>
void Map<T, U>::print() const {
	for (typename RedBlackTree<Pair>::Iterator i = tree.begin(); i != tree.end(); ++i)
		std::cout << i->key << ", \"" << i->value  << "\" " << std::endl;
}

template <typename T, typename U>
bool Map<T, U>::Pair::operator<(const Pair& other) const {
	return key < other.key;
}

template <typename T, typename U>
bool Map<T, U>::Pair::operator>(const Pair& other) const {
	return other.operator<(*this);
}

template <typename T, typename U>
bool Map<T, U>::Pair::operator<=(const Pair& other) const {
	return !(operator>(other));
}

template <typename T, typename U>
bool Map<T, U>::Pair::operator>=(const Pair& other) const {
	return !(operator<(other));
}

template <typename T, typename U>
bool Map<T, U>::Pair::operator==(const Pair& other) const {
	return key == other.key;
}

template <typename T, typename U>
bool Map<T, U>::Pair::operator!=(const Pair& other) const {
	return !(operator==(other));
}

#endif //!_MY_MAP_HPP_