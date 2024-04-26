

/* Brute Force:
A straightforward approach to reversing a singly linked list requires an additional data structure
to temporarily store the values. We can use a stack for this. By pushing each node onto the stack
as we move through the list, we effectively reverse the order of the nodes. Once all the nodes
are stored in the stack, we rebuild the reversed linked list by popping nodes from the stack and assigning them to the nodes.
The result is a new linked list with the elements in the opposite order of the original list.

Time Complexity: O(2N)
Space Complexity: O(N)
 */

Node *reverseLinkedList(Node *head)
{
  Node *temp = head;
  stack<int> st;

  while (temp != nullptr)
  {
    st.push(temp->data);
    temp = temp->next;
  }

  temp = head;

  while (temp != nullptr)
  {
    temp->data = st.top();
    st.pop();
    temp = temp->next;
  }
  return head;
}

// Function to print the linked list
void printLinkedList(Node *head)
{
  Node *temp = head;
  while (temp != nullptr)
  {
    cout << temp->data << " ";
    temp = temp->next;
  }
  cout << endl;
}

/* Approach 2: Reverse Links in place (Iterative)

The previous approach uses O(N) addition space which can be avoided by interchanging the connecting links of the nodes of the linked list in place.
Time Complexity: O(N)
Space Complexity: O(1)
*/

Node *reverseLinkedList_opt1(Node *head)
{
  Node *temp = head;
  Node *prev = NULL;
  while (temp != NULL)
  {
    Node *front = temp->next;
    temp->next = prev;
    prev = temp;
    temp = front;
  }

  return prev;
}
