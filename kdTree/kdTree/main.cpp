#include"kdtree.h"
#include<conio.h>
using namespace std;

int k;
void initVector(vector<int> &tp) {
	tp.clear();
	for (int i = 0; i < k; i++) {
		tp.push_back(0);
	}
}
void inputVector(vector<int> &tp) {
	initVector(tp);
	int x = -1;
	char b = 0;
	bool input = false;
	int order = 0;
	while (b != '\r') {
		b = _getche();
		if (b == 27)exit(0);
		if (input) {
			if (b == ')') {
				if (order < k) tp[order++] = x;
				input = false;
				break;
			}
			else if (order == k) {
				printf_s("\b");
			}
			else if (b >= '0'&&b <= '9') {
				if (x == -1)x = b - '0';
				else x = x * 10 + b - '0';
			}
			else if (b == ',') {
				if (order < k) tp[order++] = x;
				x = -1;
			}
			else {
				printf_s("\b");
			}
		}
		else {
			if (b == '(') {
				printf_s("\b (");
				input = true;
				x = -1;
				order = 0;
			}
			else {
				printf_s("\b");
			}
		}
	}
}
void main() {
	int x = 0;	
	printf_s("Please input k:");
	scanf_s("%d", &k);
	kdTree<int> kt1(k);
	vector<int> tp;
	do {
		initVector(tp);
		printf_s("\n----------------------------");
		printf_s("\nThis is your tree.");
		kt1.listAll();
		x = -1;
		printf_s("\nThere are several selections, input number to use relevant function:\n1.Insert a number or a series of number to the tree.\n2.Remove a number or a series of number to the tree.\n3.Search for all datas in a given range.\n4.Clear it up, make it Empty.\n5.Check if tree contians the paticular element.\nPress ESC to Exit!");
		printf_s("\n----------------------------");
		switch (_getch()) {
		case 27:exit(0); break;
		case '1': {
			printf_s("\nPlease Input vector ");
			PrintVector(tp);
			printf_s(" like this to insert:\n  ");
			char b = 0;
			bool input = false;
			int order = 0;
			while (b != '\r') {
				b = _getche();
				if (b == 27)exit(0);
				if (input) {
					if (b == ')') {
						if (order < k) tp[order++] = x;
						input = false;
						kt1.insert(tp);
					}
					else if (order == k) {
						printf_s("\b");
					}
					else if (b >= '0'&&b <= '9') {
						if (x == -1)x = b - '0';
						else x = x * 10 + b - '0';
					}
					else if (b == ',') {
						if (order < k) tp[order++] = x;
						x = -1;
					}
					else {
						printf_s("\b");
					}
				}
				else {
					if (b == '(') {
						printf_s("\b (");
						input = true;
						initVector(tp);
						x = -1;
						order = 0;
					}
					else {
						printf_s("\b");
					}
				}
			}
			printf_s("\nInsert completed!");
			break;
		}
		case '2': {
			printf_s("\nPlease Input vector ");
			PrintVector(tp);
			printf_s(" like this to remove:\n  ");
			char b = 0;
			bool input = false;
			int order = 0;
			while (b != '\r') {
				b = _getche();
				if (b == 27)exit(0);
				if (input) {
					if (b == ')') {
						if (order < k) tp[order++] = x;
						input = false;
						kt1.remove(tp);
					}
					else if (order == k) {
						printf_s("\b");
					}
					else if (b >= '0'&&b <= '9') {
						if (x == -1)x = b - '0';
						else x = x * 10 + b - '0';
					}
					else if (b == ',') {
						if (order < k) tp[order++] = x;
						x = -1;
					}
					else {
						printf_s("\b");
					}
				}
				else {
					if (b == '(') {
						printf_s("\b (");
						input = true;
						initVector(tp);
						x = -1;
						order = 0;
					}
					else {
						printf_s("\b");
					}
				}
			}
			printf_s("\nRemove completed!");
			break;
		}
		case '3': {
			vector<int> low;
			printf_s("\nPlease Input 2 vector ");
			PrintVector(tp);
			PrintVector(tp);
			printf_s(" like this to search:  ");
			inputVector(low);
			inputVector(tp);
			printf_s("\nResult:\n");
			kt1.printRange(low, tp);
			printf_s("\nSearch over");
			break;
		}
		case '4': {
			kt1.makeEmpty();
			printf_s("\nEmpty now.");
			break;
		}
		case '5': {
			printf_s("\nPlease Input a vector ");
			PrintVector(tp);
			printf_s(" like this to check:  ");
			inputVector(tp);
			if (kt1.contians(tp))printf_s("\nFounded!");
			else printf_s("\nNot Founded.");
			break;
		}
		default:printf_s("\nNothing done."); break;
		}
		printf_s("\n----------------------------");
		printf_s("\nPress Any Botton to continue...");
	} while (_getch() != 27);
}