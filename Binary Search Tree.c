#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *left;
    struct node *right;
};

struct node* createNode(int value)
{
    struct node *newNode;
    newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct node* insert(struct node *root, int value)
{
    if (root == NULL)
        return createNode(value);
    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);
    return root;
}

void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(struct node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct node *root)
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

void levelOrder(struct node *root)
{
    struct node *queue[100];
    int front = 0, rear = 0;
    struct node *current;
    if (root == NULL)
       return;
    queue[rear++] = root;
    while (front < rear)
    {
        current = queue[front++];

        printf("%d ", current->data);

        if (current->left != NULL)
            queue[rear++] = current->left;

        if (current->right != NULL)
            queue[rear++] = current->right;
    }
}

int findSmallest(struct node *root)
{
    if (root == NULL)
        return -1;

    while (root->left != NULL)
        root = root->left;
    return root->data;
}

int findLargest(struct node *root)
{
    if (root == NULL)
        return -1;
    while (root->right != NULL)
        root = root->right;

    return root->data;
}

int Height(struct node *root)
{
    int leftheight, rightheight;

    if (root == NULL)
        return 0;

    leftheight = Height(root->left);
    rightheight = Height(root->right);

    if (leftheight > rightheight)
        return leftheight + 1;
    else
        return rightheight + 1;
}

int countLeaf(struct node *root)
{
    if (root == NULL)
        return 0;

    if (root->left == NULL && root->right == NULL)
        return 1;

    return countLeaf(root->left) +
           countLeaf(root->right);
}

int countNonLeaf(struct node *root)
{
    if (root == NULL)
        return 0;

    if (root->left == NULL && root->right == NULL)
        return 0;

    return 1 + countNonLeaf(root->left)
             + countNonLeaf(root->right);
}

void deleteTree(struct node *root)
{
    if (root != NULL)
    {
        deleteTree(root->left);
        deleteTree(root->right);
        printf("Deleting node: %d\n", root->data);
        free(root);
    }
}

int main()
{
    struct node *root = NULL;
    int n, value, i;
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    printf("Enter node values:\n");

    for (i = 0; i < n; i++)
    {
        scanf("%d", &value);
        root = insert(root, value);
    }

    printf("\n--- BST OPERATIONS ---\n");

    printf("\na. Inorder Traversal: ");
    inorder(root);

    printf("\nb. Preorder Traversal: ");
    preorder(root);

    printf("\nc. Postorder Traversal: ");
    postorder(root);

    printf("\nd. Level Order Traversal: ");
    levelOrder(root);
    printf("\ne. Smallest Element: %d", findSmallest(root));
    printf("\nf. Largest Element: %d", findLargest(root));
    printf("\ng. Height of BST: %d", Height(root));
    printf("\nh. Total Leaf Nodes: %d", countLeaf(root));
    printf("\ni. Total Non-Leaf Nodes: %d", countNonLeaf(root));
    printf("\n\n--- Deleting BST ---\n");
    deleteTree(root);
    root = NULL;
    return 0;
}