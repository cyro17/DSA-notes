

def sort(arr):
    global n
    n = len(arr)

    for i in range(n):
        swapped = False
        for j in range(n-i-1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
                swapped = True
        if swapped == False:
            break
    return arr


def findMin(arr):
    global n
    slow = 0
    fast = 1
    diff = arr[fast] - arr[slow]
    for i in range(n):
        if fast == n:
            break
        temp = arr[fast]-arr[slow]
        if temp < diff:
            diff = temp
        slow += 1
        fast += 1
    return diff


t = int(input())

for i in range(t):
    n = int(input())
    skills = list(map(int, input("").split()))
    # print(skills)
    sort(skills)
    diff = findMin(skills)
    print(diff)

# arr = [1, 0, 9, 5, 6, 7]
# sort(arr)
# print(findMin(arr))
