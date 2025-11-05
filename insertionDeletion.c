//binary search tree insertion and deletion

#include<stdio.h>
#include<stdlib.h>

struct node {
    int data; 
    struct node* left; 
    struct node* right; 
}; 

struct node* createNode(int data) {
    struct node* nn = (struct node*) malloc(sizeof(struct node)); 
    if( nn == NULL) {
        printf("Memory allocation failed!\n"); 
        exit(1); 
    }
    nn->data = data; 
    nn->left = NULL; 
    nn->right = NULL; 
    return nn; 
}

struct node* insert(struct node* root, int data) {
    if(root == NULL) {
        return createNode(data); 
    }

    if(data < root->data) {
        root->left = insert(root->left, data); 
    }
    else if(data > root->data) {
        root->right = insert(root->right, data); 
    }
    return root; 
}

struct node* findMin(struct node* root) {
    struct node* current = root; 
    while(current && current->left != NULL) {
        current = current->left;
    }
    return current; 
}

struct node* deletion(struct node* root, int key) {
    if(key < root->data) {
        root->left = deletion(root->left, key); 
    }
    else if(key > root->data) {
        root->right = deletion(root->right, key); 
    }
    else {
        if(root->left == NULL) {
            struct node* temp = root->right; 
            free(root); 
            return temp;
        }
        else if(root->right == NULL) {
            struct node* temp = root->left; 
            free(root); 
            return temp; 
        }
        struct node* temp = findMin(root->right); 
        root->data = temp->data;
        root->right = deletion(root->right, temp->data);
    }
    return root; 
}

void inorder(struct node* root) {
    if(root != NULL) {
        inorder(root->left); 
        printf("%d ", root->data); 
        inorder(root->right); 
    }
}

int main() {
    struct node* root = NULL; 
    root = insert(root, 50); 
    root = insert(root, 30); 
    root = insert(root, 20); 
    root = insert(root, 40); 
    root = insert(root, 70); 
    root = insert(root, 60); 
    root = insert(root, 80); 

    printf("Inorder traversal of the given tree \n"); 
    inorder(root); 
    printf("\n"); 

    printf("Delete 20\n"); 
    root = deletion(root, 20); 
    printf("Inorder traversal after deletion of 20 \n"); 
    inorder(root); 
    printf("\n"); 

    printf("Delete 30\n"); 
    root = deletion(root, 30); 
    printf("Inorder traversal after deletion of 30 \n"); 
    inorder(root); 
    printf("\n"); 

    printf("Delete 50\n"); 
    root = deletion(root, 50); 
    printf("Inorder traversal after deletion of 50 \n"); 
    inorder(root); 
    printf("\n"); 

    return 0;
}
