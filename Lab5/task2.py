def check_tree(element):
    if element[1] != 0:
        check_tree(array[element[1] - 1])
    if len(ordered_array) > 0:
        if ordered_array[-1] >= element[0]:
            return False
    ordered_array.append(element[0])
    if element[2] != 0:
        check_tree(array[element[2] - 1])
    return True

fin = open("check.in")
fout = open("check.out", "w")
n = int(fin.readline())

if n == 0:
    print("YES", file=fout)
else:
    array = []
    for i in range(n):
        value, left, right = map(int, fin.readline().split())
        array.append([value, left, right])
    ordered_array = []
    if check_tree(array[0]):
        print("YES", file=fout)
    else:
        print("NO", file=fout)

fin.close()
fout.close()
