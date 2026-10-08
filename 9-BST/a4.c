#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* left;
    struct Node* right;   
}Node;

Node* createNode(int data){
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* insert(Node* root ,int key){
    if(root ==NULL) return createNode(key);

    if(key<=root->data )   root->left = insert(root->left,key);

    else root->right = insert(root->right,key);

    return root ;
}

Node* inorderSucc(Node* root ){
    if(root ==NULL) return NULL;

    Node* temp = root ;
    while(temp->left){
        temp = temp->left;
    }
    return temp;
}

Node* delete(Node* root,int key){
    if(root ==NULL) return NULL;

    if(key<root->data){
        root->left = delete(root->left,key);
    }
    else if(key>root->data){
        root->right = delete(root->right,key);
    }
    else{
        if(root->left ==NULL){
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL){
            Node* temp = root->left;
            free(root);
            return temp;
        }    
        else{
            Node* x =inorderSucc(root->right);
            root->data = x->data;
            root->right = delete(root->right , x->data);
        }
    }
    return root ;
}

Node* join(Node* root1,Node* root2){
    if(root1 == NULL && root2 == NULL)  return NULL;

    if(root1 == NULL)   return root2;
    else if(root2 == NULL)   return root1;

    else{
        //find inorder Successor in T1
        Node* x = inorderSucc(root1->right);
        Node* root = createNode(x->data);
        
        root1 =delete(root1,x->data); 
        root->left = root1;
        root->right = root2;

        return root;
    }
}

void inorder(Node* root ){
    if(root == NULL)    return;

    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);
}

int main(){
    int arr1[] = {40,30,80,60,46,71,94};
    int arr2[] ={28,21,29,12,5};
    int n =sizeof(arr1)/sizeof(arr1[0]);
    int m =sizeof(arr2)/sizeof(arr2[0]);
    
    Node* root1 = NULL;
    for(int i=0;i<n;i++){
        root1 = insert(root1,arr1[i]);
    }
    Node* root2 =NULL;
    for(int i=0;i<m;i++){
        root2 = insert(root2,arr2[i]);
    }
    inorder(root1);
    printf("\n");
    inorder(root2);
    printf("\n");

    Node* root = join(root2,root1);
    inorder(root);
    printf("\n");





}