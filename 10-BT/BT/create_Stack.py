#   create stack using list (no size limit)
#   T.C = O(1) , S.C = O(1)

class Stack:
    def __init__(self):
        self.list = []

    def __str__(self):
        values = self.list.reverse()
        values = [str(x) for x in self.list]
        return '\n'.join(values)

    def isEmpty(self):
        if self.list == []:
            return True
        else:
            return False

    def push(self, value):
        self.list.append(value)
        return "The element has been inserted succesfully."

    def pop(self):
        if self.isEmpty():
            return "There is no element in the list."
        else:
            return self.list.pop()

    def peek(self):
        if self.isEmpty():
            return "There is no element in the Stack."
        else:
            return self.last[len(self.list(len-1))]

    def delete(self):
        self.list = None


if __name__ == "__main":
    customStack = Stack()
    print(customStack.isEmpty())
    customStack.push(1)
    customStack.push(2)
    customStack.push(3)
    customStack.push(4)
    print(customStack)
    print("*"*50)
    customStack.pop()
    print(customStack)
