#pragma once
#include<iostream>
using namespace std;

template <typename Comparable>
class AvlTree {
public :
	AvlTree() :root(NULL) {

	}
	class AvlNode {
	public:
		Comparable element;
		AvlNode *left;
		AvlNode *right;
		int height;

		AvlNode(const Comparable & theElement, AvlNode*lt, AvlNode*rt, int h = 0) :element(theElement), left(lt), right(rt), height(h) {}
	};
	int height(AvlNode *t = root)const {
		return t == NULL ? -1 : t->height;
	}
	void insert(const Comparable &x) {
		insert(x, root);
	
	}
	void remove(const Comparable &x) {
		remove(x, root);
	}
	void listAll() {
		if (root == NULL) {
			printf_s("\nThis tree is EMPTY!");
		}
		else {
			listAll(root, 0);
		}
	}
	void makeEmpty() {
		makeEmpty(root);
	}
	void contians(const Comparable &x) {
		if (contains(x, root))printf_s("\nFounded!");
		else printf_s("\nNotFounded");
	}
	void search(int &k) {
		int n = 0;
		AvlNode *p = search(k, n, root);
		if (p == NULL)printf_s("\nError!");
		else {
			printf_s("The %dth element is %d, the tree node is:\n", k, p->element);
			listAll(p, 1);
		}
	}
private:
	AvlNode * search(int &k, int &n, AvlNode *&t)const {
		AvlNode *p = NULL;
		if (t->left != NULL) {
			p = search(k, n, t->left);
		}
		n++;
		if (n == k)p = t;
		if (p != NULL)return p;
		else
			if (t->right != NULL) {
				p = search(k, n, t->right);
			}
		return p;

	}
	bool contains(const Comparable &x,AvlNode *t)const {
		if (t == NULL)return false;
		else if (x < t->element)
			return contains(x, t->left);
		else if (t->element < x)
			return contains(x, t->right);
		else return true;
	}
	void makeEmpty(AvlNode*&t) {
		if (t != NULL) {
			makeEmpty(t->left);
			makeEmpty(t->right);;
			delete t;
			t = NULL;
		}
	}
	void insert(const Comparable &x, AvlNode *&t) {
		if (t == NULL) {
			t = new AvlNode(x, NULL, NULL);
		}
		else if (x < t->element) {
			insert(x, t->left);
			if (height(t->left) - height(t->right) == 2) {
				if (x < t->left->element)rotateWithLeftChild(t);
				else doubleWithLeftChild(t);
			}
		}
		else if (t->element < x) {
			insert(x, t->right);
			if (height(t->left) - height(t->right) == -2) {
				if (t->right->element<x)rotateWithRightChild(t);
				else doubleWithRightChild(t);
			}
		}
		else {
			//рясп
		}
		t->height = max(height(t->left), height(t->right)) + 1;
	}
	void remove(const Comparable &x, AvlNode *&t) {
		if (t != NULL) {
			if (x < t->element) {
				remove(x, t->left);
				if (height(t->left) - height(t->right) == -2) {
					if (height(t->right) - height(t->right->left)>=2)rotateWithRightChild(t);
					else doubleWithRightChild(t);
				}
			}
			else if (t->element < x) {
				remove(x, t->right);
				if (height(t->left) - height(t->right) == 2) {
					if (height(t->left) - height(t->left->right)>=2)rotateWithLeftChild(t);
					else doubleWithLeftChild(t);
				}
			}
			else {
				if (t->right != NULL) {
					AvlNode *oldNode = t;
					t = findMinAndRemove(t->right);
					t->left = oldNode->left;
					if (t == oldNode->right)t->right = NULL;
					else
					t->right = oldNode->right;
					delete oldNode;
				}
				else if (t->left != NULL) {
					AvlNode *oldNode = t;
					t = findMaxAndRemove(t->left);
					t->left = oldNode->left;
					if (t == oldNode->left)t->left = NULL;
					else
					t->right = oldNode->right;
					delete oldNode;
				}
				else {
					delete t;
					t = NULL;
				}
			}
			if(t!=NULL)
			t->height = max(height(t->left), height(t->right)) + 1;
		}
	}
	void listAll(AvlNode*&t, int depth)const {
		if (t != NULL) {
			listAll(t->right, depth + 1);
			printf_s("\n");
			for (int i = 0; i < depth; i++) {
				printf_s("    ");
			}
			if (depth > 0)
				printf_s("--");

			printf_s("%2d", t->element);
			listAll(t->left, depth + 1);
		}
	}
	AvlNode* findMinAndRemove(AvlNode*t) {
		AvlNode*p;
		if (t->left == NULL) {
			p = t;
		}
		else {
			p = findMinAndRemove(t->left);
			if (t->left == p) {
				t->left = p->right;
			}
			if (height(t->left) - height(t->right) == -2) {
				if (height(t->right)-height(t->right->left)>=2)rotateWithRightChild(t);
				else doubleWithRightChild(t);
			}
		}
		t->height = max(height(t->left), height(t->right)) + 1;
		return p;
	}
	AvlNode* findMaxAndRemove(AvlNode*t) {
		AvlNode*p;
		if (t->right == NULL) {
			p = t;
		}
		else {
			p = findMaxAndRemove(t->left);
			if (t->right == p) {
				t->right = p->left;
			}
			if (height(t->left) - height(t->right) == 2) {
				if (height(t->left) - height(t->left->right)>=2)rotateWithLeftChild(t);
				else doubleWithLeftChild(t);
			}
		}
		t->height = max(height(t->left), height(t->right)) + 1;
		return p;
	}
	void rotateWithLeftChild(AvlNode * & k2) {
		AvlNode*k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;
		k2->height = max(height(k2->left), height(k2->right)) + 1;
		k1->height = max(height(k1->left), k2->height) + 1;
		k2 = k1;
	}
	void rotateWithRightChild(AvlNode * & k2) {
		AvlNode*k1 = k2->right;
		k2->right = k1->left;
		k1->left = k2;
		k2->height = max(height(k2->left), height(k2->right)) + 1;
		k1->height = max(height(k1->left), k2->height) + 1;
		k2 = k1;
	}
	void doubleWithLeftChild(AvlNode * & k3) {
		rotateWithRightChild(k3->left);
		rotateWithLeftChild(k3);
	}
	void doubleWithRightChild(AvlNode * & k3) {
		rotateWithLeftChild(k3->right);
		rotateWithRightChild(k3);
	}
	AvlNode *root;
};
int max(int a, int b) {
	return a < b ? b : a;
}