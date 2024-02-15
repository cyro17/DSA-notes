
# Binary Search Tree is a Binary tree where all tht nodes less than OR equal to are on left side and all the nodes greater than are o right side.

class BinarySearchTree:
    def __init__(self, data):
        self.left = self.right = None
        self.data = data

    def add_child(self, data):
        if data == self.data:
            return "The element already exist in the Tree."

        if data < self.data:
            if self.left:
                # call recursively the function to the left node
                self.left.add_child(data)
            else:
                self.left = BinarySearchTree(data)

        if data > self.data:
            if self.right:
                self.right.add_child(data)
            else:
                self.right = BinarySearchTree(data)

    def search(self, data) -> bool:
        if self.data == data:
            return True

        if data < self.data:
            if self.left:
                return self.left.search(data)
            else:
                return False

        if data > self.data:
            if self.right:
                return self.right.search(data)

    def preOrderTraversal(self):
        elements = []

        elements.append(self.data)
        if self.left:
            elements += self.left.preOrderTraversal()

        if self.right:
            elements += self.right.preOrderTraversal()

        return elements

    def postOrderTraversal(self):
        elements = []

        if self.left:
            elements += self.left.postOrderTraversal()

        if self.right:
            elements += self.right.postOrderTraversal()

        elements.append(self.data)

        return elements

    def find_min(self):
        if self.left is None:
            return self.data
        return self.left.find_min()

    def find_max(self):
        if self.right is None:
            return self.data
        return self.right.find_max()

    def find_Sum(self):
        ele = self.InOrderTraversal()
        sum = 0
        for i in ele:
            sum += i
            i += 1
        return sum


def build_tree(elements):
    root = BinarySearchTree(elements[0])
    for i in range(1, len(elements)):
        root.add_child(elements[i])
    return root


if __name__ == "__main__":
    num = [1, 3, 6, 19, 29]
    num_tree = build_tree(num)
    print(num_tree.preOrderTraversal())
    print(num_tree.InOrderTraversal())
    print(num_tree.PostOrderTraversal())
    print(num_tree.find_Sum())
