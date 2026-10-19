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

Node* createNode(RBTree * tree,int data){
    Node* node =(Node*)malloc(sizeof(Node));
    node->data = data;
    node->color = '0';
    node->left = tree->nil;
    node->right = tree->nil;
    node->parent = tree->nil;
    return node;
}

RBTree* createTree(){
    RBTree * tree = (RBTree*)malloc(sizeof(RBTree));
    tree->nil = (Node*)malloc(sizeof(Node));
    tree->nil->left = tree->nil;
    tree->nil->parent = tree->nil;
    tree->nil->right = tree->nil;
    tree->nil->color = '1';

    tree->root = tree->nil;
    return tree;
}

void leftRotate(RBTree* tree,Node*x){
    Node* y =x->right;
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
    else{
        x->parent->right = y;
    }

    y->parent = x->parent;
    y->left = x;
    x->parent = y;
}

void rightRotate(RBTree* tree,Node* x){
    Node* y = x->left;
    x->left = y ->right;
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

void insertFixUp(RBTree* tree, Node* z){
    while(z->parent->color == '0'){
        // case 1 : parent is on the left;
        if(z->parent == z->parent->parent->left){
            Node* uncle = z->parent->parent->right;
            if(uncle->color =='0'){
                z->parent->color = '1';
                uncle->color = '1';
                z->parent->parent->color = '0';
                z  = z->parent->parent;
            }
            else{
                if(z==z->parent->right){
                    z = z->parent;
                    leftRotate(tree,z);

                }
                z->parent->color = '1';
                z->parent->parent->color = '0';
                rightRotate(tree,z->parent->parent);
            }
        }
        //case2 : parent is on the right
        else{
            Node* uncle = z->parent->parent->left;
            if(uncle->color =='0'){
                z->parent->color = '1';
                uncle->color ='1';
                z->parent->parent->color = '0';
                z = z->parent->parent;
            } 
            else{
                if(z == z->parent->left){
                    z = z->parent;
                    rightRotate(tree,z);
                }

                z->parent->color = '1';
                z->parent->parent->color='0'; 
                leftRotate(tree,z->parent->parent);
            }
        }
    }
    tree->root->color = '1';
}

void insert(RBTree* tree, int key){
    Node*z = createNode(tree,key);
    Node* y = tree->nil;
    Node* x = tree->root;

    while(x!=tree->nil){
        y =x;
        if(key<x->data){
            x = x->left;
        }
        else{
            x =x->right; 
        }
    }
    z->parent = y;
    if(y==tree->nil){
        tree->root = z;
    }
    else if(key<y->data){
        y->left = z;
    }
    else{
        y->right = z;
    }
    insertFixUp(tree,z);
}

void inorder(RBTree* tree, Node* root){
    if(root == tree->nil)   return ;

    inorder(tree,root->left);
    printf("[%d %c] ",root->data,root->color);
    inorder(tree,root->right);
}


int main(){
    RBTree* tree = createTree();

    // Inserting values that trigger recoloring, left rotation, and right rotation
    int values[] = {20, 15, 25, 10, 5, 1, 30, 22};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++) {
        insert(tree, values[i]);
    }
    printf("\n");

    inorder(tree, tree->root);
    printf("\n");

    return 0;
}