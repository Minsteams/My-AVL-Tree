#pragma once


class AvlNode {
public:
	int element;
	AvlNode *left;
	AvlNode *right;
	int height;

	AvlNode(const int & theElement, AvlNode*lt, AvlNode*rt, int h = 0) :element(theElement), left(lt), right(rt), height(h) {}
};
class AvlTree {
public :
	AvlTree();
	int height(AvlNode *t= (AvlNode*)-1)const;
	void insert(const int &x);
	void remove(const int &x);
	void listAll(FILE *fp=NULL);
	void list(AvlNode*&t, int depth,FILE*fp=NULL)const;
	void makeEmpty();
	void contians(const int &x, FILE*fp = NULL);
	void search(int &k, FILE*fp = NULL);
	int numLessThanK(int &k);
private:
	void numLessThanK(int &k, int &n, AvlNode *&t)const;
	AvlNode * search(int &k, int &n, AvlNode *&t)const;
	bool contains(const int &x, AvlNode *t)const;
	void makeEmpty(AvlNode*&t);
	void insert(const int &x, AvlNode *&t);
	void remove(const int &x, AvlNode *&t);
	AvlNode* findMinAndRemove(AvlNode*t);
	AvlNode* findMaxAndRemove(AvlNode*t);
	void rotateWithLeftChild(AvlNode * & k2);
	void rotateWithRightChild(AvlNode * & k2);
	void doubleWithLeftChild(AvlNode * & k3);
	void doubleWithRightChild(AvlNode * & k3);
	AvlNode *root;
};
int max(int a, int b);