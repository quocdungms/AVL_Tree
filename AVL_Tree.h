#pragma once
#include <iostream>


template <class T>
class AVL
{

public:
	class Node;

private:
	Node* root;
	int numOfNode;
public:
	AVL() {
		this->root = NULL;
		this->numOfNode = 0;
	}
	~AVL() {
		this->Clear(root);
	}
	
	int get_height_rec(Node* node);
	int get_balance_factor(Node* node);
	Node* insert(Node*& node, const T& element);
	void INSERT(const T& element);
	Node* remove(Node*& ndoe, const T& element);
	void REMOVE(const T& element);
	Node* search(const T& element);
	void SEARCH(const T& element);
	Node* get_root();
	Node* balance(Node* node);
	Node* ll_rotation(Node* parent);
	Node* rr_rotation(Node* parent);
	Node* lr_rotation(Node* parent);
	Node* rl_rotation(Node* parent);
	Node* max_node_rec(Node* node);
	Node* min_node_rec(Node* node);
	T MAX_NODE();
	T MIN_NODE();
	void printNLR(Node* node);
	void PRINT_NLR();
	void printLRN(Node* node);
	void PRINT_LRN();
	void display(Node* node, int level);
	void Clear(AVL::Node* node);

	public: class Node
	{
		
	protected:
		
		T data;
		Node* left;
		Node* right;
		friend class AVL<T>;

	public:
		Node() {
			this->data = 0;
			this->left = this->right = NULL;
		}
		Node(const T& data) {
			this->data = data;
			this->left = this->right = NULL;
		}
	};

};


template <class T>
void AVL<T>::Clear(Node* node) {
	if (node != NULL) {
		Clear(node->left);
		Clear(node->right);
		delete node;
	}
	node = NULL;
	numOfNode = 0;
}

template <class T>
int AVL<T>::get_height_rec(Node* node) {
	if (node == NULL)
		return 0;
	int left_height = get_height_rec(node->left);
	int right_height = get_height_rec(node->right);

	return left_height > right_height ? left_height + 1 : right_height + 1;
}

template <class T>
int AVL<T>::get_balance_factor(Node* node) {
	int left_height = get_height_rec(node->left);
	int right_height = get_height_rec(node->right);
	return left_height - right_height;
}


template <class T>
typename AVL<T>::Node* AVL<T>::balance(Node* node) {
	int balance_factor = get_balance_factor(node);

	if (balance_factor > 1) {
		if (get_balance_factor(node->left) > 0) {
			node = ll_rotation(node);
		}
		else {
			node = lr_rotation(node);
		}
	}
	else if (balance_factor < -1) {
		if (get_balance_factor(node->right) > 0) {
			node = rl_rotation(node);
		}
		else {
			node = rr_rotation(node);
		}
	}
	return node;
}

template <class T>
typename AVL<T>::Node* AVL<T>::ll_rotation(Node* parent) {
	Node* current;
	current = parent->left;
	parent->left = current->right;
	current->right = parent;

	return current;
}

template <class T>
typename AVL<T>::Node* AVL<T>::rr_rotation(Node* parent) {
	Node* current;
	current = parent->right;
	parent->right = current->left;
	current->left = parent;
	return current;
}


template <class T>
typename AVL<T>::Node* AVL<T>::lr_rotation(Node* parent) {
	Node* current;
	current = parent->left;
	parent->left = this->rr_rotation(current);
	return this->ll_rotation(parent);
}

template <class T>
typename AVL<T>::Node* AVL<T>::rl_rotation(Node* parent) {
	Node* current;
	current = parent->right;
	parent->right = this->ll_rotation(current);
	return this->rr_rotation(parent);
}

template <class T>
typename AVL<T>::Node* AVL<T>::search(const T& element) {
	Node* current = root;
	while (current != NULL)
	{
		if (current->data == element) {
			break;
		}
		element > current->data ? current = current->right : current = current->left;
	}
	return current;
}
template <class T>
void AVL<T>::SEARCH(const T& element) {
	this->search(element) != NULL ? std::cout << "\n" << element <<" was found\n" : std::cout << "\n" << element << " was not found\n";
}

template <class T>
typename AVL<T>::Node* AVL<T>::insert(Node *&node, const T& element) {
	if (node == NULL) {
		Node* temp = new Node(element);
		numOfNode++;
		node = temp;
		node->left = NULL;
		node->right = NULL;
		return node;
	}
	else if (node->data > element) {
		node->left = insert(node->left, element);
		node = balance(node);
	}
	else if (node->data <= element) {
		node->right = insert(node->right, element);
		node = balance(node);
	}
	
	return node;
}

template <class T>
void AVL<T>::INSERT(const T& element) {
	this->insert(root, element);
}

\
template <class T>
typename AVL<T>::Node* AVL<T>::remove(Node*& node, const T& element) {
	Node* temp = NULL;
	if (node == NULL) return NULL;
	else if (element > node->data) node->right = remove(node->right, element);
	else if (element < node->data) node->left = remove(node->left, element);
	// element found and has 2 children
	else if ( node->left != NULL && node->right != NULL)
	{
		// get min node of right sub-tree
		temp = this->min_node_rec(node->right);
		// assign data of current node to min
		node->data = temp->data;

		node->right = remove(node->right, node->data);
	}
	else
	{
		temp = node;
		if (node->left == NULL) node = node->right;
		else if (node->right == NULL) node = node->left;
		delete temp;
	}
	if (node == NULL) return node;
	node = this->balance(node);
	return node;
}

template <class T>
void AVL<T>::REMOVE(const T& element) {
	if (this->search(element) != NULL) {
		this->remove(root, element);
	}
	else this->SEARCH(element);
}


template <class T>
void AVL<T>::printNLR(Node* node)
{
	if (node == NULL) return;
	std::cout << node->data << " ";
	printNLR(node->left);
	printNLR(node->right);

}


template <class T>
void AVL<T>::PRINT_NLR()
{
	std::cout << "Num of node: " << this->numOfNode << std::endl;
	printNLR(this->root);
}


template <class T>
void AVL<T>::printLRN(Node* node)
{
	if (node == NULL) return;

	printLRN(node->left);
	printLRN(node->right);
	std::cout << node->data << " ";
	
}


template <class T>
void AVL<T>::PRINT_LRN()
{
	std::cout << "Num of node: " << this->numOfNode << std::endl;
	printLRN(this->root);
}


template <class T>
typename AVL<T>::Node* AVL<T>::get_root() {
	return this->root;
}


template <class T>
void AVL<T>::display(Node* node, int level) {
	
	int i;
	if (node != NULL)
	{
		display(node->right, level + 1);
		printf("\n");
		if (node == root)
			std::cout << "Root -> ";
		for (i = 0; i < level && node != root; i++)
			std::cout << "      ";
		std::cout << node->data;
		display(node->left, level + 1);
	}
}


template <class T>
typename AVL<T>::Node* AVL<T>::max_node_rec(Node* node) {
	if (node == NULL) {
		return NULL;
	}
	else if (node->right == NULL) {
		return node;
	}
	else {
		return max_node_rec(node->right);
	}
}


template <class T>
T AVL<T>::MAX_NODE() {
	return max_node_rec(root)->data;
}


template <class T>
typename AVL<T>::Node* AVL<T>::min_node_rec(Node* node) {
	if (node == NULL) {
		return NULL;
	}
	else if (node->left == NULL) {
		return node;
	}
	else {
		return min_node_rec(node->left);
	}
}


template <class T>
T AVL<T>::MIN_NODE() {
	return min_node_rec(root)->data;
}

