#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    char color;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
}Node;

typedef struct RBTree{
    Node* root;
    Node* nil;
}RBTree;

Node* createNode(RBTree* tree,int data){
    Node* node = (Node*)malloc(sizeof(Node));
    node->color = '1';
    node->parent = tree->nil;
    node->right = tree->nil;
    node->left = tree->nil;
    node->data = data;
    return node;
}

RBTree* createTree(){
    RBTree* tree = (RBTree*) malloc(sizeof(RBTree));
    tree->nil = (Node*)malloc(sizeof(Node));
    tree->nil->parent = tree->nil;
    tree->nil->left = tree->nil;
    tree->nil->right = tree->nil;
    tree->nil->color = '0';

    tree->root = tree->nil;

    return tree;
}

void leftRotate(RBTree* tree,Node* x){
    Node* y = x->right;
    x->right = y->left;
    if(y->left!=tree->nil){
        y->left->parent = x;
    }

    if(x->parent == tree->nil){
        tree->root = y;
    }
    else if(x == x->parent->left){
        x->parent->left = y;
    }
    else if(y == x->parent->right){
        x->parent->right = y;
    }
    y->parent = x->parent ;
    y->left = x;
    x->parent = y;
}

void rightRotate(RBTree* tree,Node* x){
    Node* y = x->left;
    x->left = y->right;
    if(y->right!=tree->nil){
        y->right->parent = x;
    }

    if(x->parent == tree->nil){
        tree->root = y;
    }
    else if(x->parent->left == x){
        x->parent->left = y;
    }
    else if(x->parent->right == x){
        x->parent->right = y;
    }
    y->parent = x->parent;
    y->right =x;
    x->parent = y;

}

void insertFixUp(RBTree* tree, Node* z){

    while(z->parent->color == '0'){
        //case1 : parent is on the left
        if(z->parent == z->parent->parent->left){
            Node* uncle = z->parent->parent->right;
            //case 1.1 : uncle color is red
            if(uncle->color == '0'){
                z->parent ->color = '1';
                uncle->color = '1';
                z->parent->parent->color = '0';
                z = z->parent->parent;
            } 

            //case 1.2 : uncle color is black 
            else{
                // case 1.2.1: z is on the right child
                if(z == z->parent->right){
                    z = z->parent;
                    leftRotate(tree,z);
                }
                
                z->parent->color = '1';
                z->parent->parent->color = '0';
                rightRotate(tree,z->parent->parent);
            }
        }


        // case2 : parent is on the right;
        else{
            Node* uncle = z->parent->parent->left;
            //uncle color is red
            if(uncle->color =='0'){
                z->parent->color = '1';
                uncle->color = '1';
                z->parent->parent->color = '0';
                z = z->parent->parent;
            }

            // uncle colr is black
            else{
                if(z == z->parent->left){
                    z = z->parent;
                    rightRotate(tree,z);
                }
                z->parent->color = '1';
                z->parent->parent->color = '0';
                leftRotate(tree,z->parent->parent);
            }


        }
        
    }
    tree->root->color = '1';

}

void insert(RBTree* tree, int key){
    Node* z = createNode(tree,key);
    Node* y = tree->nil;
    Node* x = tree->root;
    while(x!=tree->nil){
        y=x;
        if(key<x->data){
            x = x->left;
        }
        else {
            x = x->right;
        }
    }

    z->parent = y;
    if(y == tree->nil){
        tree->root = z;
    }
    else if(key<y->data){
        y->left = z;
    }
    else {
        y->right = z;
    }
}

int main(){

}