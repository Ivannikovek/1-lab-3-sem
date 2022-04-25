#ifndef _MY_RED_BLACK_TREE_HPP_

#define _MY_RED_BLACK_TREE_HPP_

#include "RedBlackTree.h"

template <typename T>
RedBlackTree<T>::RedBlackTree() :nil(new Node(T(), BLACK)), root(nil) {
	update_nil_pointers_to_root();
}


template <typename T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree& other) : RedBlackTree() {
	root = get_clone(other.root, other.nil, nil);
	update_nil_pointers_to_root();
}


template <typename T>
RedBlackTree<T>::RedBlackTree(RedBlackTree&& other) : RedBlackTree() {
	std::swap(root, other.root);
	std::swap(nil, other.nil);
}


template <typename T>
RedBlackTree<T>::~RedBlackTree() {
	clear();
	delete nil;
}

template <typename T>
RedBlackTree<T>& RedBlackTree<T>::operator=(const RedBlackTree& other) {
	if (this != &other) {
		clear();
		root = get_clone(other.root, other.nil, nil);
		update_nil_pointers_to_root();
	}

	return *this;
}

template <typename T>
RedBlackTree<T>& RedBlackTree<T>::operator=(RedBlackTree&& other) {
	clear();

	std::swap(root, other.root);
	std::swap(nil, other.nil);

	return *this;
}
template <typename T>
typename RedBlackTree<T>::Iterator RedBlackTree<T>::begin() {
	if (root == nil)
		return end();

	return Iterator(get_the_most_left(root), nil);
}

template <typename T>
typename RedBlackTree<T>::Iterator RedBlackTree<T>::end() {
	return Iterator(nil, nil);
}

template <typename T>
typename RedBlackTree<T>::Iterator RedBlackTree<T>::begin() const {
	if (root == nil)
		return end();

	return Iterator(get_the_most_left(root), nil);
}

template <typename T>
typename RedBlackTree<T>::Iterator RedBlackTree<T>::end() const {
	return Iterator(nil, nil);
}

template <typename T>
void RedBlackTree<T>::clear() {
	delete_tree(root, nil);
	root = nil;
	update_nil_pointers_to_root();
}

template <typename T>
bool RedBlackTree<T>::insert(T value) {
	Node* new_node; //new node
	if (!insert(root, nil, value, new_node))
		return false;

	restoring_of_properties_after_inserting(new_node);

	update_nil_pointers_to_root();
	return true;
}

#include <iostream>

template <typename T>
bool RedBlackTree<T>::insert(Node*& node, Node* parent, T value, Node*& new_node) {
	if (node == nil) {
		new_node = new Node(value, RED, parent, nil, nil);
		node = new_node;
		return true;
	}

	if (value == node->value) 
		return false;

	if (value < node->value)
		return insert(node->left, node, value, new_node);

	//if (value > node->value)
	return insert(node->right, node, value, new_node);
}


template <typename T>
bool RedBlackTree<T>::remove(T value) {
	if (!remove(root, value))
		return false;

	update_nil_pointers_to_root();

	//delete deleted;

	return true;
}

template <typename T>
bool RedBlackTree<T>::remove(Node*& node, T value) {
	if (node == nil)
		return false;

	if (node->value == value) {
		Node* removing;
		if (node->left != nil && node->right != nil)
			removing = remove_node_with_2_children(node);
		else
			removing = remove_node_with_0_or_1_child(node);

		//if (removing == root) {
		//	root = nil;
		//	update_nil_pointers_to_root();
		//}

		delete removing;

		return true;
	}

	if (value < node->value)
		return remove(node->left, value);

	//if (value > node->value)
	return remove(node->right, value);
}

//change the minimum in rightbranch with removing tree
//for not copying the value (of T type), nodes are swaping 
//function return node which replaces deleting
template <typename T>
typename RedBlackTree<T>::Node* RedBlackTree<T>::remove_node_with_2_children(Node* node) {
	//R - removing
	Node* R = node;
	Node*& reference_to_R_place = (R->parent->left == R ? R->parent->left : R->parent->right);

	//M - min in the right subtree (which means themost left)
	Node* M = get_the_most_left(node->right);
	Node*& reference_to_M_place = (M->parent->left == M ? M->parent->left : M->parent->right); //can be first in the right subtree, or left

	//for move-types is better, for other's there will be copy:
	std::swap(M->value, R->value);
	return remove_node_with_0_or_1_child(M);
}

//function return node which replaces deleting
template <typename T>
typename RedBlackTree<T>::Node* RedBlackTree<T>::remove_node_with_0_or_1_child(Node* M) {

	//red node has two black children or two black leaves
	//(it can't have one black child and one blackleaf, it's disbalance the tree)
	//here we are because it has two black leaves
	if (M->isRed()) {
		Node* parent = M->parent;
		Node*& reference_to_place = (parent->left == M ? parent->left : parent->right);
		reference_to_place = nil;

		//delete M;

		return M;
	}

	//node M is black

	Node* C = (M->left == nil ? M->right : M->left);
	if (C->isRed()) { //&& M.isBlack()
		Node* parent = M->parent;
		Node*& reference_to_place = (parent->left == M ? parent->left : parent->right);

		reference_to_place = C;
		C->parent = parent;

		C->color = BLACK;

		//delete M;

		return M;
	}

	//node C is black

	//black node has two black children or two black leaves
	//(it can't have one black child and one blackleaf, it's disbalance the tree)
	//here we are because it has two black leaves

	Node* parent = M->parent;//it's correct for the root also
	Node*& reference_to_place = (parent->left == M ? parent->left : parent->right);
	reference_to_place = nil; //for root: nil -> root as right child (yet)

	//delete M;

	restoring_of_properties_after_removing(nil, parent);

	return M;
}

