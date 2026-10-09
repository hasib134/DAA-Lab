#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

// Delete Function 

typedef struct Node{
    int num_keys;
    int keys[3];
    struct Node* child[4];
    bool is_leaf;
}Node;

Node* createNode(bool is_leaf){
    Node* node = (Node*)malloc(sizeof(Node));
    node->num_keys = 0;
    node->is_leaf = is_leaf;

    for(int i=0;i<4;i++){
        node->child[i] = NULL;
    }
    return node;
}

//borrow from left
//borrow from right


void borrow_from_left(Node* parent , int idx){
    Node* curr_child = parent->child[idx];
    Node* left_child = parent->child[idx-1];
    
    //make space for parent in the child 
    for(int i =curr_child->num_keys-1;i>=0;i--){
        curr_child->keys[i+1] = curr_child->keys[i];
    }


    // if curr child is not the leaf shift the child pointers also
    if(!curr_child->is_leaf){
        for(int i = curr_child->num_keys;i>=0;i--){
        curr_child->child[i+1] = curr_child->child[i];
        }
        curr_child->child[0] = left_child->child[left_child->num_keys];
        left_child->child[left_child->num_keys] = NULL ; 
    }

    //copy the aprent key in the curr child 
    curr_child->keys[0]=parent->keys[idx-1];
    curr_child->num_keys++;
    
    parent->keys[idx-1] = left_child->keys[left_child->num_keys-1];
    left_child->num_keys--;
}

void borrow_from_right(Node* parent,int idx){
    Node* curr_child = parent->child[idx];
    Node* right_child = parent->child[idx+1];

    //copy parent key in the curr child 
    curr_child->keys[curr_child->num_keys] = parent->keys[idx];
    
    //check if the curr_child is the leaf node
    if(!curr_child->is_leaf){
        curr_child->child[curr_child->num_keys + 1] = right_child->child[0];
        right_child->child[0] = NULL;
    }

    // push the right siblimg key to parent 
    parent->keys[idx] = right_child->keys[0];


    //shift the pointers and keys in the right sibling by 1
    //shif the keys
    for(int i=0;i<right_child->num_keys;i++){
        right_child->keys[i] = right_child->keys[i+1];
    }

    //shift the pointers only if ,it is not leaf
    if(!right_child->is_leaf){
        for(int i=0;i<=right_child->num_keys;i++){
            right_child->child[i] = right_child->child[i+1];
        }
        right_child->child[right_child->num_keys]  = NULL;
    }
    right_child->num_keys -- ;
}

// Merge Function 

void merge(Node* parent,int idx){
    Node* left_child = parent->child[idx];
    Node* right_child = parent->child[idx+1];

    left_child->keys[1] = parent->keys[idx];
    left_child->keys[2] = right_child->keys[0]; 

    //if left_child is not a leaf
    if(!left_child->is_leaf){
        //shift the pointers
        left_child->child[2] = right_child->child[0];
        left_child->child[3] = right_child->child[1];
    }
    left_child->num_keys = 3;

    // now shift the keys and pointer in the parent 
    
    //shift the keys 
    for(int i = idx;i<parent->num_keys-1;i++){
        parent->keys[i] = parent->keys[i+1];
    }
    
    //shift the pointers 
    for(int i =idx+1;i<parent->num_keys;i++){
        parent->child[i] = parent->child[i+1];
    }
    parent->child[parent->num_keys] = NULL;
    parent->num_keys -- ;

    free(right_child);
}

//check if the node have atleast 2 child
void ensure_2_child(Node* parent,int *idx_pre){
    int idx = (*idx_pre); 
    Node* curr_child = parent->child[idx];

    //if child have 2 childs dont do anything 
    if(curr_child->num_keys >=2)    return ;

    //check for siblings 
    
    //check for left child
    if(idx>0 && parent->child[idx-1]->num_keys>=2){
        borrow_from_left(parent,idx);
    }

    //check for the right child;
    else if(idx < parent->num_keys && parent->child[idx + 1]->num_keys>=2){
        borrow_from_right(parent,idx);
    }
    
    //call merge function 
    else{

        if(idx<parent->num_keys){
            merge(parent,idx);
        }
        else{
            merge(parent,idx-1);
            *idx_pre = idx-1;
        }
        }
}

//Get the predecesor in the curr node , subtree 
int get_predecessor(Node* root){
    //gives the maximum value rooted at subtree root 
    Node* curr = root;
    while(!curr->is_leaf){
        curr = curr->child[curr->num_keys]; 
    }
    return curr->keys[curr->num_keys-1];
}

