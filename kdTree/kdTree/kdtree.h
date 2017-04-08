#pragma once
#include<iostream>
#include<vector>
using namespace std;

template <typename Comparable>
class kdTree {
public:
	kdTree(int n) :root(NULL),k(n) {

	}
	class kdNode {
	public:
		vector<Comparable> data;
		kdNode *left;
		kdNode *right;
		kdNode(const vector<Comparable> & theElement, kdNode*lt, kdNode*rt, int h = 0) :element(theElement), left(lt), right(rt){}
	};
	void insert(const Comparable &x) {
		insert(x, root);
	}
	void remove(const Comparable &x) {
		remove(x, root);
	}
	void listAll() {
		printf_s("\n----------------------------");
		if (root == NULL) {
			printf_s("\nThis tree is EMPTY!");
		}
		else {
			list(root, 0);
		}
		printf_s("\n----------------------------");
	}
	void list(kdNode*&t, int depth)const {
		if (t != NULL) {
			list(t->right, depth + 1);
			printf_s("\n");
			for (int i = 0; i < depth; i++) {
				printf_s("    ");
			}
			if (depth > 0)
				printf_s("--");

			printf_s("%2d", t->element);
			list(t->left, depth + 1);
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
		kdNode *p = search(k, n, root);
		if (p == NULL)printf_s("\nError!");
		else {
			printf_s("The %dth element is %d, the tree node is:\n", k, p->element);
			list(p, 1);
		}
	}
	int numLessThanK(int &k) {
		int n = 0;
		if (root != NULL)
			numLessThanK(k, n, root);
		return n;
	}
private:
	void numLessThanK(int &k, int &n, kdNode *&t)const {
		if (t->element < k) {
			n++;
			if (t->right != NULL)numLessThanK(k, n, t->right);
		}
		if (t->left != NULL) {
			numLessThanK(k, n, t->left);
		}
	}
	kdNode * search(int &k, int &n, kdNode *&t)const {
		kdNode *p = NULL;
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
	bool contains(const Comparable &x, kdNode *t)const {
		if (t == NULL)return false;
		else if (x < t->element)
			return contains(x, t->left);
		else if (t->element < x)
			return contains(x, t->right);
		else return true;
	}
	void makeEmpty(kdNode*&t) {
		if (t != NULL) {
			makeEmpty(t->left);
			makeEmpty(t->right);;
			delete t;
			t = NULL;
		}
	}
	void insert(const Comparable &x, kdNode *&t) {
		if (t == NULL) {
			t = new kdNode(x, NULL, NULL);
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
	void remove(const Comparable &x, kdNode *&t) {
		if (t != NULL) {
			if (x < t->element) {
				remove(x, t->left);
				if (height(t->left) - height(t->right) == -2) {
					if (height(t->right) - height(t->right->left) >= 2)rotateWithRightChild(t);
					else doubleWithRightChild(t);
				}
			}
			else if (t->element < x) {
				remove(x, t->right);
				if (height(t->left) - height(t->right) == 2) {
					if (height(t->left) - height(t->left->right) >= 2)rotateWithLeftChild(t);
					else doubleWithLeftChild(t);
				}
			}
			else {
				if (t->right != NULL) {
					kdNode *oldNode = t;
					t = findMinAndRemove(t->right);
					t->left = oldNode->left;
					if (t == oldNode->right)t->right = NULL;
					else
						t->right = oldNode->right;
					delete oldNode;
				}
				else if (t->left != NULL) {
					kdNode *oldNode = t;
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
			if (t != NULL)
				t->height = max(height(t->left), height(t->right)) + 1;
		}
	}
	kdNode* findMinAndRemove(kdNode*t) {
		kdNode*p;
		if (t->left == NULL) {
			p = t;
		}
		else {
			p = findMinAndRemove(t->left);
			if (t->left == p) {
				t->left = p->right;
			}
			if (height(t->left) - height(t->right) == -2) {
				if (height(t->right) - height(t->right->left) >= 2)rotateWithRightChild(t);
				else doubleWithRightChild(t);
			}
		}
		t->height = max(height(t->left), height(t->right)) + 1;
		return p;
	}
	kdNode* findMaxAndRemove(kdNode*t) {
		kdNode*p;
		if (t->right == NULL) {
			p = t;
		}
		else {
			p = findMaxAndRemove(t->left);
			if (t->right == p) {
				t->right = p->left;
			}
			if (height(t->left) - height(t->right) == 2) {
				if (height(t->left) - height(t->left->right) >= 2)rotateWithLeftChild(t);
				else doubleWithLeftChild(t);
			}
		}
		t->height = max(height(t->left), height(t->right)) + 1;
		return p;
	}
	void rotateWithLeftChild(kdNode * & k2) {
		kdNode*k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;
		k2->height = max(height(k2->left), height(k2->right)) + 1;
		k1->height = max(height(k1->left), k2->height) + 1;
		k2 = k1;
	}
	void rotateWithRightChild(kdNode * & k2) {
		kdNode*k1 = k2->right;
		k2->right = k1->left;
		k1->left = k2;
		k2->height = max(height(k2->left), height(k2->right)) + 1;
		k1->height = max(height(k1->left), k2->height) + 1;
		k2 = k1;
	}
	void doubleWithLeftChild(kdNode * & k3) {
		rotateWithRightChild(k3->left);
		rotateWithLeftChild(k3);
	}
	void doubleWithRightChild(kdNode * & k3) {
		rotateWithLeftChild(k3->right);
		rotateWithRightChild(k3);
	}
	kdNode *root;
	int k;
};
int max(int a, int b) {
	return a < b ? b : a;
}