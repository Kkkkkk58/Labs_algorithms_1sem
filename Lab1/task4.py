def qsort(array):
    if len(array) < 2:
        return array

    pivot = array[len(array) // 2]
    less = []
    more = []
    equal = []
    for elem in array:
        if elem == pivot:
            equal.append(elem)
        elif elem > pivot:
            more.append(elem)
        else:
            less.append(elem)

    return qsort(less) + equal + qsort(more)
"""""
fin = open("smallsort.in")
fout = open("smallsort.out", "w")
n = int(fin.readline())
arr = list(map(int, fin.readline().split()))
arr = qsort(arr)

for element in arr:
    print(element, end=' ', file = fout)

fin.close()
fout.close()
"""""
n = int(input())
arr = list(map(int, input().split()))
print(arr)
arr = qsort(arr)

for element in arr:
    print(element, end=' ')






