def merge(array, left, right):
    i = j = k = 0

    while len(left) > i and len(right) > j:
        if left[i] <= right[j]:
            array[k] = left[i]
            k += 1
            i += 1
        else:
            array[k] = right[j]
            k += 1
            j += 1

    if len(left) > i:
        array[k:] = left[i:]
    elif len(right) > j:
        array[k:] = right[j:]


def mergesort(array):
    if len(array) > 1:
        mid = len(array) // 2
        left = array[:mid]
        right = array[mid:]
        mergesort(left)
        mergesort(right)
        merge(array, left, right)
    return array


fin = open("sort.in")
fout = open("sort.out", "w")
n = int(fin.readline())
array = list(map(int, fin.readline().split()))

mergesort(array)
for i in range(len(array)):
    print(array[i], file=fout, end=' ')

fin.close()
fout.close()
