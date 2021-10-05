#pragma once

struct Branch {
	int value;
	Branch* ptr;
	Branch* left = nullptr;
	Branch* right = nullptr;
	
	Branch(Branch* ptr, int val) {
		this->ptr = ptr;
		value = val;
	}

	void SetLeft(int val) {
		if (left == nullptr) {
			left = (Branch*)malloc(sizeof(Branch));
			left->ptr = left;
		}
		left->value = val;
	}

	void SetRight(int val) {
		if (right == nullptr) {
			right = (Branch*)malloc(sizeof(Branch));
			right->ptr = right;
		}
		right->value = val;
	}
};

Branch* CreateBinaryTree(int val) {
	Branch* root = (Branch*)malloc(sizeof(Branch));
	root->value = val;
	root->left = nullptr;
	root->right = nullptr;
	return root;
}