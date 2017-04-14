/* ÷∂Ø ‰»Î
#include"AVLTreeClass.h"
#include<conio.h>
#include<iostream>
using namespace std;

void main() {
	int x=0;
	AvlTree at1;
	do{
		printf_s("\n----------------------------");
		printf_s("\nThis is your tree.");
		at1.listAll();
		x = -1;
		printf_s("\nThere are several selections, input number to use relevant function:\n1.Insert a number or a series of number to the tree.\n2.Remove a number or a series of number to the tree.\n3.Search for the Nth element in a ascending order.\n4.Clear it up, make it Empty.\n5.Check if tree contians the paticular element.\n6.Check how many element is less than the given one.\nPress ESC to Exit!");
		printf_s("\n----------------------------");
		switch (_getch()) {
		case 27:exit(0); break;
		case '1': {
			printf_s("\nPlease Input numbers separated with single \"space\" to insert:\n  ");
			char b = 0;
			while (b != '\r') {
				b = _getche();
				if (b >= '0'&&b <= '9') {
					if (x == -1)x = b - '0';
					else x = x * 10 + b - '0';
				}
				else if (b == ' ') {
					at1.insert(x);
					x = -1;
				}
				else if (b == 27)exit(0);
				else {
					printf_s("\b \b");
				}
			}
			if (b != ' ')at1.insert(x);
			
			printf_s("\nInsert completed!");
			break;
		}
		case '2': {
			printf_s("\nPlease Input numbers separated with single \"space\" to remove:\n  ");
			char b = 0;
			while (b != '\r') {
				b = _getche();
				
				if (b >= '0'&&b <= '9') {
					if (x == -1)x = b - '0';
					else x = x * 10 + b - '0';
				}
				else if (x != -1 && b == ' ') {
					at1.remove(x);
					x = -1;
				}
				else if (b == 27)exit(0);
				else {
					printf_s("\b \b");
				}
			}
			if (b != ' ')at1.remove(x);
			printf_s("\nRemove completed!");
			break;
		}
		case '3': {
			printf_s("\nPlease Input number n:");
			scanf_s("%d", &x);
			at1.search(x);
			printf_s("\nSearch over");
			break;
		}
		case '4': {
			at1.makeEmpty();
			printf_s("\nEmpty now.");
			break;
		}
		case '5': {
			printf_s("\nPlease Input number n:");
			scanf_s("%d", &x);
			at1.contians(x);
			break;
		}
		case '6': {
			printf_s("\nPlease Input number k:");
			scanf_s("%d", &x);
			int n = at1.numLessThanK(x);
			printf_s("\nThere is %d element less than %d", n, x);
			break;
		}
		default:printf_s("\nNothing done."); break;
		}
		printf_s("\n----------------------------");
		printf_s("\nPress Any Botton to continue...");
	} while (_getch()!=27);
}
*/