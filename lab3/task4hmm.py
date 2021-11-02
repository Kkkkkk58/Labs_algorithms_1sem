def heapify(array, current, heap_size):
    left = 2 * current + 1
    right = 2 * current + 2

    if left <= heap_size and array[left][0] < array[current][0]:
        smallest = left
    else:
        smallest = current
    if right <= heap_size and array[right][0] < array[smallest][0]:
        smallest = right

    if smallest != current:
        array[current], array[smallest] = array[smallest], array[current]
        heapify(array, smallest, heap_size)


def extract_min(array):
    heap_size = len(array) - 1
    if heap_size < 0:
        return "*"

    min_elem = array[0][0]
    if heap_size == 0:
        del array[0]
        return min_elem

    array[0] = array[heap_size]
    del array[heap_size]
    heap_size -= 1
    heapify(array, 0, heap_size)
    return min_elem


def decrease_key(array, index, key):
    array[index] = key
    while index > 0 and array[(index - 1) // 2][0] > array[index][0]:
        array[(index - 1) // 2], array[index] = array[index], array[(index - 1) // 2]
        index = (index - 1) // 2


def push(array, value):
    heap_size = len(array)
    array.append(0)
    decrease_key(array, heap_size, value)


fin = open("priorityqueue.in")
fout = open("priorityqueue.out", "w")
total_counter = 0
array = []

for command in fin:
    total_counter += 1

    if command[0] == "p":
        value = int(command[5:])
        push(array, [value, total_counter])

    elif command[0] == "e":
        print(extract_min(array), file=fout)

    else:
        old, new = map(int, command[13:].split())
        for index in range(len(array)):
            if array[index][1] == old:
                break
        decrease_key(array, index, [new, array[index][1]])

fin.close()
fout.close()
