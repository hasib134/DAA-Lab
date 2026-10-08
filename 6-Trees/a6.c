#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


#define MAX_STACK_SIZE 128
typedef struct{
    int data;
    struct node* left;
    struct node* right;
} TreeNode;

TreeNode* createNode(int data){
    TreeNode* treeNode = (struct node*)malloc(sizeof(TreeNode));

    treeNode->data = data;
    treeNode->left = NULL;
    treeNode->right = NULL;

    return treeNode;
}

typedef struct{
    TreeNode* items[MAX_STACK_SIZE];
    int top;
}stack;


void initStack(stack* s){
    s->top = -1;
}

bool isEmpty(stack *s){
    if(s->top ==-1) return true;

    return false;
}

void push(stack* s, TreeNode* node){
    s->top ++;
    s->items[s->top] = node;
}

TreeNode* pop(stack * s){
    if(s->top==-1){
        return ;
    }
    
    TreeNode* temp = s->items[s->top];
    s->top --;
    return temp;
}

TreeNode* peek(stack *s){
    return s->items[s->top];
}

void iterativeInorder(TreeNode* root){
    if(root ==NULL) return ; 

    stack s;
    initStack(&s);
    TreeNode *curr = root;
    while(curr!=NULL || !isEmpty(&s)){
        // go as deep as possible 

        while(curr!=NULL){
            push(&s,curr);
            curr = curr->left;
        }
        // pop an process the root
        curr = pop(&s);
        printf("%d ",curr->data);

        curr = curr->right;
    }
    printf("\n");
}

void IterativePreorder(TreeNode* root){
    stack s;
    initStack(&s);
    push(&s,root);

    while(!isEmpty(&s)){
        TreeNode* curr = pop(&s);

        printf("%d ",curr->data);

        if(curr->right!=NULL) push(&s,curr->right);
        if(curr->left!=NULL) push(&s,curr->left);
    }
    printf("\n");
} 



int main(){
 
//  iterative tree traversal 
// for iterative traversal we need stack


}