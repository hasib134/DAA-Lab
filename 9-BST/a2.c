#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* left;
    struct Node* right;
}Node;

Node * createNode(int data){
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left  = NULL;
    node->right = NULL;

    return node;
}

Node* insert(Node* root , int key){
    if(root == NULL)    return createNode(key);

    if(key <= root->data) root->left = insert(root->left,key);

    else root->right = insert(root->right,key);

    return root;
}

Node* inorderSucc(Node* root){
    if(root ==NULL) return NULL;
    Node* temp = root;

    while(temp->left){
        temp = temp->left;
    }
    return temp;
}

Node* delete(Node* root , int key){
    if(root ==NULL) return NULL;


    //find the key
    if(key<root->data){
        root->left = delete(root->left,key);
    }
    else if (key>root->data){
        root->right = delete(root->right,key);
    }

    else{
        //key is foun delete that node

        //node have 0 ,1 child
        if(root->left ==NULL){
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right ==NULL){
            Node* temp = root->left;
            free(root);
            return temp;
        }

        //node have 2 child 
        //find the inorder successor 
        
        Node* x = inorderSucc(root->right);

        root->data = x->data;
        root->right = delete(root->right,x->data);
    }
    return root ;
}

void inorder(Node* root ){
    if(root ==NULL)  return;

    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);
}

int main(){
    Node* root = NULL;
    
    int arr[] ={4,7,2,1,8,0,9,3,7,5};
    int n = sizeof(arr)/sizeof(arr[0]);

    for(int i=0;i<n;i++){
        root = insert(root,arr[i]);
    }

    inorder(root);
    printf("\n");

    delete(root, 5);
    inorder(root);
    printf("\n");
}