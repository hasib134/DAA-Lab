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
    Node* node = (Node*)malloc(sizeof(Node));
    node->is_leaf = is_leaf;
    node->num_keys =0;
    for(int i =0;i<4;i++){
        node->child[i] = NULL;
    }  
    return node;
}

void split_child(Node* parent,int idx){
    Node* full_child =parent->child[idx];
    Node* sibling = createNode(full_child->is_leaf);

    sibling->keys[0] = full_child->keys[2];
    sibling->num_keys = 1;
    
    if(!full_child->is_leaf){
        sibling->child[0] = full_child->child[2];
        sibling->child[1] = full_child->child[3];
        full_child->child[2] = NULL;
        full_child->child[3] = NULL;
    }

    full_child->num_keys = 1;
    
    //shift the child pointers in the parent    
    for(int i=parent->num_keys;i>=idx+1;i--){
        parent->child[i+1] = parent->child[i];
    }
    parent->child[idx+1] =  sibling;

    //shift the keys in the parent 

    for(int i = parent->num_keys;i>=idx;i++){
        parent->keys[i+1] = parent->keys[i];
    }
    parent->keys[idx] = full_child->keys[1];
    parent->num_keys++;

}



void insert_in_nonfullNode(Node* curr ,int key){
    // here we are assuming that the node have atmost 2 child 
    //insertion always happens atleaf nodes 
    //no of keys in the node 
    int num = curr->num_keys-1;

    //case 1 : if curr node is a leaf node 
    if(curr->is_leaf){
        while(num>=0 && key<curr->keys[num]){
            curr->keys[num+1] = curr->keys[num];
            num--;
        }
        curr->keys[num+1] = key;
        curr->num_keys++;
        return ;
    }
     
    else{
        while(num>=0 && key<curr->keys[num]){
            num -- ;
        }
        num++;
        if(curr->child[num]->num_keys == 3){
            split_child(curr,num);
            if(key>curr->keys[num]) num++;
        }
        insert_in_nonfullNode(curr->child[num],key);
    }
}
Node* insert(Node* root ,int key){

    if(root->num_keys ==3){
        //root is full we have to split the root ;
        Node* new_root  = createNode(false);
        new_root->child[0] = root;
        split_child(new_root,0);
        

        //choose where to put the new key 
        int target_idx ;
        if(key > new_root->keys[0]){
            target_idx = 1;
        }
        else{
            target_idx = 0;
        }
        insert_in_nonfullNode(new_root->child[target_idx],key);
        return new_root;
    }
    insert_in_nonfullNode(root,key);
    return root;
}
int main(){

}


