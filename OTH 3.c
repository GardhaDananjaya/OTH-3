#include <stdio.h>
#include <stdlib.h>

struct node {
struct node *prev;
int data;
struct node *next;
};

typedef struct node Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = newNode->prev = newNode;
    return newNode;
}

void insertFirst(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node *last = (*head)->prev;
    newNode->next = *head;
    newNode->prev = last;
    last->next = newNode;
    (*head)->prev = newNode;
    *head = newNode;
}

void display(Node* head) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    Node *temp = head;
    do {
        printf("Address: %p, Data: %d\n", (void*)temp, temp->data);
        temp = temp->next;
    } while (temp != head);
}

void sort(Node **head) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }

    int count = 0;
    Node *temp = *head;
    do {
        count++;
        temp = temp->next;
    } while (temp != *head);

    Node **nodeArray = (Node **)malloc(count * sizeof(Node *));
    temp = *head;
    for (int i = 0; i < count; i++) {
        nodeArray[i] = temp;
        temp = temp->next;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (nodeArray[j]->data > nodeArray[j + 1]->data) {
                Node *tempNode = nodeArray[j];
                nodeArray[j] = nodeArray[j + 1];
                nodeArray[j + 1] = tempNode;
            }
        }
    }

    for (int i = 0; i < count; i++) {
        nodeArray[i]->next = nodeArray[(i + 1) % count];
        nodeArray[i]->prev = nodeArray[(i - 1 + count) % count];
    }

    *head = nodeArray[0];

    free(nodeArray);
}

int main() {
    int N, i, data;
    Node *head = NULL;
    printf("Enter number of elements: ");
    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &data);
        insertFirst(&head, data);
    }
    printf("\nList before sorting:\n");
    display(head);
    sort(&head);
    printf("\nList after sorting:\n");
    display(head);
    return 0;
}
