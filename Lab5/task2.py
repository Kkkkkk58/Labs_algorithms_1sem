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


def check_tree(root_element):
    is_correct = True
    queue = Queue()
    queue.push_in(root_element)
    while queue.size > 0:
        nodes_on_level = queue.size
        while nodes_on_level > 0:
            node = queue.array[queue.head]
            queue.pop_out()
            if node[1] != 0:
                left_child = array[node[1] - 1]
                if left_child[0] >= node[0]:
                    is_correct = False
                    break
                queue.push_in(left_child)
            if node[2] != 0:
                right_child = array[node[2] - 1]
                if right_child[0] <= node[0]:
                    is_correct = False
                    break
                queue.push_in(right_child)
            nodes_on_level -= 1
        if not is_correct:
            break
    return is_correct



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
    if check_tree(array[0]):
        print("YES", file=fout)
    else:
        print("NO", file=fout)

fin.close()
fout.close()
