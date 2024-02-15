# import numpy as np


# matrix = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]


# class Solution:
#     def rotateMatrix(m):
#         m1 = []
#         m = m[len(m)::-1]
#         i = 0
#         j = 0
#         for j in range(0, len(m[i])):
#             for i in range(0, len(m)):
#                 m1.append([m[i][j]])
#         m1 = np.array(m1)
#         m1 = m1.reshape(3, 3)
#         m = m1.tolist()
#         return m


# print(Solution.rotateMatrix(matrix))

# ----------------------------------------------------------------------------------------------

import numpy as np
myArray = np.array([[1, 2, 3, 21], [4, 5, 6, 22], [
                   7, 8, 9, 23], [10, 11, 12, 13]])


class Solution:
    def rotate(matrix) -> None:
        n = len(matrix)
        for layer in range(n//2):
            first = layer
            last = n-layer-1

            for i in range(first, last):
                top = matrix[layer][i]
                matrix[layer][i] = matrix[-i-1][layer]
                matrix[-i-1][layer] = matrix[-layer-1][-i-1]
                matrix[-layer-1][-i-1] = matrix[i][layer-1]
                matrix[i][layer-1] = top

        return matrix


print(Solution.rotate(myArray))
