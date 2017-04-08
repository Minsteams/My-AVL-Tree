#pragma once
#include<iostream>
#include<vector>
using namespace std;

template <typename Comparable>
void PrintVector(vector<Comparable> v) {
	printf_s("(");
	for (int i = 0; i < v.size(); i++) {
		printf_s("%d,", v[i]);
	}
	printf_s("\b)");
}
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
		bool isActive;
		kdNode(const vector<Comparable> & theElement, kdNode*lt=NULL, kdNode*rt=NULL) :data(theElement), left(lt), right(rt),isActive(true){}
	};
	void insert(const vector<Comparable> &x) {
		insert(x, root,0);
	}

	bool contians(const vector<Comparable> &x) {
		kdNode *p = contains(x, root, 0);
		return p == NULL ? false : true;
	}

	void remove(const vector<Comparable> &x) {
		kdNode *p = contains(x, root, 0);
		if (p != NULL)p->isActive = false;
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

	void makeEmpty() {
		makeEmpty(root);
	}
	void printRange(const vector<Comparable>&low, const vector<Comparable>&high) {
		printRange(low, high, root, 0);
	}
	
private:
	void printRange(const vector<Comparable>&low, const vector<Comparable>&high, kdNode*t, int level) {
		if (t != NULL) {
			int nl = nextLevel(level);
			bool isIn = true;
			for (int i = 0; i < k; i++) {
				if (low[i] > t->data[i] || high[i] < t->data[i])isIn = false;
			}
			if (isIn)PrintVector(t->data);

			if (low[level] <= t->data[level])
				printRange(low, high, t->left, nl);
			if (high[level] >= t->data[level])
				printRange(low, high, t->right, nl);
		}
	}
	int nextLevel(int level) {
		int nextL = level + 1;
		if (nextL == k)nextL = 0;
		return nextL;
	}
	void makeEmpty(kdNode*&t) {
		if (t != NULL) {
			makeEmpty(t->left);
			makeEmpty(t->right);;
			delete t;
			t = NULL;
		}
	}
	kdNode* contains(const vector<Comparable> &x, kdNode *t, int level) {
		int nl = nextLevel(level);
		if (t == NULL)return false;
		else if (x[level] < t->data[level])
			return contains(x, t->left, nl);
		else if (t->data[level] < x[level])
			return contains(x, t->right, nl);
		else if (x == t->data) return t;
		else return contains(x, t->right, nl);
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

			if (t->isActive == true)PrintVector(t->data);
			list(t->left, depth + 1);
		}
	}
	void insert(const vector<Comparable> &x, kdNode *&t, int level) {
		int nl = nextLevel(level);
		if (t == NULL)
			t = new kdNode(x);
		else if (x[level] < t->data[level])
			insert(x, t->left, nl);
		else if (x == t->data)t->isActive = true;
		else
			insert(x, t->right, nl);
	}
	kdNode *root;
	int k;
};