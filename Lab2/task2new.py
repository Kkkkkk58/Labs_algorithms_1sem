def merge(array, left, right):
    i = j = k = 0

    while i < len(left) and j < len(right):
        if left[i][0] <= right[j][0]:
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


fin = open("race.in")
fout = open("race.out", "w")
n = int(fin.readline())
results = []

for i in range(n):
    results.append(list(fin.readline().split()))
mergesort(results)
country = ""

for runner in results:
    if country != runner[0]:
        print(f"=== {runner[0]} ===", file=fout)
        country = runner[0]
    print(runner[1], file=fout)

fin.close()
fout.close()
