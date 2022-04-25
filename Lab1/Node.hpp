#ifndef _MY_NODE_HPP_

#define _MY_NODE_HPP_

#include "Node.h"

template <typename T>
Node<T>::Node(const T& value, Color color, Node* parent, Node* left, Node* right)
	:value(value), color(color), parent(parent), left(left), right(right) 
{ }

template <typename T>
bool Node<T>::isBlack() const {
	return color == BLACK;
}

template <typename T>
bool Node<T>::isRed() const {
	return color == RED;
}

#endif //!_MY_NODE_HPP_