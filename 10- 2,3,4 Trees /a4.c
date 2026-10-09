#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Node{
    int num_keys;
    int keys[3];
    struct Node* child[4];
    bool is_leaf;
}Node;

Node* createNode(bool is_leaf){
    Node* node = (Node*) malloc(sizeof(Node));

    node->num_keys = 0;
    node->is_leaf = is_leaf;
    for(int i=0;i<4;i++){
        node->child[i] = NULL;
    }
    return node;
}

bool search(Node* root,int key){
    if(!root)   return false;

    //find the child where the key can be present
    int i=0;
    while(i < root->num_keys && key>root->keys[i])    i++;
    
    if(i < root->num_keys && key == root->keys[i])    return true;

    if(root->is_leaf)   return false;

    return search(root->child[i],key);
}

void inorder(Node* root){
    if(!root)   return;

    for(int i =0;i<root->num_keys;i++){
        if(!root->is_leaf){
            inorder(root->child[i]);
        }
        printf("%d ",root->keys[i]);
    }
    if(!root->is_leaf){
        inorder(root->child[root->num_keys]);
    }
}

void split(Node* parent ,int idx){
    Node* full_child = parent->child[idx];
    Node* sibling = createNode(full_child->is_leaf);
    
    sibling->keys[0]= full_child->keys[2];
    sibling->num_keys =1 ;
    
    if(!full_child->is_leaf){
        sibling->child[0] = full_child->child[2];
        sibling->child[1] = full_child->child[3];
        full_child->child[2]= NULL;
        full_child->child[3]= NULL;
    }   
    full_child->num_keys = 1;
    
    //shift the pointers in parent 
    for(int i= parent->num_keys;i>=idx+1;i--){
        parent->child[i+1] = parent->child[i];
    }
    parent->child[idx+1] = sibling;

    //shift the  keys in the parent

    for(int i=parent->num_keys-1;i>=idx;i--){
        parent->keys[i+1] = parent->keys[i];
    }
    parent->keys[idx] = full_child->keys[1];
    parent->num_keys++;
}

void insert_nonFullNode(Node* curr,int key){
    //if curr node is a leaf 
    //insertion always happens at the leaf node
    int i = curr->num_keys-1; 
    if(curr->is_leaf){
        //shift the keys and 
        while(i>=0 && key<curr->keys[i]){
            curr->keys[i+1] =curr->keys[i]; 
            i--;
        }
        curr->keys[i+1] = key;
        curr->num_keys++;
        return; 
    }
    else{
        while(i>=0 && key<curr->keys[i]){
            i--;
        }
        i++;
        if(curr->child[i]->num_keys==3){
            split(curr,i);
            if(key>curr->keys[i])   i++;

        }
        insert_nonFullNode(curr->child[i],key);
    }
}
Node* insert(Node* root,int key){
    if(root->num_keys == 3){
        Node* new_root = createNode(false);
        new_root->child[0] = root ;
        split(new_root,0);

        int target_idx ;
        if(key>new_root->keys[0]){
            target_idx = 1;
        }
        else{
            target_idx = 0;
        }

        insert_nonFullNode(new_root->child[target_idx],key);
        return new_root;
    }
    insert_nonFullNode(root,key);
    return root ;
}
int main(){

    int arr[] = {50, 20, 70, 90, 10, 30, 40, 60, 80, 100};
    int n = sizeof(arr)/sizeof(arr[0]);

    Node* root = createNode(true);
    for(int i =0 ;i<n;i++){
        root = insert(root,arr[i]);
    }
    inorder(root);
    printf("%d ",search(root,1000));
}
