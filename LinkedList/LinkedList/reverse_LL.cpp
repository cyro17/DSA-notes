#include <iostream>
using namespace std;

struct ListNode
{
    int data = 0;
    ListNode *next = NULL;

} *head = NULL;

ListNode *new_ListNode(int val)
{
    ListNode *temp = new ListNode();
    temp->data = val;
    temp->next = NULL;
    return temp;
}

ListNode *createLL(int *a, int n)
{
    ListNode *temp, *tail;
    ListNode *head = new_ListNode(a[0]);
    tail = head;

    for (int i = 0; i < n; i++)
    {
        temp = new_ListNode(a[i]);
        tail->next = temp;
        tail = temp;
    }
    return head->next;
}

void disp(ListNode *head)
{
    ListNode *temp = head;
    while (temp)
    {
        cout << temp->data << "->";
        temp = temp->next;
    }
    cout << "null" << endl;
}

ListNode *reverseRecursive(ListNode *head)
{

    if (head == NULL || head->next == NULL)
    {
        return head;
    }

    ListNode *newhead = reverseRecursive(head->next);
    head->next->next = head;
    head->next = NULL;

    return newhead;
}

int getLength(ListNode *head)
{
    int n = 0;
    ListNode *temp = head;
    while (temp != NULL)
    {
        n++;
        temp = temp->next;
    }
    return n;
}

ListNode *reverseKthListNode(ListNode *head, int k)
{
    if (head == NULL)
    {
        return NULL;
    }

    ListNode *prev = NULL, *curr = head, *nxt = NULL;
    int len = getLength(head);
    if (len < k)
        return head;

    int count = 0;
    while (curr && count < k)
    {
        nxt = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nxt;
        count++;
    }

    if (nxt != NULL)
    {
        head->next = reverseKthListNode(nxt, k);
    }

    return prev;
}

ListNode *floydDetectionCycle(ListNode *head)
{
    ListNode *slow = head;
    ListNode *fast = head;

    while (slow && fast->next)
    {
        slow = slow->next;
        fast = fast->next;

        if (slow == fast)
            return slow;
    }
    return NULL;
}

ListNode *detectFirstListNode(ListNode *head)
{
    if (!head || !head->next)
        return NULL;

    // if it contains a cycle or length >= 2
    ListNode *slow = head, *fast = head;

    do
    {
        slow = slow->next;
        fast = fast->next->next;
    } while (fast && fast->next && slow != fast);

    // if it does not contain a cycle
    if (!fast || !fast->next)
        return NULL;

    // find the beginning (h2 slow and fast me se kuch bhi le sakte the as h2 woh position hai jahan woh dono meet kar rahe hain)
    ListNode *h1 = head, *h2 = slow;

    while (h1 != h2)
    {
        h1 = h1->next;
        h2 = h2->next;
    }
    return h1;
}

ListNode *detectCycle(ListNode *head)
{
    if (!head || !head->next)
    {
        return NULL;
    }
    ListNode *slow = head, *fast = head;
    do
    {
        slow = slow->next;
        fast = fast->next;
    } while (fast && fast->next && slow != fast);

    if (!fast || !fast->next)
        return NULL;

    ListNode *temp = head;
    while (temp != slow)
    {
        temp = temp->next;
        slow = slow->next;
    }
    return slow;
}

int main()
{
    int a[] = {1, 2, 3, 4, 5, 6};
    ListNode *head = new ListNode;
    head = createLL(a, 6);
    disp(head);

    reverseKthListNode(head, 2);
    disp(head);
    return 0;
}