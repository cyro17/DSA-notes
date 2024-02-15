#  topological sort using hashmap


from collections import defaultdict


class Graph_:
    def __init__(self, vertices) -> None:
        self.graph = defaultdict(list)
        self.v = vertices  # no of vertices

    def addEdge(self, u, v):
        self.graph[u].append(v)

    def topologicalSort(self):
        # create a visited array and mark it with False
        visited = [False] * self.v
        stack = []                      # an empty stack to store the neighbour values
        for i in range(self.v):
            if visited[i] == False:
                self.topologocalSortUtil(i, visited, stack)
        print(stack[::-1])

    def topologocalSortUtil(self, j, visited, stack):
        visited[j] = True
        for i in self.graph[j]:
            if visited[i] == False:
                self.topologocalSortUtil(i, visited, stack)
        stack.append(j)


# Driver code
if __name__ == "__main__":
    graph = Graph_(5)
    graph.addEdge(0, 1)
    graph.addEdge(0, 3)
    graph.addEdge(1, 2)
    graph.addEdge(2, 3)
    graph.addEdge(2, 4)
    graph.addEdge(3, 4)

    print("The Topological Sort Of The Graph Is:  ")

    graph.topologicalSort()
