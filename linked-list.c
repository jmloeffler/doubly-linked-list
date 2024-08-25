#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "linked-list.h"

struct node* head;

void printUsage();
void push(char newItem);
char pop();
void insertAt(char newItem, int position);
void removeAt(int position);
struct node* locateNode(int position);
void print();

int main()
{
    char command, item;
    int position;
    head = NULL;

    printUsage();

    for (;;)
    {
        printf("command: ");
        scanf("%s", &command);
        switch (command)
        {
        case 'p':
            printf("\npush: ");
            scanf("%s", &item);
            push(item);
            break;
        case 'o':
            pop();
            break;
        case 'i':
            printf("\ninsert <X> at position <Y>: ");
            scanf("%s%i", &item, &position);
            insertAt(item, position);
            break;
        case 'r':
            printf("\nremove at position <X>: ");
            scanf("%i", &position);
            removeAt(position);
            break;
        case 'q':
            exit(EXIT_SUCCESS);
        default:
            printf("Invalid command\n");
            break;
        }

        print();
    }
}

void printUsage()
{
    printf("You are standing in an open field west of a white house, with a boarded front door. There is a small mailbox here.\n");
    printf("Your doubly-linked list is empty.\n");
    printf("Your commands are:\n");
    printf("p to push a character onto your list\n");
    printf("o to pop a character from the front of your list\n");
    printf("i to insert an item to a given position\n");
    printf("r to remove an item from a given position\n");
    printf("q to abandon your quest\n");

}

void push(char newItem)
{
    struct node *newNode = malloc(sizeof(struct node));

    if (!newNode)
    {
        printf("Memory allocation failure.");
        exit(EXIT_FAILURE);
    }

    newNode->value = newItem;
    newNode->next = head;
    newNode->prev = NULL;

    if(head != NULL){
        head->prev = newNode;
    }

    head = newNode;
}

char pop()
{
    if (head == NULL)
    {
        return '\0';
    }

    struct node *nodeToRemove = head;
    head = head->next;
    head->prev = NULL;
    char value = nodeToRemove->value;
    free(nodeToRemove);
    return value;
}

void insertAt(char newItem, int position)
{
    struct node *oldPredecessor;
    struct node *nodeAtPosition = locateNode(position);
    if(nodeAtPosition == NULL){
        printf("Invalid insertion position\n");
        return;
    }

    // found position x, insert node
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->value = newItem;
    newNode->next = nodeAtPosition;
    newNode->prev = nodeAtPosition->prev;

    //update the next pointer of the predecessor
    oldPredecessor = nodeAtPosition->prev;
    oldPredecessor->next = newNode;

    //update the prev pointer of the successor
    nodeAtPosition->prev = newNode;
}

void removeAt(int position)
{
    struct node *predecessor, *successor;
    struct node *nodeAtPosition = locateNode(position);
    if(nodeAtPosition == NULL){
        printf("Invalid removal position\n");
        return;
    }

    // found position x, remove node
    predecessor = nodeAtPosition->prev;
    successor = nodeAtPosition->next;
    predecessor->next = successor;
    successor->prev = predecessor;
    free(nodeAtPosition);
}

struct node* locateNode(int position)
{
    struct node *nodeAtPosition = head;
    for(int i = 0; i<position && nodeAtPosition != NULL; i++)
    {
        nodeAtPosition = nodeAtPosition->next;
    }
    return nodeAtPosition;
}

void print()
{
    printf("The list is currently: ");
    struct node *currentItem = head;
    while(currentItem != NULL)
    {
        printf("%c -> ", currentItem->value);
        currentItem = currentItem->next;
    }

    printf("End\n");
}
