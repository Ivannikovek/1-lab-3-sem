#ifndef _MY_NODE_

#define _MY_NODE_

template <typename T>
struct Node {
	enum class Color { black, red };

	Node(const T& value, Color color /*= true*/, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr);

	T value;

	bool isBlack() const;
	bool isRed() const;

	Node* parent;
	Node* left;
	Node* right;

	static const Color BLACK = Color::black;
	static const Color RED = Color::red;

	Color color;
};

#endif //!_MY_NODE_