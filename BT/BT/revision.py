#  create stack using python List.

# isEmpty(), push(), pop(), peek(), delete()


class Stack:
    def __init__(self):
        self.List = []

    def __str__(self) -> str:
        values = self.List.reverse()
        values = [str(x) for x in self.List]
        return '/n'.join(values)

    def isEmpty(self):
        if self.List == []:
            return True
        else:
            return False

    def push(self, value):
        self.List.append(value)
        return " The value has been inserted successfully."

    def pop(self):
        if self.List.
