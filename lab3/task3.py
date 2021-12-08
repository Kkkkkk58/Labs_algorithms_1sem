def counting_sort(array, area, index):
    counting_array = [0] * area
    sorted_array = [0] * len(array)

    for j in range(len(array)):
        counting_array[ord(array[j][index]) - ord("a")] += 1
    for j in range(1, area):
        counting_array[j] += counting_array[j - 1]
    for j in range(len(array) - 1, -1, -1):
        sorted_array[counting_array[ord(array[j][index]) - ord("a")] - 1] = array[j]
        counting_array[ord(array[j][index]) - ord("a")] -= 1
    return sorted_array


def radix_sort(array, length, phase, area):
    counter = 0
    for i in range(length, -1, -1):
        if counter < phase:
            array = counting_sort(array, area, i)
            counter += 1
        else:
            break
    return array


fin = open("radixsort.in")
fout = open("radixsort.out", "w")
n, m, k = map(int, fin.readline().split())
array = [0] * n
for i in range(n):
    array[i] = fin.readline().rstrip("\n")
area = 26

array = radix_sort(array, m - 1, k, area)
for i in range(n):
    print(array[i], file=fout)

fin.close()
fout.close()
