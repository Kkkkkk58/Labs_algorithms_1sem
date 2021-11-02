fin = open("turtle.in")   
fout = open("turtle.out", "w")

h, w = map(int, fin.readline().split())
field = [list(map(int, fin.readline().split()))]

for i in range(w - 2, -1, -1):
    field[0][i] += field[0][i + 1]

for i in range(1, h):
    field.append(list(map(int, fin.readline().split())))
    field[i][-1] += field[i - 1][-1]
    for j in range(w - 2, -1, -1):
        field[i][j] += max(field[i - 1][j], field[i][j + 1])

print(field[h - 1][0], file = fout)
fin.close()
fout.close()
print('kanec')
