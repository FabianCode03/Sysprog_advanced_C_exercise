#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

static ListNode *front = NULL;
static ListNode *back = NULL;

static bool listIsEmpty()
{
    if (front == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static ListNode *allocateSpaceForListNode()
{
    ListNode *newListNode = (ListNode *)malloc(sizeof(ListNode));
    if (newListNode == NULL)
    {
        perror("Fehler beim allokieren von speicher");
        return NULL;
    }
    else
    {
        return newListNode;
    }
}

static void initializeListNode(ListNode *newListNode, const char *name)
{
    strcpy(newListNode->name, name);
    newListNode->number[0] = '\0';
}

static bool userNameAlreadyTaken(const char *name)
{
    ListNode *temp = front;
    while (temp != NULL)
    {
        if (strcmp(temp->name, name) == 0)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

static ListNode *returnUserByName(const char *name)
{
    ListNode *temp = front;
    while (temp != NULL)
    {
        if (strcmp(temp->name, name) == 0)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

static bool userNameIsEmpty(const char *name)
{
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (name[i] != ' ')
        {
            return false;
        }
    }
    return true;
}

static bool validUserName(const char *name)
{
    if (!userNameAlreadyTaken(name) && !userNameIsEmpty(name))
    {
        return true;
    }
    else
    {
        return false;
    }
}

ListNode *listAdd(const char *name)
{
    if (validUserName(name))
    {
        ListNode *newListNode = allocateSpaceForListNode();
        initializeListNode(newListNode, name);

        if (listIsEmpty())
        {
            front = newListNode;
            back = newListNode;
            newListNode->next = NULL;
            newListNode->prev = NULL;
        }
        else
        {
            newListNode->prev = back;
            newListNode->next = NULL;
            back->next = newListNode;
            back = newListNode;
        }

        return newListNode;
    }
    else
    {
        puts("Ungültiger Name (schon vergeben oder leerer String)\n");
        return NULL;
    }
}

void listForEach(void (*func)(ListNode *))
{
    ListNode *temp = front;
    while (temp != NULL)
    {
        func(temp);
        temp = temp->next;
    }
    return;
}

int listRemoveByName(const char *name)
{
    ListNode *removedUser = returnUserByName(name);

    if (removedUser == NULL)
    {
        return -1;
    }

    else if (removedUser == front)
    {
        front = front->next;
        if (front != NULL)
        {
            front->prev = NULL;
        }
    }

    else if (removedUser == back)
    {
        back = back->prev;
        if (back != NULL)
        {
            back->next = NULL;
        }
    }

    else
    {
        ListNode *beforeRemoved = removedUser->prev;
        ListNode *afterRemoved = removedUser->next;

        beforeRemoved->next = afterRemoved;
        afterRemoved->prev = beforeRemoved;
    }

    free(removedUser);
    return 0;
}

void freeListNode(ListNode *node)
{
    free(node);
}

void listRemoveAll(void)
{
    listForEach(freeListNode);
}