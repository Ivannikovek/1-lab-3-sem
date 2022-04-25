#ifndef _MY_ITERATOR_HPP_ 

#define _MY_ITERATOR_HPP_

#include "Iterator.h"

template <typename T>
Iterator<T>::Iterator(Node<T>* node, Node<T>* nil) :current(node), nil(nil)
{}

template <typename T>
bool Iterator<T>::operator==(const Iterator& other) const {
	if (current == other.current)
		return true;
	return false;
}

template <typename T>
bool Iterator<T>::operator!=(const Iterator& other) const {
	return !operator==(other);
}

template <typename T>
Iterator<T>& Iterator<T>::operator++() {
	if (current == nil)
		throw std::out_of_range("Iterator is out of range.\n");

	if (current->right != nil)
		current = get_the_most_left(current->right);
	else
		if (current->parent == nil) //if parent doesn't exsists
			current = nil;
		else
			//if (current->parent->left == current) //if parent exsists and temp node is left son
				//current = current->parent;
			//else
				//if (current->parent->right == current) //if parent exsists and temp node is right son
			current = first_nearest_bigger_upper();

	return *this;
}

template <typename T>
Iterator<T> Iterator<T>::operator++(int) {
	Iterator<T> copy(*this);

	operator++();

	return copy;
}

template <typename T>
Iterator<T>& Iterator<T>::operator--() {
	if (current == nil) //if iterator == end()
		current = get_the_most_right(nil->right); //get_the_most_right(root)
	else
		if (current->left != nil)
			current = get_the_most_right(current->left);
		else
			if (current->parent == nil)
				throw std::out_of_range("Iterator is out of range.\n");
			else
				//if (current->parent->right == current) //if parent exsists and node is right son
					//current = current->parent;
				//else
					//if (current->parent->left == current) //if parent exsists and node is left son
				current = first_nearest_least_upper();

	return *this;
}

template <typename T>
Iterator<T> Iterator<T>::operator--(int) {
	Iterator<T> copy(*this);

	operator--();

	return copy;
}

template <typename T>
T& Iterator<T>::operator* () {
	return current->value;
}

template <typename T>
T* Iterator<T>::operator-> () {
	return &(current->value);
}

template <typename T>
const T& Iterator<T>::operator* () const {
	return current->value;
}

template <typename T>
const T* Iterator<T>::operator-> () const {
	return &(current->value);
}

template <typename T>
Node<T>* Iterator<T>::get_the_most_left(Node<T>* root) {
	Node<T>* temp = root;
	while (temp->left != nil)
		temp = temp->left;

	return temp;
}

template <typename T>
Node<T>* Iterator<T>::get_the_most_right(Node<T>* root) {
	Node<T>* temp = root;
	while (temp->right != nil)
		temp = temp->right;

	return temp;
}

template <typename T>
Node<T>* Iterator<T>::first_nearest_bigger_upper() {
	Node<T>* upper = current->parent;

	while (upper != nil && current->value > upper->value)
		upper = upper->parent;

	return upper;
}

template <typename T>
Node<T>* Iterator<T>::first_nearest_least_upper() {
	Node<T>* upper = current->parent;

	while (upper != nil && current->value < upper->value)
		upper = upper->parent;

	return upper;
}

#endif //!_MY_ITERATOR_