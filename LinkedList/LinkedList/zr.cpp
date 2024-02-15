#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *next;
};

class CLL
{
private:
    Node *head;

public:
    CLL(int a[], int n);
    void disp();
    void rec_disp(Node *head);
    Node *get_head(){return head};
};

CLL ::CLL(int *a, int n)
{
    Node *t;
    Node *tail;

    head = new Node;
    head->data = a[0];
    head->next = head;
    tail = head;

    for (int i = 0; i < n; i++)
    {
        t = new Node;
        t->data = a[i];
        t->next = t;
        tail = t;
    }
}

void CLL::disp()
{
    Node *p = head;
    do
    {
        cout << p->data << " -> " << flush;
        p = p->next;
    } while (p != head);
    cout << endl;
}

int main()
{

    return 0;
}