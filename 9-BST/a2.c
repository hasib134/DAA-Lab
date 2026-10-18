#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
    int data;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
}Node;

Node* createNode(int data){
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->parent =NULL;
    return node;
}

Node* insertBST(Node* root,int key){
    if(root ==NULL) return createNode(key);

    Node* parent= NULL;
    Node* curr = root;
    while(curr!=NULL){
        parent = curr;
        if(key<=curr->data){
            curr = curr->left;
        }
        else{
            curr = curr->right;
        }
    }
    Node* newnode = createNode(key);
    newnode->parent = parent;

    if(key<=parent->data){
        parent->left = newnode;
    }
    else{
        parent->right = newnode;
    }
    return root;
}

int max_val(Node* root){
    if(root ==NULL) return -1;
    Node* curr = root;
    while(curr->right){
        curr = curr->right;
    }
    return curr->data;
}
int min_val(Node* root){
    if(root == NULL)    return -1;
    Node* curr = root;

    while(curr->left){
        curr=curr->left;
    }
    return curr->data;
}

void inorder(Node* root){
    if(root == NULL)    return;

    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);
}

int main(){
    int arr[] = {4,6,8,2,1,6,2,7,5};
    Node* root = NULL;
    int n = sizeof(arr)/sizeof(arr[0]);
    for(int i=0;i<n;i++){
        root = insertBST(root,arr[i]);
    }
    inorder(root);
    printf("\n");
    
    printf("%d\n",min_val(root));
    printf("%d\n",max_val(root));



}