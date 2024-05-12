#include <iostream>
#include "redblack.h"
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	RedBlack * tree = new RedBlack();
	char op;
	int num;
	do{
		cout <<"Op: ";
		cin>>op;
		switch(op){
			case 'i':
				cin>>num;
				tree->insert(num);
				break;
			case 'p':
				tree->print();
				break;
			case 'x':
				cout <<"Exiting";
				break;
			default:
				cout<<"Invalid"<<endl;			
		}
	}while (op!='x');
	return 0;
}
