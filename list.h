typedef struct listNode
{
    char name[32];
    char number[32];
    struct listNode *prev;
    struct listNode *next;
}listNode;
