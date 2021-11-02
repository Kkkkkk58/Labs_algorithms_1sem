class Stack:
    def __init__(self, array):
        self.top = -1
        self.array = array

    def is_empty(self):
        return self.top < 0

    def push_in(self, value):
        self.top += 1
        self.array[self.top] = value

    def pop_out(self):
        if self.is_empty():
            return " "
        self.top -= 1
        return self.array[self.top + 1]


fin = open("brackets.in")
fout = open("brackets.out", "w")

for line in fin:
    line = line.rstrip("\n")
    array = [""] * len(line)
    opening_brackets = Stack(array)
    is_correct = True
    i = 0
    
    while i < len(line) and is_correct:
        bracket = line[i]
        if bracket == "(" or bracket == "[":
            opening_brackets.push_in(bracket)

        else:
            opening = opening_brackets.pop_out()
            if (bracket == ")" and opening != "(") \
                    or (bracket == "]" and opening != "["):
                is_correct = False
                break

        i += 1
    if (not is_correct) or (not opening_brackets.is_empty()):
        print("NO", file=fout)
        continue
    print("YES", file=fout)

fin.close()
fout.close()
