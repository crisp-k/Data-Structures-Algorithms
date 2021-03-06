#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *prev;
    struct node *next;
} node;

typedef struct list {
    struct node *head;
    struct node *tail;
} list;

list *createList(void)
{
    list *newList = (list *) malloc(sizeof(list));

    newList->head = NULL;
    newList->tail = NULL;

    return newList;
}

node *createNode(int data)
{
    node *newNode = (node *) malloc(sizeof(node));

    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

void printListForwards(list *list)
{
    node *traversal = list->head;

    if(traversal == NULL)
    {
        printf("List empty!\n");
        return;
    }

    // first time using a do-while loop out of neccessity honestly
    do
    {
        printf("%d ", traversal->data);
        traversal = traversal->next;
    } while(traversal != list->head);

    printf("\n");
}

void printListBackwards(list *list)
{
    node *traversal = list->tail;

    if(list->tail == NULL)
    {
        printf("List empty!\n");
        return;
    }

    do
    {
        printf("%d ", traversal->data);
        traversal = traversal->prev;
    } while(traversal != list->tail);

    printf("\n");
}

// passing the list as a whole for the sake of the user
list *insertFront(list *list, int data)
{
    node *newNode = createNode(data);

    if(list->head == NULL)
    {
        // we are considering this the first real initialization of the list, 
        // thus we create the next/prev here instead of elsewhere
        list->head = newNode;
        list->head->next = list->tail;
        list->head->prev = list->tail;

        list->tail = newNode;
        list->tail->next = list->head;
        list->tail->prev = list->tail;
    }
    else
    {
        // otherwise new node is now the head
        // tail is updated accordingly
        newNode->next = list->head;
        newNode->prev = list->tail;

        list->head->prev = newNode;
        list->tail->next = newNode;

        list->head = newNode;
    }

    return list;
}

list *insertEnd(list *list, int data)
{
    node *newNode = createNode(data);

    if(list->tail == NULL)
    {
        list->tail = newNode;
        list->tail->next = list->head;
        list->tail->prev = list->tail;

        list->head = newNode;
        list->head->next = list->tail;
        list->head->prev = list->tail;
    }
    else
    {
        newNode->next = list->head;
        newNode->prev = list->tail;

        list->tail->next = newNode;
        list->head->prev = newNode;

        list->tail = newNode;
    }

    return list;
}

list *insertAfter(list *list, int data, int insertData)
{
    node *traversal = list->head;

    while(traversal->data != data && traversal != list->tail)
        traversal = traversal->next;

    if(traversal->data == data)
    {
        node *newNode = createNode(insertData);

        newNode->next = traversal->next;
        newNode->prev = traversal;

        traversal->next = newNode;
        newNode->next->prev = newNode;
    }
    else
        printf("Desired data not found!\n");

    return list;
}

list *deleteNode(list *list, int data)
{
    if(list->head->data == data)
    {
        node *deleteNode = list->head;

        list->head = deleteNode->next;

        list->tail->next = list->head;
        list->head->prev = list->tail;

        free(deleteNode);

        return list;
    }
    else if(list->head == list->tail)
    {
        free(list->head);

        list->head = NULL;
        list->tail = NULL;

        return list;
    }

    node *traversal = list->head;

    while(traversal->next->data != data && traversal != list->tail)
        traversal = traversal->next;

    if(traversal->next->data == data)
    {
        node *deleteNode = traversal->next;

        traversal->next = deleteNode->next;
        deleteNode->next->prev = traversal;

        free(deleteNode);
    }
    else
        printf("Desired data not found!\n");

    return list;
}

node *search(list *list, int data)
{
    node *traversal = list->head;

    while(traversal->data != data && traversal != list->tail)
        traversal = traversal->next;

    if(traversal->data == data)
        return traversal;
    else
        printf("Desired data not found!\n");
    
    return NULL;
}

void updateNode(list *list, int data, int newData)
{
    node *traversal = list->head;

    while(traversal->data != data && traversal != list->tail)
        traversal = traversal->next;

    if(traversal->data == data)
        traversal->data = newData;
    else
        printf("Desired data not found!\n");
        
}

void sortList(list *list)
{
    node *traversal, *sweep;
    int temp;

    traversal = list->head;

    do
    {
        sweep = traversal;

        do
        {
            if(sweep->data <= traversal->data)
            {
                temp = sweep->data;
                sweep->data = traversal->data;
                traversal->data = temp;
            }

            sweep = sweep->next;

        } while(sweep != list->head);

        traversal = traversal->next;

    } while(traversal != list->head);
}

list *deleteList(list *list)
{
    while(list->head != list->tail)
        list = deleteNode(list, list->head->data);

    free(list->head);

    list->head = NULL;
    list->tail = NULL;

    return list;
}

int main(void)
{
    list *list = createList();

    for(int i = 0; i <= 10; i++)
    {
        list = insertFront(list, i * 10);
        list = insertAfter(list, i * 10, i + 5);
    }

    sortList(list);

    list = deleteList(list);

    printListForwards(list);
}