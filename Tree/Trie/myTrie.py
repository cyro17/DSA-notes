

class TrieNode:
    def __init__(self, char):
        self.char = char
        self.children = [None] * 30
        self.isEndofWord = False
        self.counter = 0


class Trie:
    def __init__(self) -> None:
        # create an empty node as rootnode in the Trie
        self.root = TrieNode("")

    def insert(self, word):
        curr = self.root

        for char in word:
            if char in curr.children:
                curr = curr.children[char]
            else:
                new_node = TrieNode(char)
                curr.children[char] = new_node
                curr = new_node

            curr.isEndofWord = True
            curr.counter += 1

    def dfs(self, node, prefix):
        if node.isEndOfWord:
            self.output.append(prefix + node.char, node.counter)

        for child in node.children.values():
            self.dfs(child, prefix + node.char)

    def query(self, x):
        self.output = []
        node = self.root

        for char in x:
            if char in node.children[char]:
                node = node.children[char]

            else:
                return []

        self.dfs(node, x[:-1])
        return sorted(self.output, key=lambda x: x[1], reverse=True)
