#ifndef _MY_RED_BLACK_TREE_

#define _MY_RED_BLACK_TREE_

#include <utility>

#include "Node.hpp"
#include "Iterator.hpp"

//visualisation:
//https://www.cs.usfca.edu/~galles/visualization/RedBlack.html

template <typename T>
class RedBlackTree
{
public:
	using Iterator = Iterator<T>;
	using Node = Node<T>;

	RedBlackTree();

	RedBlackTree(const RedBlackTree& other);
	RedBlackTree(RedBlackTree&& other);

	~RedBlackTree();

	RedBlackTree& operator=(const RedBlackTree& other);
	RedBlackTree& operator=(RedBlackTree&& other);

	Iterator begin();
	Iterator end();

	Iterator begin() const;
	Iterator end() const;

	void clear();
	bool insert(T value);
	bool remove(T value);

private:
	//insert in non-empty tree (without balancing)
	bool insert(Node*& node, Node* parent, T value, Node*& new_node);

	//remove node from tree (with balancing)
	bool remove(Node*& node, T value);

	Node* remove_node_with_2_children(Node* node); 
	Node* remove_node_with_0_or_1_child(Node* node);

	static void delete_tree(Node* temp_node, Node* nil);

	static Node* get_clone(const Node* temp_node, const Node* nil, const Node* new_nil);
	void update_nil_pointers_to_root();

	void restoring_of_properties_after_inserting(Node* N);
	void restoring_of_properties_after_removing(Node* N, Node* P);

	void left_rotation(Node* x);
	void right_rotation(Node* x);

	Node* get_the_most_left(Node* node) const;
private:
	Node* const nil;
	Node* root;

	static const typename Node::Color BLACK = Node::BLACK;
	static const typename Node::Color RED = Node::RED;
};

#endif //!_MY_RED_BLACK_TREE_