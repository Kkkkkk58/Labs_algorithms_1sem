def new_lamp(penult, last):
    return 2 * last - penult + 2


def binsearch(left, right):
    array = [0] * n
    array[0] = a
    for j in range(30):
        mid = (left + right) / 2
        array[1] = mid
        is_negative = 0
        for i in range(2, n):
            array[i] = new_lamp(array[i - 2], array[i - 1])
            if array[i] < 0:
                is_negative = 1
                break
        if is_negative:
            left = mid
        else:
            right = mid
    return array[-1]


fin = open("garland.in")
fout = open("garland.out", "w")

n, a = map(float, fin.readline().split())
n = int(n)
print(round(binsearch(0, a), 2), file=fout)

fin.close()
fout.close()
