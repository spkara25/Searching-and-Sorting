// Binary Search Tree Insertion, Deletion, Min, Max, and Kth Elements

#include<stdio.h>
#include<stdlib.h>
#include<limits.h> // Used for INT_MIN and safety checks

struct node {
    int data; 
    struct node* left; 
    struct node* right; 
}; 

// --- Global Variables for Kth Element Traversal ---
// These must be reset before each call to find the Kth element
int count_kth = 0; 
int kth_element_result = -1; 


// --- Node Creation ---
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

// --- Insertion ---
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

// --- Deletion Helper: Find Minimum Node (Inorder Successor) ---
struct node* findMinNode(struct node* root) {
    struct node* current = root; 
    while(current && current->left != NULL) {
        current = current->left;
    }
    return current; 
}

// --- Deletion ---
struct node* deletion(struct node* root, int key) {
    if(root == NULL) {
        // Key not found case
        return root; 
    }

    if(key < root->data) {
        root->left = deletion(root->left, key); 
    }
    else if(key > root->data) {
        root->right = deletion(root->right, key); 
    }
    else {
        // Node to be deleted found
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
        struct node* temp = findMinNode(root->right); 
        root->data = temp->data;
        root->right = deletion(root->right, temp->data);
    }
    return root; 
}

// --- Traversal (Inorder for Verification) ---
void inorder(struct node* root) {
    if(root != NULL) {
        inorder(root->left); 
        printf("%d ", root->data); 
        inorder(root->right); 
    }
}

// =========================================================
//            LOGIC ADDED FOR MIN, MAX, KTH
// =========================================================

// --- 4. Find Minimum Element (Leftmost Node) ---
int findBSTMin(struct node* root) {
    if (root == NULL) {
        return INT_MIN; // Use INT_MIN to signify an empty tree or error
    }
    struct node* current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current->data;
}

// --- 5. Find Maximum Element (Rightmost Node) ---
int findBSTMax(struct node* root) {
    if (root == NULL) {
        return INT_MIN;
    }
    struct node* current = root;
    while (current->right != NULL) {
        current = current->right;
    }
    return current->data;
}

// --- 6. Find Kth Smallest Element (Inorder Traversal) ---
void findBSTKthSmallest(struct node* root, int k) {
    // Stop if we hit NULL OR if the Kth element is already found
    if (root == NULL || count_kth >= k) {
        return;
    }

    // L (Left)
    findBSTKthSmallest(root->left, k);

    // N (Node)
    if (count_kth < k) {
        count_kth++;
        if (count_kth == k) {
            kth_element_result = root->data;
            return; // Found it, terminate the search
        }
    }

    // R (Right)
    findBSTKthSmallest(root->right, k);
}

// --- 7. Find Kth Largest Element (Reverse Inorder Traversal) ---
void findBSTKthLargest(struct node* root, int k) {
    // Stop if we hit NULL OR if the Kth element is already found
    if (root == NULL || count_kth >= k) {
        return;
    }

    // R (Right) - Visits largest elements first
    findBSTKthLargest(root->right, k);

    // N (Node)
    if (count_kth < k) {
        count_kth++;
        if (count_kth == k) {
            kth_element_result = root->data;
            return; // Found it, terminate the search
        }
    }

    // L (Left)
    findBSTKthLargest(root->left, k);
}

// =========================================================
//                  MAIN EXECUTION
// =========================================================

int main() {
    struct node* root = NULL; 
    
    // Initial Insertion
    root = insert(root, 50); 
    root = insert(root, 30); 
    root = insert(root, 20); 
    root = insert(root, 40); 
    root = insert(root, 70); 
    root = insert(root, 60); 
    root = insert(root, 80); 

    printf("Inorder traversal of the initial tree: \n"); 
    inorder(root); 
    printf("\n\n"); 

    // --- Min and Max Operations ---
    printf("--- Min/Max Operations ---\n");
    printf("Minimum Element: %d\n", findBSTMin(root)); // Output: 20
    printf("Maximum Element: %d\n", findBSTMax(root)); // Output: 80
    printf("\n");
    
    // --- Kth Smallest Operation ---
    int k_small = 3;
    count_kth = 0; // Reset global counter
    kth_element_result = -1; 
    findBSTKthSmallest(root, k_small);
    printf("--- Kth Smallest Operation ---\n");
    printf("%d-th Smallest Element: %d\n", k_small, kth_element_result); // Output: 40
    printf("\n");
    
    // --- Kth Largest Operation ---
    int k_large = 2;
    count_kth = 0; // Reset global counter
    kth_element_result = -1; 
    findBSTKthLargest(root, k_large);
    printf("--- Kth Largest Operation ---\n");
    printf("%d-th Largest Element: %d\n", k_large, kth_element_result); // Output: 70
    printf("\n");
    
    // --- Deletion Example (using original logic) ---
    printf("--- Deletion Operations (from original code) ---\n"); 
    printf("Delete 20\n"); 
    root = deletion(root, 20); 
    printf("Inorder traversal after deletion of 20: \n"); 
    inorder(root); 
    printf("\n"); 

    printf("Delete 30\n"); 
    root = deletion(root, 30); 
    printf("Inorder traversal after deletion of 30: \n"); 
    inorder(root); 
    printf("\n"); 

    printf("Delete 50\n"); 
    root = deletion(root, 50); 
    printf("Inorder traversal after deletion of 50: \n"); 
    inorder(root); 
    printf("\n"); 

    return 0;
}
