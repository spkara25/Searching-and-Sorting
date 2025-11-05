//make an expression tree using binary tree

#include<stdio.h> 
#include<stdlib.h> 
#include<ctype.h> 
#include<string.h> 

struct node {
    char data; 
    struct node* left; 
    struct node* right;
}; 

struct node* createNode(char data) {
    struct node* nn = (struct node*) malloc(sizeof(struct node)); 
    nn->data = data; 
    nn->left = NULL; 
    nn->right = NULL; 
    return nn; 
}

int isOperator(char c) {
    if(c == '+' || c =='-' || c== '*' || c == '/' || c =='^') {
        return 1; 
    }
    return 0; 
}

struct node* constructTree(char postfix[]) {
    struct node* stack[100]; // stack to hold nodes as we build the tree
    int top = -1; //top pointer of stack

    for(int i=0; i<strlen(postfix);i++) {
        char current = postfix[i]; 
        if(!isOperator(current)) {
            struct node* newNode = createNode(current); 
            stack[++top] = newNode; 
        } else {
            struct node* newNode  = createNode(current); 
            newNode->right = stack[top--]; //pop function
            newNode->left = stack[top--]; 
            stack[++top] = newNode; //push function 

        }
    }
    return stack[top]; //root of the expression tree
}

void inorderTraversal(struct node* root) {
    if(root == NULL) {
        return; 
    }
    inorderTraversal(root->left); 
    printf("%c ", root->data); 
    inorderTraversal(root->right); 
}


int main() {
    char postfix[100]; 
    printf("Enter postfix expression: "); 
    scanf("%s", postfix); 

    struct node* root = constructTree(postfix); 

    printf("inorder traversal of the expression tree: ");
    inorderTraversal(root);
    printf("\n");
    return 0;
}
