# # algorithm

# 1) Create an empty stack S.
# 2) Initialize current node as root
# 3) Push the current node to S and set current=current -> left until current is NULL
# 4) If current is NULL and stack is not empty then
#     a) Pop the top item from stack.
#     b) Print the popped item, set current=popped_item -> right
#     c) Go to step 3.
# 5) If current is NULL and stack is empty then we are done.

import create_Stack


class Solution:
    def inOrderTraversalWOrec(self, root):
        self.mystack = create_Stack.Stack()
        curr = root
        my_stack.push(curr)
        while curr != None:
            curr = curr.left

        if curr is None:
            x = my_stack.pop()
            print(x)
            curr = x.right


my_stack = create_Stack.Stack
