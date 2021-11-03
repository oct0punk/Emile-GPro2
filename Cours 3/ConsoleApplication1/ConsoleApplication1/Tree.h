

template<typename Type>
class Tree {
public:
	Type	value = {};
	Tree* left = nullptr;
	Tree* right = nullptr;

	Tree(Type val) {
		value = val;
	}

	Tree* Insert(Type newVal) {
		if (newVal <= value) {
			if (left)
				left->Insert(newVal);
			else
				left = new Tree(newVal);
		}
		else {
			if (right)
				right->Insert(newVal);
			else
				right = new Tree(newVal);
		}
		return this;
	}

	Tree* Merge(Tree* other) {
		Type vo = other->value;
		insert(vo);
		if (other->left) Merge(other->left);
		if (other->right) Merge(other->right);
		delete other;
		return this;
	}

	Tree* Remove(Type other) {
		if (value == other) {
			Tree* _l = left;
			Tree* _r = right;
			if (!left) {
				delete this;
				return _r;
			}
			else if (!right) {
				delete this;
				return _l;
			}
			else {
				left->Merge(right);
				delete this;
				return _l;
			}
		}
		else {
			if (other < value) {
				if (left)
					left = left->Remove(other);
			}
			else {
				if (right)
					right = right->Remove(other);
			}
			return this;
		}
	}

	Tree* Search(Type val) {
		if (value == val)
			return this;
		else
			if (val < value) {
				if (left)
					return left->Search(val);
				else
					return nullptr;
			}
			else//o>v -> part a droite
			{
				if (right)
					return right->Search(val);
				else
					return nullptr;
			}
	}

};