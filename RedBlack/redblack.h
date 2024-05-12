#include"node.h"
#include<iostream>
using namespace std;

class RedBlack{
	node * root;
	int size;
	
	node * create_node (int num, node * p, bool isRed){
		node * n = new node;
		n->elem =  num;
		n->left = NULL;
		n->right = NULL;
		n->parent = p;
		n->isRed = isRed;	
		size++;
		return n;
	}
	public:
	RedBlack(){
		root = NULL;
		size = 0;
	}
	void insert(int num){
		node * n = create_node(num, NULL, true);
		if(!root){
			root = n;
			root->isRed = false;
			return;
		}
		
		insertNode(root, n);
		node * z = n->parent->parent;
		if(!z){
			cout<<"";
		}else{
			checkDoubleRed(n);
		}
	}
    node * insertNode(node * currNode, node * newNode){
        if(currNode->elem<newNode->elem){
			if(!currNode->right){
				currNode->right = newNode;
				newNode->parent = currNode;
			}else{
				insertNode(currNode->right, newNode);
			}
		}else if(currNode->elem>newNode->elem){
			if(!currNode->left){
				currNode->left = newNode;
				newNode->parent = currNode;
			}else{
				insertNode(currNode->left, newNode);
			}
		}
        return currNode;
    }

    void checkDoubleRed(node *x){
        node *y = x->parent;
        node *z = y ? y->parent : nullptr;
        
        if (!y || !z || !(x->isRed && y->isRed)){
            return;
        }
        cout << "Checking Double Red";
        node *s = (z->left == y) ? z->right : z->left; //saving the sibling of y using z
        if (!s || !s->isRed) { //a must (!s->isRed)TTT mao ni ako gikadugayanTTT this checking ra
            cout << " - Restructure" << endl;
            trinode_restructure(x, y, z);
        } else {
            cout << " - Recolored" << endl;
            //perform the recoloring: make y, s as black; z as red; (by default x is red)
            recolor(y, z, s);
        }
    }
	void trinode_restructure(node *x, node *y, node *z){ // s is black
		//perform trinode restructuring make b as black; a, c as red
	     if((z->right==y )&& (y->right==x)){
            	cout<<" ZIGLEFT"<<endl;
	     	zigLeft(y, z, z->parent);
            	x->isRed = true;
            	y->isRed = false;
	     }else if((z->left==y )&& (y->left==x)){
            	cout<<" ZIGRIGHT"<<endl;
	     	zigRight(y, z, z->parent);
             	x->isRed = true;
             	y->isRed = false;
	     }else if((z->right==y )&& (y->left==x)){
            	cout<<" ZIGZAGLEFT"<<endl;
	     	zigRight(x, y, z);
		zigLeft(x, z, z->parent);
            	x->isRed = false;
            	y->isRed = true;
	     }else if((z->left==y )&& (y->right==x)){
            	cout<<" ZIGZAGRIGHT"<<endl;
            	zigLeft(x, y, z);
            	zigRight(x, z, z->parent);
            	x->isRed = false;
            	y->isRed = true;
	     }   
         	z->isRed = true;    
	}
    void recolor(node *y, node *z, node *s){
        if(s) {
            s->isRed = false;
        }
		y->isRed = false;
        if(z!=root){
            z->isRed = true;
            checkDoubleRed(z); //epasulod ni siya hereTTTTT utro sd ni do
        }
	}
	void zigLeft(node * n, node * par, node * gpar){
        node * temp = n->left; //place to store parent

        //relinking
	n->left = par;
        par->parent = n;
        par->right = temp; // move the temp

        if(temp){
            temp->parent = par;
        }
        if(!gpar){ //no grandparent
            root = n;
        }else{
            (gpar->left==par? gpar->left:gpar->right) = n;
            n->parent = gpar;
        }  
	}
	void zigRight(node *n, node * par, node * gpar){
        node * temp = n->right; //place to store parent

        //relinking
		n->right = par;
        par->parent = n;
        par->left = temp; // move the temp

        if(temp){
            temp->parent = par;
        }
        if(!gpar){ //no grandparent
            root = n;
        }else{
            (gpar->left==par? gpar->left:gpar->right) = n;
            n->parent = gpar;
        }
	}
	
	void print(){
		cout<<"Size: " <<size<<endl;
		print("", 'Q', root);
	}
	void print(string pre, char loc, node * n){
		if(!n){
			return;
		}
		cout<< pre <<"|--"<<loc<<": "<<n->elem;
		
		if(n->isRed){
			cout<<"(R)"<<endl;
		}else{
			cout<<"(B)"<<endl;
		}
		print(pre+" ", 'L', n->left);
		print(pre+" ", 'R', n->right);
	}
};
