/* using hashmap ds (node, val), if same node is visited twice, then cycle confirmed

Time Complexity: O(N * 2 * log(N) )The algorithm traverses the linked list once, performing hashmap insertions and searches in the while loop for each node. The insertion and search operations in the unordered_map have a worst-case time complexity of O(log(N)).
As the loop iterates through N nodes, the total time complexity is determined by the product of the traversal (O(N)) and the average-case complexity of the hashmap operations (insert and search), resulting in O(N * 2 * log(N)).

Space Complexity: O(N) The code uses a hashmap/dictionary
*/

bool detectLoop(Node *head)
{

  // Initialize a pointer 'temp'
  // at the head of the linked list
  Node *temp = head;

  // Create a map to keep track of
  // encountered nodes
  std::unordered_map<Node *, int> nodeMap;

  // Step 2: Traverse the linked list
  while (temp != nullptr)
  {
    // If the node is already in the
    // map, there is a loop
    if (nodeMap.find(temp) != nodeMap.end())
    {
      return true;
    }
    // Store the current node
    // in the map
    nodeMap[temp] = 1;

    // Move to the next node
    temp = temp->next;
  }

  // Step 3: If the list is successfully traversed
  // without a loop, return false
  return false;
}

/* Using slow and fast pointers

TC = O(N)
SC = O(1)
*/

bool detectCycle(Node *head)
{
  // Initialize two pointers, slow and fast,
  // to the head of the linked list
  Node *slow = head;
  Node *fast = head;

  // Step 2: Traverse the linked list with
  // the slow and fast pointers
  while (fast != nullptr && fast->next != nullptr)
  {
    // Move slow one step
    slow = slow->next;
    // Move fast two steps
    fast = fast->next->next;

    // Check if slow and fast pointers meet
    if (slow == fast)
    {
      return true; // Loop detected
    }
  }

  // If fast reaches the end of the list,
  // there is no loop
  return false;
}