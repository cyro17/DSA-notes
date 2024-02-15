

class Graph_:
    def __init__(self, gdict=None):
        if gdict is None:
            gdict = {}
        self.gdict = gdict

    def bfs(self, start, end):
        queue = []
        queue.append([start])
        while queue:
            path = queue.pop(0)
            print('path : ', path)
            node = path[-1]
            print('node : ', node)
            if node == end:
                return path

            for adj in self.gdict.get(node, []):
                new_path = list(path)
                new_path.append(adj)
                queue.append(new_path)


if __name__ == "__main__":
    custDict = {'a': ['b', 'c'],
                'b': ['d', 'g'],
                'c': ['d', 'e'],
                'd': ['f'],
                'e': ['f'],
                'g': ['f']
                }
    g = Graph_(custDict)
    print(g.bfs('a', 'f'))
