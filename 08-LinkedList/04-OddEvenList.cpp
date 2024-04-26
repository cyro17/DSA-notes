clss Node
{
  int val;
  Node *next;
  Node(int val, Node *next)
  {
    val = val;
    next = next;
  }
  Node(int val)
  {
    val = val;
    next = nullptr;
  }
}

Node *oddEvenList(Node *head)
{
  Node *odd = head, *even = head->next, *evenHead = even;
  while (even && even->next)
  {
    odd->next = even->next;
    odd = odd->next;
    even->next = odd->next;
    even = even->next;
  }
  odd->next = evenHead;
  return head;
}

int main()
