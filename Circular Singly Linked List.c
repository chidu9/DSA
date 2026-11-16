#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct node *head = NULL;

struct node *createNode(int value)
{
    struct node *newNode = malloc(sizeof(struct node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->data = value;
    newNode->next = NULL;

    return newNode;
}

void display()
{
    struct node *current;

    if (head == NULL)
    {
        printf("List is empty!\n");
        return;
    }

    current = head;

    do
    {
        printf("%d -> ", current->data);
        current = current->next;
    } while (current != head);

    printf("(back to head)\n");
}

void insertBeginning()
{
    int value;
    struct node *newNode, *current;

    printf("Enter value: ");
    scanf("%d", &value);

    newNode = createNode(value);

    if (head == NULL)
    {
        head = newNode;
        newNode->next = head;
        return;
    }

    current = head;

    while (current->next != head)
        current = current->next;

    newNode->next = head;
    current->next = newNode;
    head = newNode;
}

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
        newNode->next = head;
        return;
    }

    current = head;

    while (current->next != head)
        current = current->next;

    current->next = newNode;
    newNode->next = head;
}

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

    if (head == NULL)
    {
        printf("Invalid position!\n");
        return;
    }

    current = head;

    for (i = 1; i < pos - 1 && current->next != head; i++)
        current = current->next;

    if (i != pos - 1)
    {
        printf("Invalid position!\n");
        return;
    }

    printf("Enter value: ");
    scanf("%d", &value);

    newNode = createNode(value);
    newNode->next = current->next;
    current->next = newNode;
}

void insertAfter()
{
    int key, value;
    struct node *current, *newNode;

    printf("Enter existing value: ");
    scanf("%d", &key);

    if (head == NULL)
    {
        printf("List is empty!\n");
        return;
    }

    current = head;

    do
    {
        if (current->data == key)
            break;

        current = current->next;
    } while (current != head);

    if (current->data != key)
    {
        printf("Value not found!\n");
        return;
    }

    printf("Enter new value: ");
    scanf("%d", &value);

    newNode = createNode(value);
    newNode->next = current->next;
    current->next = newNode;
}

void insertBefore()
{
    int key, value;
    struct node *current, *previous, *newNode;

    printf("Enter existing value: ");
    scanf("%d", &key);

    if (head == NULL)
    {
        printf("List is empty!\n");
        return;
    }

    if (head->data == key)
    {
        insertBeginning();
        return;
    }

    previous = head;
    current = head->next;

    while (current != head && current->data != key)
    {
        previous = current;
        current = current->next;
    }

    if (current == head)
    {
        printf("Value not found!\n");
        return;
    }

    printf("Enter new value: ");
    scanf("%d", &value);

    newNode = createNode(value);
    previous->next = newNode;
    newNode->next = current;
}

void deleteBeginning()
{
    struct node *current, *last;

    if (head == NULL)
    {
        printf("List is empty!\n");
        return;
    }

    if (head->next == head)
    {
        free(head);
        head = NULL;
        return;
    }

    last = head;

    while (last->next != head)
        last = last->next;

    current = head;
    head = head->next;
    last->next = head;

    free(current);
}

void deleteEnd()
{
    struct node *current, *previous;

    if (head == NULL)
    {
        printf("List is empty!\n");
        return;
    }

    if (head->next == head)
    {
        free(head);
        head = NULL;
        return;
    }

    previous = head;
    current = head->next;

    while (current->next != head)
    {
        previous = current;
        current = current->next;
    }

    previous->next = head;
    free(current);
}

void deletePosition()
{
    int pos, i;
    struct node *current, *previous;

    printf("Enter position: ");
    scanf("%d", &pos);

    if (head == NULL || pos < 1)
    {
        printf("Invalid position or empty list!\n");
        return;
    }

    if (pos == 1)
    {
        deleteBeginning();
        return;
    }

    previous = head;
    current = head->next;

    for (i = 2; i < pos && current != head; i++)
    {
        previous = current;
        current = current->next;
    }

    if (current == head)
    {
        printf("Invalid position!\n");
        return;
    }

    previous->next = current->next;
    free(current);
}

