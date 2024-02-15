#include "bits/stdc++.h"
using namespace std;

struct Node
{
    int val = 0;
    Node *next = NULL;

} *head = NULL;

// creating a linked list

void create(int *a, int n)
{
    struct Node *t, *tail;

    head = new Node();
    head->val = a[0];
    head->next = NULL;
    tail = head;

    int i;
    for (int i = 0; i < n; i++)
    {
        t = new Node();
        t->val = a[i];
        t->next = NULL;
        tail->next = t;
        tail = t;
    }
}

void display(struct Node *p)
{
    if (p)
    {
        // print elements of linked list
        cout << p->val << " ";
        display(p->next);
    }
    cout << endl;
}
// print in reverse order
void rev_disp(Node *p)
{

    if (!p)
    {
        rev_disp(p->next);
        cout << p->val << " ";
    }
}

int count(Node *p)
{
    if (!p)
        return 0;
    return count(p->next) + 1;
}

int sum(Node *p)
{
    if (!p)
        return 0;
    int temp = 0;

    if (p)
    {
        temp += (p->val);
        p = p->next;
    }
    return temp;
}

int max_Node(Node *p)
{
    int max_ = INT_MIN;
    if (!p)
    {
        return 0;
    }

    while (p)
    {
        max_ = max(p->val, max_);
        p = p->next;
    }
    return max_;
}

Node *find(Node *p, int k)
{
    while (p)
    {
        if (k = p->val)
            return p;
        p = p->next;
    }
    return 0;
}

Node *search(Node *p, int key)
{
    Node *q;
    q = new Node();
    while (p)
    {
        if (key == p->val)
        {
            q->next = p->next;
            p->next = head;
            head = p;
            return p;
        }
        q = p;
        q = q->next;
    }
}

void insert(Node *p, int pos, int val)
{

    Node *temp;
    temp = new Node();
    temp->val = val;

    if (pos == 0)
    {
        temp->next = head;
        head = temp;
    }

    else if (pos < 0 && pos > count(p))
        return;
    else
    {
        for (int i = 0; i < pos - 1; i++)
            p = p->next;
        temp->next = p->next;
        p->next = temp;
    }
}

void insertAtLast(Node *p, int val)
{

    Node *temp;
    temp = new Node();
    temp->val = val;
    while (p)
    {
        p = p->next;
    }
    p->next = temp;
    temp->next = NULL;
}

void insertsorted(Node *head, int x)
{
    Node *p, *q, *temp;
    p = head;

    temp = new Node();
    temp->val = x;

    if (!head)
        head = temp;

    else
    {
        while (p && p->val < x)
        {
            q = p;
            p = p->next;
        }
        if (p == head)
        {
            temp->next = head;
            head = temp;
        }
        else
        {
            temp->next = q->next;
            q->next = temp;
        }
    }
}

void deleteNode(Node *head, int pos)
{
    if (pos == 0)
    {
        Node *p = head;
        head = head->next;
        int x = p->val;
        delete p;
    }
    else
    {
        Node *p;
        Node *q;
        p = head;
        for (int i = 0; i < pos - 1; i++)
        {
            q = p;
            p = p->next;
        }
        q->next = p->next;
        int x = p->val;
        delete p;
    }
}

bool checkSorted(Node *head)
{
    int x = INT_MIN;
    Node *temp = head;
    while (temp && temp->next)
    {
        if (temp->val < x)
        {
            return false;
        }
        x = temp->val;
        temp = temp->next;
    }
    return true;
}

Node *removeDup(Node *head)
{
    Node *temp = head;
    if (!temp)
        return NULL;

    while (temp->next)
    {
        if (temp->val == temp->next->val)
        {
            temp->next = temp->next->next;
        }
        else
            temp = temp->next;
    }
    return head;
}
Node *reverseList(Node *head)
{
    Node *temp = head;
    Node *prev;
    while (temp != NULL)
    {
        Node *nxt = temp->next;
        temp->next = prev;
        prev = temp;
        temp = nxt;
    }
    head = prev;
    return prev;
}

Node *merge(Node *list1, Node *list2)
{
    Node *res, *last;
    if (list1->val < list2->val)
    {
        res = last = list1;
        list1 = list1->next;
        last->next = NULL;
    }
    else
    {
        res = last = list2;
        list2 = list2->next;
        last->next = NULL;
    }

    while (list1 && list2)
    {
        if (list1->val < list2->val)
        {
            last->next = list1;
            last = list1;
            list1 = list1->next;
            last->next = NULL;
        }
        else
        {
            last->next = list2;
            last = list2;
            list2 = list2->next;
            last->next = NULL;
        }
    }
    if (list1)
        last->next = list1;
    else
        last->next = list2;

    return res;
}
int main()
{

    int a[] = {3, 5, 0, 7, 7, 25, 32};
    create(a, 6);
    display(head);
    cout << endl;
    cout << count(head) << endl;
    // cout << "print in reverse order" << endl;
    // rev_disp(head);
    // cout << sum(head);

    // cout << max_Node(head) << endl;
    // cout << boolalpha << endl;
    // cout << find(head, 32) << endl;

    // insert(head, int pos, int val);
    // insert(head, 1, 200);
    // insertAtLast(head, 100);
    // display(head);
    // cout << count(head);

    // insertsorted(head, 30);
    // display(head);
    // cout << endl;
    // cout << count(head) << endl;

    // delete (head, 1);
    // display(head);
    // cout << endl;
    // cout << count(head) << endl;

    // deleteNode(head, 4);
    // display(head);
    // cout << endl;
    // cout << checkSorted(head);

    // cout << endl;
    // removeDup(head);
    // display(head);
    reverseList(head);
    display(head);
    return 0;
}