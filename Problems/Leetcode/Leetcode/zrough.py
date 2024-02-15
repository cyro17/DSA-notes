

# n = list(map(int, input().split()))

def fun(l):
    sum = 0
    for i in l:
        sum += i

    return sum


if __name__ == '__main__':
    l = [int(i) for i in input().split()]
    # print(len(l))
    print(fun(l))
