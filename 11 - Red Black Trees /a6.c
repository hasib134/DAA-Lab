#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    char color ;
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
    node->data = data;
    node->color = '0';
    node->left = tree->nil;
    node->right = tree->nil;
    node->parent = tree->nil;

    return node;
}

RBTree * createtree(){
    RBTree* tree = (RBTree*)malloc(sizeof(RBTree));
    tree->nil = (Node*)malloc(sizeof(Node));
    tree->nil->parent = tree->nil;
    tree->nil->left = tree->nil;
    tree->nil->right = tree->nil;
    tree->nil->color = '1';
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
        tree->root= y;
    }
    else if(x == x->parent->left){
        x->parent->left = y;
    }
    else{
        x->parent->right = y;
    }
    y->left = x;
    y->parent = x->parent;
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
    else if(x == x->parent->left){
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    y->right = x;
    y->parent = x->parent;
    x->parent = y;
}

void insertFixUP(RBTree* tree,Node* z){
    while(z->parent->color == '0'){
        if(z->parent == z->parent->parent->left){
            Node* uncle = z->parent->parent->right;
            if(uncle->color == '0'){
                z->parent->color = '1';
                uncle->color = '1';
                z->parent->parent->color = '0';
                z = z->parent->parent;
            }
            else{
                if(z = z->parent->right){
                    z=z->parent;
                    leftRotate(tree,z);
                }
                z->parent->color = '1';
                z->parent->parent->color = '0';
                leftRotate(tree,z->parent->parent);
            }
        }
        else{
            Node* uncle = z->parent->parent->left;
            if(uncle->color =='0'){
                z->parent->color ='1';
                uncle->color = '1';
                z->parent->parent->color= '0';
                z = z->parent->parent; 
            }
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
    Node*z = createNode(tree, key);
    Node* curr = tree->root;
    Node* y = tree->nil;

    while(curr!=tree->nil){
        y = curr;
        if(key<curr->data){
            curr = curr->left;
        }
        else{
            curr = curr->right;
        }
    }

    z->parent = y;
    if(y == tree->nil){
        tree->root = z;
    }
    else if(key<y->data){
        y->left = z;
    }
    else{
        y->right = z;
    }
    insertFixUP(tree,z);
}


void transplant(RBTree* tree,Node* u,Node*v){
    if(u->parent == tree->nil){
        tree->root = v;
    }
    else if(u == u->parent->left){
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
}

Node* successor(RBTree* tree,Node* z){
    if(z == tree->nil)  return tree->nil;
    Node* curr = z;
    while(curr->left!=tree->nil){
        curr = curr->left;
    }
    return curr;
}

Node* search(RBTree* tree,int key){
    Node* curr = tree->root;
    while(curr!=tree->nil){
        if(key == curr->data){
            return curr;
        }
        else if(key<curr->data){
            curr = curr->left;
        }
        else{
            curr = curr->right;
        }
    }
    return tree->nil;
}

void deleteFixUP(RBTree* tree,Node* z){

}

void delete(RBTree* tree, int key){
    Node* z = search(tree,key);
    if(z == tree->nil)  return ;
    
    Node* y = z;
    char y_color = y->color;
    Node* x;

    if(z->left == tree->nil){
        x = z->right;
        transplant(tree,z,z->right);
    }
    else if(z->right == tree->nil){
        x = z->left;
        transplant(tree,z,z->left);
    }
    else{
        y = successor(tree,z->right);
        y_color = y->color;
        x = y->right;

        if(y->parent ==z){
            x->parent = y;
        }
        else{
            transplant(tree,y,y->right);
            y->right = z->right;
            z->right->parent = y;
        }

        transplant(tree,z,y);
        y->left = z->left;
        z->left->parent = y;
        y->color = z->color;
    }
    free(z);
    if(x->color == '1'){
        deleteFixUP(tree,x);
    }
}














