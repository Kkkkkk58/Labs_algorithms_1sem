fin = open("isheap.in")
fout = open("isheap.out", "w")
n = int(fin.readline())
array = list(map(int, fin.readline().split()))

is_heap = True
for i in range(len(array) - 1, 0, -1):
    if array[i] < array[(i - 1) // 2]:
        is_heap = False
        break

if is_heap:
    print("YES", file=fout)
else:
    print("NO", file=fout)

fin.close()
fout.close()
