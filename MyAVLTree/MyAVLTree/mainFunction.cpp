#include<iostream>
#include"myFilePrint.h"
#include"AVLTreeClass.h"

using namespace std;

void main() {
	AvlTree at;
	FILE *in;
	fopen_s(&in, "in_avltree.txt", "r");
	if (in != NULL) {
		while (!feof(in)) {
			int temp;
			fscanf_s(in, "%d", &temp);
			at.insert(temp);
		}
		fclose(in);
	}
	FILE *out;
	remove("out_avltree.txt");
	fopen_s(&out, "out_avltree.txt", "w");
	mfprint(out,"----------------------------");
	mfprint(out,"\nThis is your tree.");
	at.listAll(out);
	fclose(out);
}