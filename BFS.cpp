#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>

struct Node {
	int value;
	Node* left;
	Node* right;
	Node* parent {nullptr};
	Node(int value_, Node* left_ = nullptr, Node* right_ = nullptr) : value(value_), left(left_), right(right_) {}
	void setParent(Node* parent_)
	{
		parent = parent_;
	}
};

class binaryTree
{
	Node* root;
public:

	binaryTree(Node* root_) : root(root_) {}

	void insert(int val)
	{
		insert(root, val);
	}

	bool search(int val) {
		return search(root, val);
	}

	bool is_binary_tree() {
		std::vector<int> vec;
		is_binary_tree(root, vec);

		if (std::is_sorted(vec.begin(), vec.end())) return true;
		return false;
	}

	int find_min()
	{
		return find_min_private(root);
	}

	int find_max()
	{
		return find_max_private(root);
	}

	void print() {
		print(root);
	}

	void delete_val(int val) {
		delete_val(root, val, 0);
	}

	void swap_tree()
	{
		swap_tree(root);
	}

	void swap_tree_iteratively()
	{
		swap_tree_iteratively(root);
	}

private:
	void insert(Node* root, int val) {
		if (!root) {
			root = new Node(val);
			return;
		}
		if (val < root->value && !root->left) {
			root->left = new Node(val);
			root->left->setParent(root);
			return;
		}
		if (val >= root->value && !root->right) {
			root->right = new Node(val);
			root->right->setParent(root);
			return;
		}

		if (val < root->value && root->left) {
			insert(root->left, val);
		}
		else {
			insert(root->right, val);
		}
	}

	bool search(Node* root, int val) {
		if (!root) {
			return false;
		}
		if (root->value == val) {
			return true;
		}
		if (val < root->value) {
			return search(root->left, val);
		}
		else {
			return search(root->right, val);
		}
	}

	void is_binary_tree(Node* root, std::vector<int>& vec) {
		if (root->left) {
			is_binary_tree(root->left, vec);
		}
		vec.push_back(root->value);
		if (root->right) {
			is_binary_tree(root->right, vec);
		}
	}

	int find_min_private(Node* root)
	{
		if (!root->left)
			return root->value;
		if (root->left)
			return find_min_private(root->left);
	}

	int find_max_private(Node* root)
	{
		if (!root->right)
			return root->value;
		if (root->right)
			return find_max_private(root->right);
	}

	void print(Node* root) {
		if (!root)
			return;
		if (root->left) {
			print(root->left);
		}
		std::cout << root->value << "  ";
		if (root->right) {
			print(root->right);
		}
	}

	void delete_val(Node* root, int val, bool left_child)
	{
		if (!root)
			return;
		if (root->value == val) {
			// case 1: 
			if (!root->left && !root->right)
			{
				if (left_child)
					root->parent->left = nullptr;
				else
					root->parent->right = nullptr;
				delete root;
				return;
			}
			// case 2: when node has only right child
			else if (!root->left)
			{
				if (left_child)
				{
					root->parent->left = root->right;
					root->right->parent = root->parent;
				}
					
				else
				{
					root->parent->right = root->right;
					root->right->parent = root->parent;
				}
				delete root;
				return;
			}
			// case 2: when node has only left child
			else if (!root->right)
			{
				if (left_child)
				{
					root->parent->left = root->left;
					root->left->parent = root->parent;
				}
				else
				{
					root->parent->right = root->left;
					root->left->parent = root->parent;
				}
				delete root;
				return;
			}
			// case 3: node has 2 children
			else
			{
				int min_node_value = find_min_private(root->right);
				root->value = min_node_value;
				delete_val(root->right, min_node_value, false);
				return;
			}
		}
		else if (root->value > val)
			delete_val(root->left, val, true);
		else
			delete_val(root->right, val, false);
	}

	void swap_tree(Node* root)
	{
		if (!root)
			return;
		std::swap(root->left, root->right);
		swap_tree(root->left);
		swap_tree(root->right);
	}

	void swap_tree_iteratively(Node* root)
	{
		std::queue<Node*> queue;
		if(root)
			queue.push(root);
		while (!queue.empty())
		{
			auto front = queue.front();
			std::swap(front->left, front->right);
			if (front->left)
				queue.push(front->left);
			if (front->right)
				queue.push(front->right);
			queue.pop();
		}
	}
};

int main()
{
	Node* node21 = new Node(21);
	Node* node36 = new Node(36);
	Node* node18 = new Node(18);
	Node* node24 = new Node(24, node21);
	Node* node35 = new Node(35, nullptr, node36);
	Node* node40 = new Node(40);
	Node* node20 = new Node(20, node18, node24);
	Node* node38 = new Node(38, node35, node40);
	Node* node34 = new Node(34, node20, node38);
	node21->setParent(node24);
	node36->setParent(node35);
	node18->setParent(node20);
	node24->setParent(node20);
	node35->setParent(node38);
	node40->setParent(node38);
	node20->setParent(node34);
	node38->setParent(node34);
	binaryTree bTree(node34);
	bTree.print();
	std::cout << '\n';
	bTree.delete_val(38);
	bTree.delete_val(35);
	bTree.delete_val(34);
	bTree.delete_val(27);
	bTree.swap_tree_iteratively();
	bTree.print();
	return 0;
}
