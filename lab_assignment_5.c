#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char letter;
    struct node* next;
} node;

// Returns number of nodes in the linkedList.
int length(node* head)
{
    int i = 0;
    node* current = head;
    while (current != NULL) { // traverses the list
        i++;
        current = current->next;
    }
    return i;
}

// Parses the string in the linkedList.
// If the linked list is head -> |a|->|b|->|c|,
// then toCString function will return "abc".
char* toCString(node* head)
{
    int len = length(head);
    char* str = (char*)malloc((len + 1) * sizeof(char)); // is allocated to the length
    int i = 0;
    node* current = head;
    while (current != NULL) { // traverses and copies the chars 
        str[i] = current->letter;
        current = current->next;
        i++;
    }
    str[i] = '\0';
    return str;
}

// Inserts character to the linkedlist.
// If the linked list is head -> |a|->|b|->|c|,
// then insertChar(&head, 'x') will update the linked list as follows:
// head -> |a|->|b|->|c|->|x|.
void insertChar(node** pHead, char c)
{
    node* newNode = (node*)malloc(sizeof(node)); // new node is allocated 
    newNode->letter = c;
    newNode->next = NULL;

    if (*pHead == NULL) {
        *pHead = newNode;
    } else {
        node* current = *pHead;
        while (current->next != NULL) { // traverses the linked list 
            current = current->next;
        }
        current->next = newNode;
    }
}

// Deletes all nodes in the linkedList.
void deleteList(node** pHead)
{
    node* current = *pHead;
    while (current != NULL) { // traverses the linked list and deallocates one by one
        node* nextNode = current->next;
        free(current);
        current = nextNode;
    }
    *pHead = NULL; // head is assigned NULL
}

int main(void)
{
    int i, strLen, numInputs;
    node* head = NULL;
    char* str;
    char c;
    FILE* inFile = fopen("input.txt", "r");

    fscanf(inFile, " %d\n", &numInputs);

    while (numInputs-- > 0) {
        fscanf(inFile, " %d\n", &strLen);
        for (i = 0; i < strLen; i++) {
            fscanf(inFile, " %c", &c);
            insertChar(&head, c);
        }

        str = toCString(head);
        printf("String is: %s\n", str);

        free(str);
        deleteList(&head);

        if (head != NULL) {
            printf("deleteList is not correct!");
            break;
        }
    }

    fclose(inFile);
    return 0;
}
