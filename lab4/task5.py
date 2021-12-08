def binsearch_general(array, element, left, right):
    while left < right:
        mid = (left + right) // 2
        if array[mid] > element:
            right = mid
        elif array[mid] < element:
            left = mid + 1
        elif array[mid] == element:
            break
    if array[mid] == element:
        return mid
    else:
        return -1


def binsearch_left(array, element, left, right):
    while left < right - 1:
        mid = (left + right) // 2
        if array[mid] >= element:
            right = mid
        else:
            left = mid
    return right


def binsearch_right(array, element, left, right):
    while left < right - 1:
        mid = (left + right) // 2
        if array[mid] > element:
            right = mid
        else:
            left = mid
    return left


fin = open("binsearch.in")
fout = open("binsearch.out", "w")

n = int(fin.readline())
array = list(map(int, fin.readline().split()))
m = int(fin.readline())
requests = list(map(int, fin.readline().split()))

for element in requests:
    index = binsearch_general(array, element, 0, n)
    if index == -1:
        print("-1 -1", file=fout)
        continue
    if index > 0 and array[index - 1] == element:
        first = binsearch_left(array, element, -1, index - 1) + 1
    else:
        first = index + 1
    if index < n - 1 and array[index + 1] == element:
        last = binsearch_right(array, element, index, n) + 1
    else:
        last = index + 1
    print(first, last, file=fout)

fin.close()
fout.close()
