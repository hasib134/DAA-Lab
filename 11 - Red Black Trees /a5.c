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
    node->color = '0';
    node->data = data;
    node->parent = tree->nil;
    node->left = tree->nil;
    node->right = tree->nil;
    return node;
}

RBTree* createTree(){
    RBTree* tree = (RBTree*)malloc(sizeof(RBTree));
    tree->nil = (Node*)malloc(sizeof(Node));
    tree->nil->parent = tree->nil;
    tree->nil->left = tree->nil;
    tree->nil->right = tree->nil;
    tree->nil->color = '1';
    tree->root= tree->nil;
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

void insertFixUp(RBTree* tree,Node* z){
    while(z->parent->color=='0'){
        
        //parent is on the left side
        if(z->parent == z->parent->parent->left){
            Node* uncle = z->parent->parent->right;
            if(uncle->color == '0'){
                z->parent->color = '1';
                uncle->color = '1';
                z->parent->parent->color = '0';
                z = z->parent->parent;
            }
            else{
                if(z == z->parent->right){
                    z = z->parent;
                    leftRotate(tree,z);
                }
                z->parent->color = '1';
                z->parent->parent->color = '0';
                rightRotate(tree,z->parent->parent);
            }
        }

        //parent is on the right side
        else{
            Node* uncle = z->parent->parent->left;
            if(uncle->color == '0'){
                z->parent->color = '1';
                uncle->color = '1';
                z->parent->parent->color = '0';
                z= z->parent->parent;
            }
            else{
                if(z == z->parent->left){
                    z=z->parent;
                    rightRotate(tree,z);
                }
                z->parent->color= '1';
                z->parent->parent->color = '0';
                leftRotate(tree,z->parent->parent);
            }
        }
    }
    tree->root->color = '1';
}

void insert(RBTree* tree,int key){
    Node* z = createNode(tree,key);

    Node* curr = tree->root;
    Node* y = tree->nil;

    while(curr!=tree->nil){
        y = curr;
        if(key<curr->data){
            curr= curr->left;
        }
        else{
            curr = curr->right;
        }
    }

    if(y== tree->nil){
        tree->root= z;
    }
    else if(key<y->data){
        y->left = z;
    }
    else{
        y->right = z;
    }
    z->parent = y;

    insertFixUp(tree,z);
}


void inorderTraversal(RBTree* tree,Node* root){
    if(root == tree->nil)   return ;

    inorderTraversal(tree,root->left);
    printf("[%d %c] ",root->data,root->color);
    inorderTraversal(tree,root->right);
}



void transplant(RBTree* tree , Node* u,Node* v){
    if(u->parent == tree->nil){
        tree->root = v;
    }
    else if(u == u->parent->left){
        u->parent->left = v;
    }
    else{
        u->parent->right = v;
    }
    v->parent = u->parent;
}

Node* successor(RBTree* tree,Node* node){
    if(node == tree->nil)   return tree->nil;

    Node* curr = node;
    while(curr->left!=tree->nil){
        curr = curr->left;
    }
    return curr->left;
}

void delete(RBTree* tree,Node* z){
    Node* y = z;
    Node* x;
    char y_color = y->color;


    //case 1 : z has no left child
    if(z->left == tree->nil){
        x = z->right;
        transplant(tree,z,z->right);
    }
    
    //case2 : z has no right child
    else if(z->right == tree->nil){
        x = z->left;
        transplant(tree,z,z->left);
    }

    //case 3 : z has 2 child 
    else{
        y = successor(tree,z->right);
        y_color = y->color;
        x = y->right;

        if(y->parent == z){
            x->parent = y;
        }
        else{
            transplant(tree,y,y->right);
            y->right = z->right;
            z->right->parent = y;
        }

        transplant(tree,z,y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color; 
    }
    free(z);

    if(y_color =='1'){
        deleteFixUp(tree,x);
    }
}

int main(){
    int arr[] = {3,6,8,2,1,9,0,5,7};
    int n = sizeof(arr)/sizeof(arr[0]);

    RBTree* tree = createTree();
    for(int i = 0;i<n;i++){
        insert(tree,arr[i]);
    }
    inorderTraversal(tree,tree->root);
    printf("\n");
}   