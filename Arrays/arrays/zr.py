from collections import Counter


def findDuplicate(arr):
    # Write your code here
    c = Counter(arr)
    for i in c:
        if (c[i] > 1):
            return i


if __name__ == '__main__':
    arr = [1, 2, 3, 4, 5, 2]
    s = findDuplicate(arr)
    print(s)
