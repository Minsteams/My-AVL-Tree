#include<iostream>
#include<vector>
#include"kdtree.h"
#include"myFilePrint.h"
using namespace std;

extern void PrintVector(vector<int> &v, FILE *fp = NULL);
kdTree::kdTree(int n) :root(NULL), k(n) {

}

void kdTree::insert(const vector<int> &x) {
	insert(x, root, 0);
}

bool kdTree::contians(const vector<int> &x) {
	kdNode *p = contains(x, root, 0);
	return p == NULL ? false : true;
}

void kdTree::remove(const vector<int> &x) {
	kdNode *p = contains(x, root, 0);
	if (p != NULL)p->isActive = false;
}
void kdTree::listAll(FILE *fp) {
	mfprint(fp,"\n----------------------------");
	if (root == NULL) {
		mfprint(fp,"\nThis tree is EMPTY!");
	}
	else {
		list(root, 0,fp);
	}
	mfprint(fp,"\n----------------------------");
}

void kdTree::makeEmpty() {
	makeEmpty(root);
}
void kdTree::printRange(const vector<int>&low, const vector<int>&high) {
	printRange(low, high, root, 0);
}
void kdTree::printRange(const vector<int>&low, const vector<int>&high, kdNode*t, int level) {
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
int kdTree::nextLevel(int level) {
	int nextL = level + 1;
	if (nextL == k)nextL = 0;
	return nextL;
}
void kdTree::makeEmpty(kdNode*&t) {
	if (t != NULL) {
		makeEmpty(t->left);
		makeEmpty(t->right);;
		delete t;
		t = NULL;
	}
}
kdNode* kdTree::contains(const vector<int> &x, kdNode *t, int level) {
	int nl = nextLevel(level);
	if (t == NULL)return false;
	else if (x[level] < t->data[level])
		return contains(x, t->left, nl);
	else if (t->data[level] < x[level])
		return contains(x, t->right, nl);
	else if (x == t->data) return t;
	else return contains(x, t->right, nl);
}
void kdTree::list(kdNode*&t, int depth, FILE *fp)const {
	if (t != NULL) {
		list(t->right, depth + 1,fp);
		mfprint(fp,"\n");
		for (int i = 0; i < depth; i++) {
			mfprint(fp,"    ");
		}
		if (depth > 0)
			mfprint(fp,"--");

		if (t->isActive == true)PrintVector(t->data,fp);
		list(t->left, depth + 1,fp);
	}
}
void kdTree::insert(const vector<int> &x, kdNode *&t, int level) {
	int nl = nextLevel(level);
	if (t == NULL)
		t = new kdNode(x);
	else if (x[level] < t->data[level])
		insert(x, t->left, nl);
	else if (x == t->data)t->isActive = true;
	else
		insert(x, t->right, nl);
}