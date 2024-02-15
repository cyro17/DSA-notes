d = {0: 6, 1: 2, 2: 5, 3: 5, 4: 4, 5: 5, 6: 6, 7: 3, 8: 7, 9: 6}


def Solution(temp):
    sol = 0
    while temp > 0:
        r = temp % 10
        sol = sol+d[r]
        temp = temp//10
    return sol


t = int(input())


def main():
    for i in range(t):
        a, b = map(int, input().split(" "))
        temp_sum = a + b
        n = Solution(temp_sum)
        print(n)
    return 0


main()




