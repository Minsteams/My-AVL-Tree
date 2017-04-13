#pragma once
using namespace std;
class kdNode {
public:
	vector<int> data;
	kdNode *left;
	kdNode *right;
	bool isActive;
	kdNode(const vector<int> & theElement, kdNode*lt = NULL, kdNode*rt = NULL) :data(theElement), left(lt), right(rt), isActive(true) {}
};
class kdTree {
public:
	kdTree(int n);
	void insert(const vector<int> &x);
	bool contians(const vector<int> &x);
	void remove(const vector<int> &x);
	void listAll();
	void makeEmpty();
	void printRange(const vector<int>&low, const vector<int>&high);
	
private:
	void printRange(const vector<int>&low, const vector<int>&high, kdNode*t, int level);
	int nextLevel(int level);
	void makeEmpty(kdNode*&t);
	kdNode* contains(const vector<int> &x, kdNode *t, int level);
	void list(kdNode*&t, int depth)const;
	void insert(const vector<int> &x, kdNode *&t, int level);
	kdNode *root;
	int k;
};