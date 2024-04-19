#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
  int data;
  Node *next;
  Node(int val, Node *next_)
  {
    data = val;
    next = next_;
  }

  Node(int val)
  {
    data = val;
    next = nullptr;
  }

  Node *convert2LL(vector<int> &arr)
  {
    Node *head = new Node(arr[0]);
    Node *mover = head;
    for (int i = 0; i < arr.size(); ++i)
    {
      Node *tmp = new Node(arr[i]);
      mover->next = tmp;
      mover = tmp;
    }
    return head;
  }

  int lengthLL(Node *head)
  {
    Node *tmp = head;
    int cnt = 0;
    while (tmp->next)
    {
      cnt++;
      tmp = tmp->next;
    }
    return cnt;
  }

  bool checkIfPresent(Node *head, int val)
  {
    Node *tmp = head;
    while (tmp->next)
    {
      if (tmp->data == val)
        return 1;
      tmp = tmp->next;
    }
    return 0;
  }

  Node *removesHead(Node *head)
  {
    if (head == NULL)
      return head;
    Node *temp = head;
    head = head->next;
    delete tmp;
    return head;
  }

  Node *removesTail(Node *head)
  {
    if (head == NULL || head->next == NULL)
      return NULL;

    Node *tmp = head;
    while (tmp->next->next)
    {
      tmp = tmp->next;
    }
    delete tmp->next;
    tmp->next = nullptr;

    return head;
  }

  Node *removeK(Node *head)
  {
    if (head == NULL)
      return head;
    if (k == 1)
      return removesHead(head);
    else
    {
      int cnt = 0;
      Node *tmp = head, *prev = nullptr;
      while (tmp)
      {
        cnt++;
        if (k == cnt)
        {
          prev->next = prev->next->next;
          delete tmp;
          break;
        }
        prev = tmp;
        tmp = tmp->next;
      }
    }
    return head;
  }

  Node *insertHead(Node *head, int val)
  {
    Node *tmp = new Node(val, head);
    return tmp;
  }

  Node *insertTail(Node *head, int val)
  {
    if (!head)
      return head;
    Node *tmp = head;
    whlie(tmp->next)
    {
      tmp = tmp->next;
    }
    Node *tail = new Node(val);
    tmp->next = tail;
    return head;
  }

  Node *insertK(Node *head, int k, int val)
  {
    if (k == 1)
      return insertHead(head);
    int cnt = 0;
    while (tmp)
    {
      cnt++;
      if (cnt == (k - 1))
      {
        Node *newnode = new Node(val, tmp->next);
        tmp->next = newnode;
        return head;
      }
      tmp = tmp->next;
    }
  }

  Node *insertBeforeValue(Node *head, int el, int val)
  {
    if (!head)
      return NULL;
    if (head->data == val)
      return insertHead(head, el);
    Node *tmp = head;
    while (tmp->next)
    {
      if (tmp->next->data == val)
      {
        Node *newnode = new Node(el, tmp->next);
        tmp->next = newnode;
        break;
      }
    }
    return head;
  }
};

int main()
{
  vector<int> arr{1, 2, 3, 4, 5};
  Node *n;
  Node *head = n->convert2LL(arr);
  cout << n->lengthLL(head);

  return 0;
}