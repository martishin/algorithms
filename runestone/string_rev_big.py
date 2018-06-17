import string


class Stack:
    def __init__(self):
        self.data = []

    def put(self, char):
        self.data.append(char)

    def get(self):
        return self.data.pop()

s = Stack()
str_in = 'asd'
length = len(str_in)
for i in range(length):
    s.put(str_in[i])
print(''.join(s.get() for i in range(length)))
# print(str[::-1])


str_in = 'asd asd Hello world'
char_dict = {string.lowercase[i]: string.uppercase[i] for i in range(len(string.lowercase))}
print([char_dict[x[0]] + x[1:] if x[0] in char_dict else x for x in str_in.split(' ')])
