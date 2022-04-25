#ifndef _MY_ITERATOR_ 

#define _MY_ITERATOR_

#include "Node.hpp"

#include <stdexcept>

template <typename T>
class Iterator {
public:
	Iterator(Node<T>* node, Node<T>* nil);

	bool operator!=(const Iterator& other) const;
	bool operator==(const Iterator& other) const;

	Iterator& operator++();
	Iterator operator++(int);

	Iterator& operator--();
	Iterator operator--(int);

	T& operator* ();
	T* operator-> ();

	const T& operator* () const;
	const T* operator-> () const;


private:
	Node<T>* get_the_most_left(Node<T>* root);
	Node<T>* get_the_most_right(Node<T>* root);

	Node<T>* first_nearest_bigger_upper();
	Node<T>* first_nearest_least_upper();

	Node<T>* current;
	Node<T>* nil;
};

#endif //!_MY_ITERATOR_