def smallsort(array):
    k = len(array)
    for i in range(k - 1):
        for j in range(k - 1 - i):
            if array[j] > array[j + 1]:
                array[j], array[j + 1] = array[j + 1], array[j]


fin = open("smallsort.in")
fout = open("smallsort.out", "w")
n = int(fin.readline())
arr = list(map(int, fin.readline().split()))
smallsort(arr)

for element in arr:
    print(element, end=' ', file = fout)

fin.close()
fout.close()
