def check_tree(element, min_value, max_value):
    if element[0] < min_value or element[0] > max_value:
        return False
    left_correct = right_correct = True
    if element[1] != 0:
        left_correct = check_tree(array[element[1] - 1], min_value, element[0] - 1)
    if element[2] != 0:
        right_correct = check_tree(array[element[2] - 1], element[0] + 1, max_value)
    return left_correct and right_correct


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
    if check_tree(array[0], -10 ** 9 - 1, 10 ** 9 + 1):
        print("YES", file=fout)
    else:
        print("NO", file=fout)

fin.close()
fout.close()
