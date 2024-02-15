# Python program for the above approach

# Bucket sort for numbers
# having integer part
def bucketSort(arr, noOfBuckets):
    max_ele = max(arr)
    min_ele = min(arr)

    # range(for buckets)
    rnge = (max_ele - min_ele) / noOfBuckets

    temp = []

    # create empty buckets
    for i in range(noOfBuckets):
        temp.append([])

    # scatter the array elements
    # into the correct bucket
    for i in range(len(arr)):
        diff = (arr[i] - min_ele) / rnge - int((arr[i] - min_ele) / rnge)

        # append the boundary elements to the lower array
        if(diff == 0 and arr[i] != min_ele):
            temp[int((arr[i] - min_ele) / rnge) - 1].append(arr[i])

        else:
            temp[int((arr[i] - min_ele) / rnge)].append(arr[i])

    # Sort each bucket individually
    for i in range(len(temp)):
        if len(temp[i]) != 0:
            temp[i].sort()

    # Gather sorted elements
    # to the original array
    k = 0
    for lst in temp:
        if lst:
            for i in lst:
                arr[k] = i
                k = k+1


# Driver Code
arr = [11, 3, 9, 4, 15, 8, 7]
noOfBuckets = 5
bucketSort(arr, noOfBuckets)
print("Sorted array: ", arr)

# This code is contributed by
# Vinita Yadav
