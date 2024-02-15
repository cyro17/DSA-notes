t = int(input())
for i in range(t):
    d, n = map(int, input().split())
    print(d)
    res = sum(n)
    for i in range(d-1):
        res = sum(res)


def sum(n):
    sum = map(int, (n*n+1)/2)
    return sum
