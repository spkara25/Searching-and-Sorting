#include<stdio.h> 
#include<stdlib.h> 
#include<ctype.h> 

typedef struct node {
    char data; 
    struct node* left; 
    struct node* right; 
} Node; 

Node* createNode(char data) {
    Node* nn = (Node*) malloc(sizeof(Node)); 
    if(nn == NULL) {
        printf("Memory allocation failed!\n"); 
        exit(1); 
    }
    nn->data = data; 
    nn->left = NULL; 
    nn->right = NULL; 
    return nn; 

}

int evaluateTree(Node* root) {
    if(root == NULL) {
        return 0; 
    }
    if(isdigit(root->data)) {
        return root->data -'0'; 
    }
    if(isalpha(root->data)) {
        printf("Variable C not found. Exiting.\n");
        return 0; 
    }

    //recursive step now
    int leftVal = evaluateTree(root->left); 
    int rightVal = evaluateTree(root->right); 

    switch(root->data) {
        case '+':
            return leftVal+rightVal; 
        
        case '-': 
            return leftVal - rightVal; 

        case '*':
            return leftVal*rightVal; 
        
        case '/':
            if(rightVal == 0) {
                printf("Error.\n"); 
                return 0; 
            }
            return leftVal/rightVal; 

        default: 
            printf("Error: Unknown Operator %c\n", root->data);
            return 0; 
    }
}

int main() {
    Node* three = createNode('3'); 
    Node* four = createNode('4');
    Node* five = createNode('5');
    Node* two = createNode('2');

    Node* plus = createNode('+');

    plus->left = three; 
    plus->right = five; 

    Node* minus = createNode('-'); 
    minus->left = four; 
    minus->right = two; 

    Node* multiply = createNode('*');
    multiply->left = plus;
    multiply->right = minus;

    int result = evaluateTree(multiply); 
    printf("Result of expression tree evaluation: %d\n", result); // Expected:

    return 0; 

}
