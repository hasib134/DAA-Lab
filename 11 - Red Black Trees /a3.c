#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    char color;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
}Node;

typedef struct RedBlackTree{
    struct Node* root ;
    struct Node* NIL;
}RedBlackTree;

RedBlackTree* createTree(){
    RedBlackTree* tree = (RedBlackTree*)malloc(sizeof(RedBlackTree));
    tree->NIL = (Node*)malloc(sizeof(Node));
    tree->NIL->color= 1;
    tree->NIL->parent = tree->NIL;
    tree->NIL->left = tree->NIL;
    tree->NIL->right = tree->NIL;

    tree->root= tree->NIL;
    return tree;
}

Node* createNode(RedBlackTree* tree ,int data){
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->color = 0;
    node->left = tree->NIL;
    node->right = tree->NIL;
    node->parent = tree->NIL;
    return node;
}

void inorder(RedBlackTree* tree,Node* root){
    if(root == tree->NIL)   return;

    inorder(tree,root->left);
    printf("[%d %d]\t",root->data,root->color);
    inorder(tree,root->right);
}

void left_rotate(RedBlackTree* tree,Node* curr){

    Node* temp = curr->right;
    curr->right = temp->left;

    if(temp->left!=tree->NIL){
        temp->left->parent = curr;
    }
    
    temp->parent = curr->parent;
    
    if(curr->parent == tree->NIL){
        tree->root = temp;
    }
    else if(curr == curr->parent->left){
        curr->parent->left = temp;
    }
    else if(curr == curr->parent->right){
        curr->parent->right = temp;
    }
    temp->left = curr;
    curr->parent = temp;
}

void right_rotate(RedBlackTree* tree,Node* curr){
    Node* temp = curr->left;
    curr->left = temp->right;

    //if right node is not null;
    if(temp->right!=tree->NIL){
        temp->right->parent = curr;
    }

    //make temp parent to curr parent 

    temp->parent = curr->parent;
    
    // if curr node is root then make temp node to root
    if(curr->parent ==tree->NIL){
        tree->root = temp;
    }

    // if curr node is on left side

    else if(curr == curr->parent->left){
        curr->parent->left= temp;
    }
    // if  curr node is on right side 
    else if(curr == curr->parent->right){
        curr->parent->right = temp;
    }

    temp->right = curr;
    curr->parent = temp;
}

void fix_UP_RBTree(RedBlackTree* tree,Node* newnode){
    //fix the red black tree 
    

    //violation will only happen if newly inserted node parents is red color node 
    while(newnode->parent->color == 0){
        //if uncle is also red color node 
        //parent is on left side
        if(newnode->parent == newnode->parent->parent->left){
            Node* uncle = newnode->parent->parent->right;
            if(uncle->color == 0){
                // case 1 : uncle is red color node and parent is also red color node
                newnode->parent->color = 1;
                uncle->color = 1;
                newnode->parent->parent->color = 0;
                newnode = newnode->parent->parent;
            }
            else{
                //case 2 : uncle is black color node and new node is on the right 
                if(newnode==newnode->parent->right){
                    newnode = newnode->parent;
                    left_rotate(tree,newnode);
                }

                //case 3: uncle is black and z is left child
                newnode->parent->color = 1;
                newnode->parent->parent->color =0;
                right_rotate(tree,newnode->parent->parent); 
            }
        }
        //parent is on the right side 
        else{
            if(newnode->parent == newnode->parent->parent->right){
                Node* uncle = newnode->parent->parent->left;
                // case1 : if uncle is red color node
                if(uncle->color == 0){
                    newnode->parent->color = 1;
                    uncle->color =1;
                    newnode->parent->parent->color = 0;
                    newnode = newnode->parent->parent;
                } 
                else{
                    //uncle is black color node and new node is on the left 
                    if(newnode == newnode->parent->left){
                        newnode = newnode->parent;
                        right_rotate(tree,newnode);
                    }

                    newnode->parent->color = 1;
                    newnode->parent->parent->color = 0;
                    left_rotate(tree,newnode->parent->parent);
                }
            }
        }
    }
    tree->root->color = 1;
    
}

void insert_in_RBTree(RedBlackTree* tree,int val){
    Node* newnode = createNode(tree,val);
    Node* temp = tree->root;

    Node *y = tree->NIL;
    while(temp!=tree->NIL){
        y=temp;
        if(val<temp->data){
            temp = temp->left;
        }
        else{
            temp = temp->right;
        }
    }
    newnode->parent = y;

    if(y == tree->NIL){
        tree->root = newnode; 
    }
    else if(newnode->data<y->data){
        y->left = newnode;
    }
    else{
        y->right = newnode;
    }
    newnode->left = tree->NIL;
    newnode->right = tree->NIL;

    fix_UP_RBTree(tree,newnode);
}

int main(){
    RedBlackTree* tree = createTree();
    int arr [] = {6,4,2,7,9,1,0,3,5};
    int n = sizeof(arr)/sizeof(arr[0]);
    for(int i =0;i<n;i++){
        insert_in_RBTree(tree,arr[i]);
    }
    inorder(tree,tree->root);

}