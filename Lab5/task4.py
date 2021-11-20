from queue import Queue


class Node:
    def __init__(self, label):
        self.label = label
        self.left = self.right = None


def insert(root, label):
    if root is None:
        return Node(label)
    else:
        if root.label[0] > label[0]:
            root.left = insert(root.left, label)
        else:
            root.right = insert(root.right, label)
    return root


def search(root, label):
    while root is not None and root.label[0] != label:
        if label < root.label[0]:
            root = root.left
        else:
            root = root.right
    return root.label[1]


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
            print(x)
        else:
            register_number = ord(command[1]) - ord("a")
            print(registers[register_number])
    elif command[0] == "C":
        if len(command) == 1:
            x = queue.get()
            print(chr(x % 256), end="")
        else:
            register_number = ord(command[1]) - ord("a")
            print(chr(registers[register_number] % 256), end="")
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
            label = command[3:]
            command_index = search(labels, label)
            for j in range(command_index + 1, len(commands_array)):
                quack(commands_array[j])
            exit()
    elif command == "Q":
        exit()
    else:
        value = int(command)
        queue.put(value)


def inorder(root):
    if root:
        inorder(root.left)
        print(root.label)
        inorder(root.right)

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
