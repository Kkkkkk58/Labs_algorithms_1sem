class Queue:
    def __init__(self):
        self.array = [0] * n
        self.head = 0
        self.tail = 0
        self.size = 0

    def push_in(self, value):
        if self.tail == n:
            self.tail = 0
        self.array[self.tail] = value
        self.tail += 1
        self.size += 1

    def pop_out(self):
        self.head += 1
        if self.head == n:
            self.head = 0
        self.size -= 1


def tree_height(root_element):
    height = 0
    queue = Queue()
    queue.push_in(root_element)

    while queue.size > 0:
        nodes_on_level = queue.size

        while nodes_on_level > 0:
            node = queue.array[queue.head]
            queue.pop_out()
            if node[0] != 0:
                queue.push_in(array[node[0] - 1])
            if node[1] != 0:
                queue.push_in(array[node[1] - 1])
            nodes_on_level -= 1

        height += 1

    return height


fin = open("height.in")
fout = open("height.out", "w")
n = int(fin.readline())

if n != 0:
    array = []
    for i in range(n):
        value, left, right = map(int, fin.readline().split())
        array.append([left, right])
    print(tree_height(array[0]), file=fout)
else:
    print(0, file=fout)

fin.close()
fout.close()
