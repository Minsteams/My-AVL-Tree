#include<iostream>
#include"AVLTreeClass.h"
#include"myFilePrint.h"

AvlTree::AvlTree() :root(NULL) {

}

int AvlTree::height(AvlNode *t)const {
	if (t == (AvlNode*)-1)t = root;
	return t == NULL ? -1 : t->height;
}
void AvlTree::insert(const int &x) {
	insert(x, root);
}
void AvlTree::remove(const int &x) {
	remove(x, root);
}
void AvlTree::listAll(FILE*fp) {
	mfprint(fp,"\n----------------------------");
	if (root == NULL) {
		mfprint(fp,"\nThis tree is EMPTY!");
	}
	else {
		list(root, 0,fp);
	}
	mfprint(fp,"\n----------------------------");
}
void AvlTree::list(AvlNode*&t, int depth,FILE*fp)const {
	if (t != NULL) {
		list(t->right, depth + 1,fp);
		mfprint(fp,"\n");
		for (int i = 0; i < depth; i++) {
			mfprint(fp,"    ");
		}
		if (depth > 0)
			mfprint(fp,"--");

		mfprint(fp,"%2d", t->element);
		list(t->left, depth + 1,fp);
	}
}
void AvlTree::makeEmpty() {
	makeEmpty(root);
}
void AvlTree::contians(const int &x, FILE*fp) {
	if (contains(x, root))mfprint(fp,"\nFounded!");
	else mfprint(fp, "\nNotFounded");
}
void AvlTree::search(int &k, FILE*fp) {
	int n = 0;
	AvlNode *p = search(k, n, root);
	if (p == NULL)mfprint(fp, "\nError!");
	else {
		mfprint(fp, "The %dth element is %d, the tree node is:\n", k, p->element);
		list(p, 1);
	}
}
int AvlTree::numLessThanK(int &k) {
	int n = 0;
	if (root != NULL)
		numLessThanK(k, n, root);
	return n;
}
void AvlTree::numLessThanK(int &k, int &n, AvlNode *&t)const {
	if (t->element < k) {
		n++;
		if (t->right != NULL)numLessThanK(k, n, t->right);
	}
	if (t->left != NULL) {
		numLessThanK(k, n, t->left);
	}
}
AvlNode * AvlTree::search(int &k, int &n, AvlNode *&t)const {
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
bool AvlTree::contains(const int &x, AvlNode *t)const {
	if (t == NULL)return false;
	else if (x < t->element)
		return contains(x, t->left);
	else if (t->element < x)
		return contains(x, t->right);
	else return true;
}
void AvlTree::makeEmpty(AvlNode*&t) {
	if (t != NULL) {
		makeEmpty(t->left);
		makeEmpty(t->right);;
		delete t;
		t = NULL;
	}
}
void AvlTree::insert(const int &x, AvlNode *&t) {
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
			if (t->right->element < x)rotateWithRightChild(t);
			else doubleWithRightChild(t);
		}
	}
	else {
		//рясп
	}
	t->height = max(height(t->left), height(t->right)) + 1;
}
void AvlTree::remove(const int &x, AvlNode *&t) {
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
		if (t != NULL)
			t->height = max(height(t->left), height(t->right)) + 1;
	}
}
AvlNode* AvlTree::findMinAndRemove(AvlNode*t) {
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
			if (height(t->right) - height(t->right->left) >= 2)rotateWithRightChild(t);
			else doubleWithRightChild(t);
		}
	}
	t->height = max(height(t->left), height(t->right)) + 1;
	return p;
}
AvlNode* AvlTree::findMaxAndRemove(AvlNode*t) {
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
			if (height(t->left) - height(t->left->right) >= 2)rotateWithLeftChild(t);
			else doubleWithLeftChild(t);
		}
	}
	t->height = max(height(t->left), height(t->right)) + 1;
	return p;
}
void AvlTree::rotateWithLeftChild(AvlNode * & k2) {
	AvlNode*k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(height(k1->left), k2->height) + 1;
	k2 = k1;
}
void AvlTree::rotateWithRightChild(AvlNode * & k2) {
	AvlNode*k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;
	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(height(k1->left), k2->height) + 1;
	k2 = k1;
}
void AvlTree::doubleWithLeftChild(AvlNode * & k3) {
	rotateWithRightChild(k3->left);
	rotateWithLeftChild(k3);
}
void AvlTree::doubleWithRightChild(AvlNode * & k3) {
	rotateWithLeftChild(k3->right);
	rotateWithRightChild(k3);
}
int max(int a, int b) {
	return a < b ? b : a;
}