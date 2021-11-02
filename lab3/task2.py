def heapify(array, current, heap_size):
    left = 2 * current + 1
    right = 2 * current + 2

    if left <= heap_size and array[left] > array[current]:
        largest = left
    else:
        largest = current
    if right <= heap_size and array[right] > array[largest]:
        largest = right

    if largest != current:
        array[current], array[largest] = array[largest], array[current]
        heapify(array, largest, heap_size)
    

def build_heap(array, heap_size):
    for i in range((len(array) - 1) // 2, -1, -1):
        heapify(array, i, heap_size)


def heapsort(array):
    heap_size = len(array) - 1
    build_heap(array, heap_size)
    for i in range(heap_size, 0, -1):
        array[0], array[i] = array[i], array[0]
        heap_size -= 1
        heapify(array, 0, heap_size)


fin = open("sort.in")
fout = open("sort.out", "w")
n = int(fin.readline())
array = list(map(int, fin.readline().split()))

heapsort(array)
for i in range(n):
    print(array[i], file=fout, end=" ")

fin.close()
fout.close()
