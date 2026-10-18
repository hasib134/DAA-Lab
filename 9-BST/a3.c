#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
}Node;

Node* createNode(int data){
    Node* node =(Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->parent = NULL;
    node->right = NULL;
    return node;
}

Node* insertBST(Node* root,int key){
    if(root == NULL){
        return createNode(key);
    }
    Node* parent = NULL;
    Node* curr = root;

    while(curr!=NULL){
        parent = curr;
        if(key <= parent->data){
            curr = curr->left;
        }
        else{
            curr = curr->right;
        }
    }
    Node* newNode = createNode(key);
    newNode->parent = parent;
    if(key<=parent->data){
        parent->left = newNode;
    }
    else{
        parent->right = newNode;
    }
    return root;
}

Node* max_node(Node* root){
    if(root == NULL)    return NULL;
    Node* curr =root;
    while(curr->right){
        curr = curr->right;
    }
    return curr;
}

Node* min_node(Node* root){
    if(root == NULL)    return NULL;
    Node* curr =root;
    while(curr->left){
        curr = curr->left;
    }
    return curr;
}


Node* joinBST(Node* root1,Node* root2){
    if(root1 == NULL)   return root2;
    if(root2 == NULL)   return root1;

    Node* max1 =max_node(root1); 
    Node* min1 =min_node(root1); 

    Node* max2 =max_node(root2); 
    Node* min2 =min_node(root2); 


    Node* curr = NULL;
    Node* temp1 = NULL;
    Node* temp2 = NULL;
    if(max1->data<min2->data){
        curr = max1;
        temp1 = root1;
        temp2= root2;
    }
    else if(max2->data<min1->data){
        curr = max2;
        temp1 = root2;
        temp2 = root1;
    }
    else{
        //trees overlap 
        return NULL;
    }

    if(curr->parent!=NULL){
        curr->parent->right = curr->left;
        if(curr->left!=NULL){
            curr->left->parent = curr->parent;
        }
        curr->left = temp1;
        temp1->parent = curr;
    }
    curr->right = temp2;
    temp2->parent = curr;
    curr->parent =NULL;
    return curr;
}

void inorder(Node* root){
    if(root == NULL)    return;
    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);
}

int main(){
    int arr1[]= {1,4,7,3,2,9,5};
    int arr2[] = {10,40,70,30,20,90,50};

    Node* root1 = NULL;
    Node* root2 = NULL;

    int n1 = sizeof(arr1)/sizeof(arr1[0]);
    int n2 = sizeof(arr2)/sizeof(arr2[0]);

    for(int i=0;i<n1;i++){
        root1 = insertBST(root1,arr1[i]);
    }

    for(int i=0;i<n2;i++){
        root2 = insertBST(root2,arr2[i]);
    }

    Node* root = joinBST(root1,root2);

    inorder(root1);
    printf("\n");

    inorder(root2);
    printf("\n");

    inorder(root);
    printf("\n");
}