class Stack:
    def __init__(self):
        self.top = -1
        self.array = [0] * 100

    def push_in(self, value):
        self.top += 1
        self.array[self.top] = value

    def pop_out(self):
        self.top -= 1
        return self.array[self.top + 1]


fin = open("postfix.in")
fout = open("postfix.out", "w")

values = Stack()
input_line = list(fin.readline().split())

for i in range(len(input_line)):
    if input_line[i].isdigit():
        values.push_in(int(input_line[i]))
        
    else:
        second_operator = values.pop_out()
        first_operator = values.pop_out()

        if input_line[i] == "+":
            values.push_in(first_operator + second_operator)
        elif input_line[i] == "-":
            values.push_in(first_operator - second_operator)
        else:
            values.push_in(first_operator * second_operator)

result = values.pop_out()
print(result, file=fout)
fin.close()
fout.close()