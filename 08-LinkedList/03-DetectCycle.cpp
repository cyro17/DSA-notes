/* using hashmap ds (node, val), if same node is visited twice, then cycle confirmed

Time Complexity: O(N * 2 * log(N) )The algorithm traverses the linked list once, performing hashmap
insertions and searches in the while loop for each node. The insertion and search operations in the unordered_map have a worst-case time complexity of O(log(N)).
As the loop iterates through N nodes, the total time complexity is determined by the product of the traversal (O(N)) and the average-case complexity of the hashmap operations (insert and search)
, resulting in O(N * 2 * log(N)).

Space Complexity: O(N) The code uses a hashmap/dictionary
*/

bool detectLoop(Node *head)
{
  Node *temp = head;
  unordered_map<Node *, int> nodeMap;

  while (temp != nullptr)
  {

    if (nodeMap.find(temp) != nodeMap.end())
    {
      return true;
    }
    nodeMap[temp] = 1;
    temp = temp->next;
  }
  return false;
}

/* Using slow and fast pointers

TC = O(N)
SC = O(1)
*/

bool detectCycle(Node *head)
{
  Node *slow = head;
  Node *fast = head;

  while (fast != nullptr && fast->next != nullptr)
  {

    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast)
    {
      return true; // Loop detected
    }
  }
  return false;
}