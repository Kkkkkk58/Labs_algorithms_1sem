from queue import Queue


class Node:
    def __init__(self, label):
        self.label = label
        self.left = self.right = None


def insert(tree, label):
    if tree is None:
        return Node(label)
    else:
        if tree.label[0] > label[0]:
            tree.left = insert(tree.left, label)
        else:
            tree.right = insert(tree.right, label)
    return tree


def search(tree, label):
    while tree is not None and tree.label[0] != label:
        if label < tree.label[0]:
            tree = tree.left
        else:
            tree = tree.right
    return tree.label[1]


def quack(command):
    if command == "+":
        x = queue.get()
        y = queue.get()
        queue.put((x + y) % 65536)
    elif command == "-":
        x = queue.get()
        y = queue.get()
        queue.put((x - y) % 65536)
    elif command == "*":
        x = queue.get()
        y = queue.get()
        queue.put((x * y) % 65536)
    elif command == "/":
        x = queue.get()
        y = queue.get()
        if y == 0:
            queue.put(0)
        else:
            queue.put(x // y)
    elif command == "%":
        x = queue.get()
        y = queue.get()
        if y == 0:
            queue.put(0)
        else:
            queue.put(x % y)
    elif command[0] == ">":
        value = queue.get()
        register_number = ord(command[1]) - ord("a")
        registers[register_number] = value
    elif command[0] == "<":
        register_number = ord(command[1]) - ord("a")
        value = registers[register_number]
        queue.put(value)
    elif command[0] == "P":
        if len(command) == 1:
            x = queue.get()
            print(x, file=fout)
        else:
            register_number = ord(command[1]) - ord("a")
            print(registers[register_number], file=fout)
    elif command[0] == "C":
        if len(command) == 1:
            x = queue.get()
            print(chr(x % 256), end="", file=fout)
        else:
            register_number = ord(command[1]) - ord("a")
            print(chr(registers[register_number] % 256), end="", file=fout)
    elif command[0] == ":":
        return
    elif command[0] == "J":
        label = ":" + command[1:]
        command_index = search(labels, label)
        for j in range(command_index + 1, len(commands_array)):
            quack(commands_array[j])
        exit()
    elif command[0] == "Z":
        register_number = ord(command[1]) - ord("a")
        if registers[register_number] == 0:
            label = ":" + command[2:]
            command_index = search(labels, label)
            for j in range(command_index + 1, len(commands_array)):
                quack(commands_array[j])
            exit()
    elif command[0] == "E":
        register_1_number = ord(command[1]) - ord("a")
        register_2_number = ord(command[2]) - ord("a")
        if registers[register_1_number] == registers[register_2_number]:
            label = ":" + command[3:]
            command_index = search(labels, label)
            for j in range(command_index + 1, len(commands_array)):
                quack(commands_array[j])
            exit()
    elif command[0] == "G":
        register_1_number = ord(command[1]) - ord("a")
        register_2_number = ord(command[2]) - ord("a")
        if registers[register_1_number] > registers[register_2_number]:
            label = ":" + command[3:]
            command_index = search(labels, label)
            for j in range(command_index + 1, len(commands_array)):
                quack(commands_array[j])
            exit()
    elif command == "Q":
        exit()
    else:
        value = int(command)
        queue.put(value)


fin = open("quack.in")
fout = open("quack.out", "w")
commands_array = []
queue = Queue()
registers = [0] * 26
first_insertion = True

for line in fin:
    if line == "\n":
        break
    commands_array.append(line.rstrip("\n"))
    if line[0] == ":":
        if first_insertion:
            labels = Node([line.rstrip("\n"), len(commands_array) - 1])
            first_insertion = False
        else:
            labels = insert(labels, [line.rstrip("\n"), len(commands_array) - 1])

for command in commands_array:
    quack(command)

fin.close()
fout.close()
