def bubble(array):
    k = len(array)
    for i in range(k - 1):
        for j in range(k - 1 - i):
            if array[j][0] > array[j + 1][0]:
                array[j], array[j + 1] = array[j + 1], array[j]

fin = open("sortland.in")
fout = open("sortland.out", "w")
n = int(fin.readline())
arr = list(map(float, fin.readline().split()))
for i in range(n):
    arr[i] = [arr[i], i + 1]
bubble(arr)

print(arr[0][1], arr[n // 2][1], arr[n - 1][1], file = fout)

fin.close()
fout.close()