void delete_internal_node(Node* curr ,int key){
    //find the key in the tree 
    int i=0;

    // 10|20|30 key is 35 we want child index to be 4 
    while(i<curr->num_keys && key > curr->keys[i]){
        i++;
    }

    // Case 1:  
    // if the key to be deleted is in the curr node 
    if(i<curr->num_keys && curr->keys[i] == key){
        //key if found the node ,check if that node is leaf or not 

        // if the curr node is leaf node 
        if(curr->is_leaf){
            //just shift the key position 
            for (int j = i;j<curr->num_keys;j++){
                curr->keys[j] = curr->keys[j+1];
            }
            curr->num_keys--;
            return ;
        }
        // if the curr node is not a leaf node 
        else{
            // swap the key with inorder predecessor 
            int pred = get_predecessor(curr->child[i]);
            curr->keys[i] = pred;
            delete_internal_node(curr->child[i] , pred);
            return ;
        }
    }

    // Case 2 : if key is not present in the curr node 

    // recursively find the key in the child
    if(curr->is_leaf)   return;

    // ensure that the child have atleast 2 child 
    ensure_2_child(curr,&i);
    return delete_internal_node(curr->child[i],key);

}
Node* delete_key(Node* root , int key){

    if(!root) return NULL;

    delete_internal_node(root,key);

    if(root->num_keys == 0){
        Node* old_root = root ; 
        if(root->is_leaf){
            return NULL;
        }
        else{
            root = root->child[0];
        }
        free(old_root);
    }
    return root ;
}

void inorder(Node* root){
    if(!root)   return ;

    for(int i=0;i<root->num_keys;i++){
        if(!root->is_leaf){
            inorder(root->child[i]);
        }
        printf("%d ",root->keys[i]);
    }
    if(!root->is_leaf){
        inorder(root->child[root->num_keys]);
    }
}


void split(Node* parent , int idx){
    // idx : index where the split will happen 
    Node* curr_child = parent->child[idx];
    Node* sibling = createNode(curr_child->is_leaf);

    sibling->keys[0] = curr_child->keys[2];
    sibling->num_keys ++;

    if(!curr_child->is_leaf){
        sibling->child[0] = curr_child->child[2];
        sibling->child[1] = curr_child->child[3];
        curr_child->child[2] = NULL;
        curr_child->child[3] = NULL;
    }

    curr_child->num_keys = 1 ;

    //shift the pointer and keys in the parent node ;

    for(int i= parent->num_keys ; i>=idx+1;i--){
        parent->child[i+1] = parent->child[i];
    }
    parent->child[idx+1] = sibling;

    for(int i= parent->num_keys-1;i>=idx;i--){
        parent->keys[i+1] = parent->keys[i];
    }
    parent->keys[idx] = curr_child->keys[1];
    parent->num_keys ++;
}



void insert_in_non_full_tree(Node* curr ,int key){

    //node have atmost 2 child 
    int num = curr->num_keys-1;
    
    if(curr->is_leaf){
        //shift the keys ans insert in the node
        while(num >=0  && key < curr->keys[num]){
            curr->keys[num+1] = curr->keys[num];
            num--;
        }
        curr->keys[num+1] = key;
        curr->num_keys++;
        return ;
    }
    else{
        //if curr node is internal node
        //shift the keys and shift the pointers 
        while(num >=0 && key < curr->keys[num]){
            num--;
        }
        num++;

        //find the no of keys in the child 
        if(curr->child[num]->num_keys ==3 ){
            split(curr,num);
            if(key>curr->keys[num]) num++;
        }

        insert_in_non_full_tree(curr->child[num],key);

    }
    
}

Node* insert(Node* root, int key){
    if(root->num_keys == 3){
        Node* new_root = createNode(false);
        new_root->child[0] = root ;
        split(new_root,0);

        int target_idx;

        if(key>new_root->keys[0]){
            target_idx =1 ;
        }
        else{
            target_idx =0 ;
        }

        insert(new_root->child[target_idx],key);
        return new_root;
    }
    insert_in_non_full_tree(root , key);
    return root;
}

int main(){
    int arr[] = {78,34,7,41,45,79,69,23,49,67,68};
    int n = sizeof(arr)/sizeof(arr[0]);

    Node* root = createNode(true);

    for(int i =0 ;i<n;i++){
        root = insert(root,arr[i]);
    }
    inorder(root);
    
    delete_key(root ,45);
    printf("\n");
    inorder(root);

}
