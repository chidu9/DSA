#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *prev;
    struct node *next;
};

struct node *head = NULL;

/* Create a new node */
struct node *createNode(int value)
{
    struct node *newNode = malloc(sizeof(struct node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = NULL;

    return newNode;
}

/* Display */
void display()
{
    struct node *current = head;

    if (head == NULL)
    {
        printf("List is empty!\n");
        return;
    }

    printf("NULL <-> ");

    while (current != NULL)
    {
        printf("%d <-> ", current->data);
        current = current->next;
    }

    printf("NULL\n");
}

/* Insert at beginning */
void insertBeginning()
{
    int value;
    struct node *newNode;

    printf("Enter value: ");
    scanf("%d", &value);

    newNode = createNode(value);

    newNode->next = head;

    if (head != NULL)
        head->prev = newNode;

    head = newNode;
}

/* Insert at end */
void insertEnd()
{
    int value;
    struct node *newNode, *current;

    printf("Enter value: ");
    scanf("%d", &value);

    newNode = createNode(value);

    if (head == NULL)
    {
        head = newNode;
        return;
    }

    current = head;

    while (current->next != NULL)
        current = current->next;

    current->next = newNode;
    newNode->prev = current;
}

/* Insert at position */
void insertPosition()
{
    int value, pos, i;
    struct node *current, *newNode;

    printf("Enter position: ");
    scanf("%d", &pos);

    if (pos < 1)
    {
        printf("Invalid position!\n");
        return;
    }

    if (pos == 1)
    {
        insertBeginning();
        return;
    }

    current = head;

    for (i = 1; i < pos - 1 && current != NULL; i++)
        current = current->next;

    if (current == NULL)
    {
        printf("Invalid position!\n");
        return;
    }

    printf("Enter value: ");
    scanf("%d", &value);

    newNode = createNode(value);

    newNode->next = current->next;
    newNode->prev = current;

    if (current->next != NULL)
        current->next->prev = newNode;

    current->next = newNode;
}

/* Insert after a value */
void insertAfter()
{
    int key, value;
    struct node *current, *newNode;

    printf("Enter existing value: ");
    scanf("%d", &key);

    current = head;

    while (current != NULL && current->data != key)
        current = current->next;

    if (current == NULL)
    {
        printf("Value not found!\n");
        return;
    }

    printf("Enter new value: ");
    scanf("%d", &value);

    newNode = createNode(value);

    newNode->next = current->next;
    newNode->prev = current;

    if (current->next != NULL)
        current->next->prev = newNode;

    current->next = newNode;
}

/* Insert before a value */
void insertBefore()
{
    int key, value;
    struct node *current, *newNode;

    printf("Enter existing value: ");
    scanf("%d", &key);

    current = head;

    while (current != NULL && current->data != key)
        current = current->next;

    if (current == NULL)
    {
        printf("Value not found!\n");
        return;
    }

    printf("Enter new value: ");
    scanf("%d", &value);

    newNode = createNode(value);

    newNode->next = current;
    newNode->prev = current->prev;

    if (current->prev != NULL)
        current->prev->next = newNode;
    else
        head = newNode;

    current->prev = newNode;
}

/* Delete beginning */
void deleteBeginning()
{
    struct node *current;

    if (head == NULL)
    {
        printf("List is empty!\n");
        return;
    }

    current = head;
    head = head->next;

    if (head != NULL)
        head->prev = NULL;

    free(current);
}

/* Delete end */
void deleteEnd()
{
    struct node *current;

    if (head == NULL)
    {
        printf("List is empty!\n");
        return;
    }

    current = head;

    while (current->next != NULL)
        current = current->next;

    if (current->prev != NULL)
        current->prev->next = NULL;
    else
        head = NULL;

    free(current);
}

/* Delete at position */
void deletePosition()
{
    int pos, i;
    struct node *current;

    printf("Enter position: ");
    scanf("%d", &pos);

    if (pos < 1 || head == NULL)
    {
        printf("Invalid position or empty list!\n");
        return;
    }

    current = head;

    for (i = 1; i < pos && current != NULL; i++)
        current = current->next;

    if (current == NULL)
    {
        printf("Invalid position!\n");
        return;
    }

    if (current->prev != NULL)
        current->prev->next = current->next;
    else
        head = current->next;

    if (current->next != NULL)
        current->next->prev = current->prev;

    free(current);
}

/* Delete by value */
void deleteValue()
{
    int key;
    struct node *current = head;

    printf("Enter value to delete: ");
    scanf("%d", &key);

    while (current != NULL && current->data != key)
        current = current->next;

    if (current == NULL)
    {
        printf("Value not found!\n");
        return;
    }

    if (current->prev != NULL)
        current->prev->next = current->next;
    else
        head = current->next;

    if (current->next != NULL)
        current->next->prev = current->prev;

    free(current);
}

/* Delete a given node using its pointer */
void deleteGivenNode()
{
    int key;
    struct node *current = head;

    printf("Enter value of node to delete: ");
    scanf("%d", &key);

    while (current != NULL && current->data != key)
        current = current->next;

    if (current == NULL)
    {
        printf("Node not found!\n");
        return;
    }

    if (current->prev != NULL)
        current->prev->next = current->next;
    else
        head = current->next;

    if (current->next != NULL)
        current->next->prev = current->prev;

    free(current);

    printf("Node deleted.\n");
}

/* Clear entire list */
void clearList()
{
    struct node *current;

    while (head != NULL)
    {
        current = head;
        head = head->next;
        free(current);
    }

    printf("List cleared.\n");
}

/* Search */
void search()
{
    int key, pos = 1;
    struct node *current = head;

    printf("Enter value to search: ");
    scanf("%d", &key);

    while (current != NULL)
    {
        if (current->data == key)
        {
            printf("Found at position %d\n", pos);
            return;
        }

        current = current->next;
        pos++;
    }

    printf("Value not found!\n");
}

/* Count nodes */
void countNodes()
{
    int count = 0;
    struct node *current = head;

    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    printf("Number of nodes = %d\n", count);
}

/* Reverse */
void reverseList()
{
    struct node *current = head;
    struct node *temp;

    while (current != NULL)
    {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;

        current = current->prev;
    }

    if (head != NULL)
        head = temp == NULL ? head : head;

    /* Find the new head */
    current = head;

    if (current != NULL)
    {
        while (current->prev != NULL)
            current = current->prev;

        head = current;
    }

    printf("List reversed.\n");
}

/* Concatenate another list */
void concatenate()
{
    int n, i, value;
    struct node *secondHead = NULL;
    struct node *current, *newNode;

    printf("Number of nodes in second list: ");
    scanf("%d", &n);

    if (n < 0)
    {
        printf("Invalid number!\n");
        return;
    }

    for (i = 0; i < n; i++)
    {
        printf("Enter value: ");
        scanf("%d", &value);

        newNode = createNode(value);

        if (secondHead == NULL)
        {
            secondHead = newNode;
            current = newNode;
        }
        else
        {
            current->next = newNode;
            newNode->prev = current;
            current = newNode;
        }
    }

    if (head == NULL)
        head = secondHead;
    else if (secondHead != NULL)
    {
        current = head;

        while (current->next != NULL)
            current = current->next;

        current->next = secondHead;
        secondHead->prev = current;
    }

    printf("Lists concatenated.\n");
}

/* Sort in ascending order */
void sortList()
{
    struct node *current, *nextNode;
    int temp;

    for (current = head; current != NULL; current = current->next)
    {
        for (nextNode = current->next;
             nextNode != NULL;
             nextNode = nextNode->next)
        {
            if (current->data > nextNode->data)
            {
                temp = current->data;
                current->data = nextNode->data;
                nextNode->data = temp;
            }
        }
    }

    printf("List sorted.\n");
}

/* Main function */
int main()
{
    int choice;

    do
    {
        printf("\n===== DOUBLY LINKED LIST =====\n");
        printf("1.  Create list (insert elements at end)\n");
        printf("2.  Display\n");
        printf("3.  Insert Beginning\n");
        printf("4.  Insert End\n");
        printf("5.  Insert Position\n");
        printf("6.  Insert After Value\n");
        printf("7.  Insert Before Value\n");
        printf("8.  Delete Beginning\n");
        printf("9.  Delete End\n");
        printf("10. Delete Position\n");
        printf("11. Delete by Value\n");
        printf("12. Delete Given Node\n");
        printf("13. Clear List\n");
        printf("14. Search\n");
        printf("15. Count Nodes\n");
        printf("16. Reverse\n");
        printf("17. Concatenate\n");
        printf("18. Sort\n");
        printf("0.  Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1: insertEnd(); break;
            case 2: display(); break;
            case 3: insertBeginning(); break;
            case 4: insertEnd(); break;
            case 5: insertPosition(); break;
            case 6: insertAfter(); break;
            case 7: insertBefore(); break;
            case 8: deleteBeginning(); break;
            case 9: deleteEnd(); break;
            case 10: deletePosition(); break;
            case 11: deleteValue(); break;
            case 12: deleteGivenNode(); break;
            case 13: clearList(); break;
            case 14: search(); break;
            case 15: countNodes(); break;
            case 16: reverseList(); break;
            case 17: concatenate(); break;
            case 18: sortList(); break;
            case 0: clearList(); printf("Program terminated.\n"); break;
            default: printf("Invalid choice!\n");
        }

    } while (choice != 0);

    return 0;
}
