#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Node{
    int data;
    struct Node* left;
    struct Node* right;
}Node;

Node* createNode(int data){
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left =NULL;
    node->right = NULL;

    return node;
}

int max(Node* root){
    if(root ==NULL) return INT_FAST8_MIN;

    Node* temp = root;
    while(temp->right){
        temp = temp->right;
    }

    return temp->data;
}


int min(Node* root){
    if(root ==NULL) return INT_FAST8_MIN;

    Node* temp = root;
    while(temp->left){
        temp=temp->left;
    }
    return temp->data;
}


Node* insertBST(Node* root , int key){
    if(root == NULL)    return createNode(key);

    if(key<=root->data) { root->left = insertBST(root->left,key);}
    else    {root->right = insertBST(root->right,key);}

    return root;
}

bool search(Node* root , int key){
    if(root == NULL)    return false;

    Node* temp = root;
    while(temp){
        if(temp->data == key)   return true;

        else if(key < temp->data) temp = temp->left;

        else   temp = temp->right;
    }
    return false;
}

void inorder(Node* root){
    if(root == NULL)    return ;

    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);
}

int main(){
    int arr []= {5,3,7,9,1,0,2,8};

    int n = sizeof(arr)/sizeof(arr[0]);

    Node* root = NULL;

    for(int i=0;i<n;i++){
        root = insertBST(root,arr[i]);
    }

    // inorder(root);

    printf("%d ",search(root,9));
    printf("%d ",search(root,20));

    

}