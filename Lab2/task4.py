fin = open("antiqs.in")
fout = open("antiqs.out", "w")

n = int(fin.readline())
data = [i for i in range(1, n + 1)]
for i in range(n):
    data[i], data[i // 2] = data[i // 2], data[i]
for i in range(n):
    print(data[i], end=' ', file=fout)

fin.close()
fout.close()
