maxlength = 0

def search_depth(element, length):
    global maxlength
    if element[0] != 0:
        search_depth(array[element[0] - 1], length + 1)
    if element[1] != 0:
        search_depth(array[element[1] - 1], length + 1)
    if element[0] == element[1]:
        maxlength = max(length, maxlength)


fin = open("height.in")
fout = open("height.out", "w")
n = int(fin.readline())
if n != 0:
    array = []
    for i in range(n):
        value, left, right = map(int, fin.readline().split())
        array.append([left, right])
    length = 1
    search_depth(array[0], length)
print(maxlength, file=fout)

fin.close()
fout.close()
