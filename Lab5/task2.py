def check_tree(element):
    ordered_nodes = [element]
    prev = [float("inf"), 0, 0]
    while len(ordered_nodes) > 0 or element[2] != 0:

        while element[1] != 0 and prev[1] != element[1]:
            element = tree_nodes[element[1] - 1]
            ordered_nodes.append(element)

        element = ordered_nodes.pop()
        if prev[0] != float("inf") and element[0] <= prev[0]:
            return False
        prev = element

        if element[2] != 0:
            element = tree_nodes[element[2] - 1]
            ordered_nodes.append(element)

    return True


fin = open("check.in")
fout = open("check.out", "w")
n = int(fin.readline())

if n == 0:
    print("YES", file=fout)
else:
    tree_nodes = []
    for i in range(n):
        value, left, right = map(int, fin.readline().split())
        tree_nodes.append([value, left, right])
    if check_tree(tree_nodes[0]):
        print("YES", file=fout)
    else:
        print("NO", file=fout)

fin.close()
fout.close()
