

/* Brute Force:
A straightforward approach to reversing a singly linked list requires an additional data structure
to temporarily store the values. We can use a stack for this. By pushing each node onto the stack
as we move through the list, we effectively reverse the order of the nodes. Once all the nodes
are stored in the stack, we rebuild the reversed linked list by popping nodes from the stack and assigning them to the nodes.
The result is a new linked list with the elements in the opposite order of the original list.

Time Complexity: O(2N)
Space Complexity: O(N)
 */

class Node
{
public:
  // Data stored in the node
  int data;

  // Pointer to the next node in the list
  Node *next;

  // Constructor with both data and
  // next node as parameters
  Node(int data1, Node *next1)
  {
    data = data1;
    next = next1;
  }

  // Constructor with only data as a
  // parameter, sets next to nullptr
  Node(int data1)
  {
    data = data1;
    next = nullptr;
  }
};

// Function to reverse the
// linked list using a stack
Node *reverseLinkedList(Node *head)
{
  // Create a temporary pointer
  // to traverse the linked list
  Node *temp = head;

  // Create a stack to temporarily
  // store the data values
  stack<int> st;

  // Step 1: Push the values of the
  // linked list onto the stack
  while (temp != nullptr)
  {
    // Push the current node's
    // data onto the stack
    st.push(temp->data);

    // Move to the next node
    // in the linked list
    temp = temp->next;
  }

  // Reset the temporary pointer to
  // the head of the linked list
  temp = head;

  // Step 2: Pop values from the stack
  // and update the linked list
  while (temp != nullptr)
  {
    // Set the current node's data to
    // the value at the top of the stack
    temp->data = st.top();

    // Pop the top element from the stack
    st.pop();

    // Move to the next node
    // in the linked list
    temp = temp->next;
  }

  // Return the new head of
  // the reversed linked list
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
  // Initialize'temp' at
  // head of linked list
  Node *temp = head;

  // Initialize pointer 'prev' to NULL,
  // representing the previous node
  Node *prev = NULL;

  // Traverse the list, continue till
  // 'temp' reaches the end (NULL)
  while (temp != NULL)
  {
    // Store the next node in
    // 'front' to preserve the reference
    Node *front = temp->next;

    // Reverse the direction of the
    // current node's 'next' pointer
    // to point to 'prev'
    temp->next = prev;

    // Move 'prev' to the current
    // node for the next iteration
    prev = temp;

    // Move 'temp' to the 'front' node
    // advancing the traversal
    temp = front;
  }

  // Return the new head of
  // the reversed linked list
  return prev;
}