void deleteValue()
{
    int key;
    struct node *current, *previous;

    printf("Enter value to delete: ");
    scanf("%d", &key);

    if (head == NULL)
    {
        printf("List is empty!\n");
        return;
    }

    if (head->data == key)
    {
        deleteBeginning();
        return;
    }

    previous = head;
    current = head->next;

    while (current != head && current->data != key)
    {
        previous = current;
        current = current->next;
    }

    if (current == head)
    {
        printf("Value not found!\n");
        return;
    }

    previous->next = current->next;
    free(current);
}

void deleteGivenNode()
{
    int key;
    struct node *current, *nextNode, *previous;

    printf("Enter node value to delete: ");
    scanf("%d", &key);

    if (head == NULL)
    {
        printf("List is empty!\n");
        return;
    }

    current = head;

    do
    {
        if (current->data == key)
            break;

        current = current->next;
    } while (current != head);

    if (current->data != key)
    {
        printf("Node not found!\n");
        return;
    }

    if (current->next != current)
    {
        nextNode = current->next;

        if (current == head)
        {
            current->data = nextNode->data;
            current->next = nextNode->next;
            free(nextNode);
        }
        else
        {
            previous = head;

            while (previous->next != current)
                previous = previous->next;

            previous->next = current->next;
            free(current);
        }
    }
    else
    {
        free(current);
        head = NULL;
    }

    printf("Node deleted.\n");
}

void clearList()
{
    struct node *current, *nextNode;

    if (head == NULL)
        return;

    current = head->next;

    while (current != head)
    {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    free(head);
    head = NULL;

    printf("List cleared.\n");
}

void search()
{
    int key, pos = 1;
    struct node *current;

    printf("Enter value to search: ");
    scanf("%d", &key);

    if (head == NULL)
    {
        printf("List is empty!\n");
        return;
    }

    current = head;

    do
    {
        if (current->data == key)
        {
            printf("Found at position %d\n", pos);
            return;
        }

        current = current->next;
        pos++;
    } while (current != head);

    printf("Value not found!\n");
}

void countNodes()
{
    int count = 0;
    struct node *current;

    if (head == NULL)
    {
        printf("Number of nodes = 0\n");
        return;
    }

    current = head;

    do
    {
        count++;
        current = current->next;
    } while (current != head);

    printf("Number of nodes = %d\n", count);
}

void reverseList()
{
    struct node *previous, *current, *nextNode;

    if (head == NULL || head->next == head)
        return;

    previous = head;
    current = head->next;

    while (current != head)
    {
        nextNode = current->next;
        current->next = previous;
        previous = current;
        current = nextNode;
    }

    head->next = previous;
    head = previous;

    printf("List reversed.\n");
}

void concatenate()
{
    int n, i, value;
    struct node *secondHead = NULL, *last2 = NULL;
    struct node *current, *last1, *newNode;

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
            last2 = newNode;
        }
        else
        {
            last2->next = newNode;
            last2 = newNode;
        }
    }

    if (secondHead == NULL)
        return;

    last2->next = secondHead;

    if (head == NULL)
    {
        head = secondHead;
        return;
    }

    last1 = head;

    while (last1->next != head)
        last1 = last1->next;

    last1->next = secondHead;
    last2->next = head;

    printf("Lists concatenated.\n");
}

void sortList()
{
    struct node *current, *nextNode;
    int temp;

    if (head == NULL)
        return;

    current = head;

    do
    {
        nextNode = current->next;

        while (nextNode != head)
        {
            if (current->data > nextNode->data)
            {
                temp = current->data;
                current->data = nextNode->data;
                nextNode->data = temp;
            }

            nextNode = nextNode->next;
        }

        current = current->next;
    } while (current->next != head);

    printf("List sorted.\n");
}

int main()
{
    int choice;

    do
    {
        printf("\n===== CIRCULAR SINGLY LINKED LIST =====\n");
        printf("1. Create (insert at end)\n");
        printf("2. Display\n");
        printf("3. Insert Beginning\n");
        printf("4. Insert End\n");
        printf("5. Insert Position\n");
        printf("6. Insert After Value\n");
        printf("7. Insert Before Value\n");
        printf("8. Delete Beginning\n");
        printf("9. Delete End\n");
        printf("10. Delete Position\n");
        printf("11. Delete by Value\n");
        printf("12. Delete Given Node\n");
        printf("13. Clear List\n");
        printf("14. Search\n");
        printf("15. Count Nodes\n");
        printf("16. Reverse\n");
        printf("17. Concatenate\n");
        printf("18. Sort\n");
        printf("0. Exit\n");
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