template <typename T>
void RedBlackTree<T>::restoring_of_properties_after_removing(Node* N, Node* P) {
	//https://ru.wikipedia.org/wiki/Красно-чёрное_дерево#Удаление

	//case 1
	if (N == root)
		return;

	Node* S = (P->left == N ? P->right : P->left); //sibling of N

	//case 2
	if (S->isRed()) {
		//P is black

		//std::swap(S->color, P->color);
		S->color = BLACK;
		P->color = RED;

		if (N == P->left)
			left_rotation(P);
		else
			right_rotation(P);
		std::swap(P, S);

		S = (P->left == N ? P->right : P->left);

		//P is red
		//S is black (old SL)
	}

	//case 3

	//S is not leaf, because M wasn't leaf (and P is not leaf too)
	Node* SL = S->left;
	Node* SR = S->right;

	if (P->isBlack() && S->isBlack() && SL->isBlack() && SR->isBlack()) {
		S->color = RED;
		restoring_of_properties_after_removing(P, P->parent);

		return;
	}

	//case 4
	if (P->isRed() && S->isBlack() && SL->isBlack() && SR->isBlack()) {
		//std::swap(S->color, P->color);
		P->color = BLACK;
		S->color = RED;

		return;
	}

	//case 5
	if (S->isBlack())
		if (SL->isRed() && SR->isBlack()) {
			if (N == P->left) {
				right_rotation(S);
				std::swap(S, SL);

				//std::swap(S->color, SL->color);
				S->color = RED;
				SL->color = BLACK;
			}
		}
		else if (SL->isBlack() && SR->isRed()) {
			if (N == P->right) {
				left_rotation(S);
				std::swap(S, SR);

				//std::swap(S->color, SL->color);
				S->color = RED;
				SR->color = BLACK;
			}
		}

	//case 6
	//if (S->isBlack() && SR->isRed())

	//std::swap(S->color, P->color);
	S->color = P->color;
	P->color = BLACK;

	if (N == P->left) {
		SR->color = BLACK;
		left_rotation(P);
	}
	else {
		SL->color = BLACK;
		right_rotation(P);
	}
}

template <typename T>
typename RedBlackTree<T>::Node* RedBlackTree<T>::get_the_most_left(Node* node) const {
	Node* temp = node;

	while (temp->left != nil)
		temp = temp->left;

	return temp;
}

template <typename T>
void RedBlackTree<T>::delete_tree(Node* node, Node* nil) {
	if (node == nil)
		return;

	delete_tree(node->left, nil);
	delete_tree(node->right, nil);

	delete node;
}

template <typename T>
typename RedBlackTree<T>::Node* RedBlackTree<T>::get_clone(const Node* node, const Node* nil, const Node* new_nil) {
	if (node == nil)
		return new_nil;

	Node* current = new Node(*node);

	current->left = get_clone(node->left, nil, new_nil);
	current->right = get_clone(node->right, nil, new_nil);

	return current;
}

template <typename T>
void RedBlackTree<T>::update_nil_pointers_to_root() {
	nil->left = nil->right = root;
}

template <typename T>
void RedBlackTree<T>::restoring_of_properties_after_inserting(Node* N)
{
	//https://ru.wikipedia.org/wiki/Красно-чёрное_дерево#Вставка

	//case 1
	if (N == root) {
		root->color = BLACK;
		return;
	}

	//N is not root => it has a parent

	//case 2
	Node* P = N->parent; //parent

	if (P->isBlack())
		return;

	//parent is red => it can't be root => it has a parent (N's grandparent)

	//case 3
	Node* G = P->parent; //grandparent (parent of a parent)
	Node* U = (G->left == P) ? G->right : G->left; //uncle (brother of a parent)

	if (U->isRed()) { //&& P->isRed()
		P->color = BLACK;
		U->color = BLACK;

		G->color = RED;

		restoring_of_properties_after_inserting(G);
		return;
	}

	//uncle is black

	//case 4

	if (N == P->right && P == G->left) { //N is right of P, P is left of a G
		left_rotation(P);
		std::swap(N, P);
	}
	else
		if (N == P->left && P == G->right) { //N is left of P, P is right of a G
			left_rotation(P);
			std::swap(N, P);
		}

	//case 5
	if (N == P->left)  // && P == G->left
		right_rotation(G);
	else
		left_rotation(G);

	G->color = RED;
	P->color = BLACK;

	//or call:
	//insert_case_1(N);
}

template <typename T>
void RedBlackTree<T>::left_rotation(Node* x) {
	bool is_x_root = (x == root) ? true : false;

	Node* y = x->right;
	Node* p = x->parent;

	x->right = y->left;
	if (x->right != nil) //has it sence ???
		x->right->parent = x;

	y->parent = p;
	(p->right == x ? p->right : p->left) = y;

	y->left = x;
	x->parent = y;

	if (is_x_root)
		root = y;
}

template <typename T>
void RedBlackTree<T>::right_rotation(Node* x) {
	bool is_x_root = (x == root) ? true : false;

	Node* y = x->left;
	Node* p = x->parent;

	x->left = y->right;
	if (x->left != nil) //has it sence ???
		x->left->parent = x;

	y->parent = p;
	(p->right == x ? p->right : p->left) = y;

	y->right = x;
	x->parent = y;

	if (is_x_root)
		root = y;
}

#endif //!_MY_RED_BLACK_TREE_HPP_