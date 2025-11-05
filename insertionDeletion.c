// binary search tree insertion and deletion

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *left;
    struct node *right;
};

// --- Node Creation ---
struct node *createNode(int data)
{
    struct node *nn = (struct node *)malloc(sizeof(struct node));
    if (nn == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    nn->data = data;
    nn->left = NULL;
    nn->right = NULL;
    return nn;
}

// --- Insertion ---
struct node *insert(struct node *root, int data)
{
    if (root == NULL)
    {
        return createNode(data);
    }

    if (data < root->data)
    {
        root->left = insert(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = insert(root->right, data);
    }
    return root;
}

// --- Deletion Helper: Find Inorder Successor ---
struct node *findMin(struct node *root)
{
    struct node *current = root;
    // Loop down to find the leftmost leaf
    while (current && current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

// --- Deletion ---
struct node *deletion(struct node *root, int key)
{
    // 1. Base Case: Tree is empty or key is not found
    if (root == NULL)
    {
        printf("Key %d not found in the tree.\n", key);
        return root;
    }

    // 2. Recurse down to find the node
    if (key < root->data)
    {
        root->left = deletion(root->left, key);
    }
    else if (key > root->data)
    {
        root->right = deletion(root->right, key);
    }
    else
    {
        // 3. Node to be deleted is found (key == root->data)

        // Case 1 & 2: Node with only one child or no child
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp; // Return the non-NULL child (or NULL if leaf)
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }

        // Case 3: Node with two children
        // Get the inorder successor (smallest in the right subtree)
        struct node *temp = findMin(root->right);

        // Copy the inorder successor's data to this node
        root->data = temp->data;

        // Delete the inorder successor (now we are handling Case 1 or 2 recursively)
        root->right = deletion(root->right, temp->data);
    }
    return root;
}

// --- Traversal ---
void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// --- Main Execution ---
int main()
{
    struct node *root = NULL;

    // Initial Insertion
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("Inorder traversal of the initial tree: \n");
    inorder(root); // Output: 20 30 40 50 60 70 80
    printf("\n");

    // Deletion 1: Leaf Node
    printf("\n--- Deletion 1: Delete 20 (Leaf Node) ---\n");
    root = deletion(root, 20);
    printf("Inorder traversal after deletion of 20: \n");
    inorder(root); // Output: 30 40 50 60 70 80
    printf("\n");

    // Deletion 2: Node with 1 child (30 now only has right child 40)
    printf("\n--- Deletion 2: Delete 30 (Node with 1 Child) ---\n");
    root = deletion(root, 30);
    printf("Inorder traversal after deletion of 30: \n");
    inorder(root); // Output: 40 50 60 70 80
    printf("\n");

    // Deletion 3: Node with 2 children (Root 50)
    printf("\n--- Deletion 3: Delete 50 (Node with 2 Children/Root) ---\n");
    root = deletion(root, 50);
    printf("Inorder traversal after deletion of 50: \n");
    inorder(root); // Output: 40 60 70 80 (50 replaced by its successor, 60)
    printf("\n");

    // Deletion 4: Deleting a key that doesn't exist
    printf("\n--- Deletion 4: Delete 99 (Key not found) ---\n");
    root = deletion(root, 99);
    printf("Inorder traversal after attempted deletion: \n");
    inorder(root);
    printf("\n");

    return 0;
}
