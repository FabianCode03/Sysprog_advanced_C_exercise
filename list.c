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

static ListNode *allocateSpaceForListnode()
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
    // newListNode->name = name;
    // newListNode->number = "";
}

ListNode *listAdd(const char *name)
{
    ListNode *newListNode = allocateSpaceForListnode();
    initializeListNode(newListNode, name);

    if (listIsEmpty())
    {
        front = newListNode;
        back = newListNode;
    }
    else
    {
        back->next = newListNode;
        back = newListNode;
    }

    return newListNode;
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