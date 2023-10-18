typedef struct ListNode
{
    char name[32];
    char number[32];
    struct ListNode *prev;
    struct ListNode *next;
}ListNode;