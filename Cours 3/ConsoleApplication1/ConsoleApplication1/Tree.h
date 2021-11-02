#pragma once

template<typename Type>
class Tree {
public :
	Type value;
	Tree* l;
	Tree* r;

	Tree(Type val) {
		value = val;
	}

	Tree* Insert(Tree* node, Type elem) {
		if (!node) return new Tree(elem);
		if (node->value < elem) {
			node->r = Insert(node->r, elem);
		}
		else {
			node->l = Insert(node->l, elem);
		}
		return node;
	}

	Tree* Search(Type o) {
		if (value == o)
			return this;
		else
			if (o < v)
			{
				if (l)	return l->Search(o);
				else	return nullptr;
			}
			else {
				if (r)	return r->Search(o);
				else	return nullptr;
			}

	}
};