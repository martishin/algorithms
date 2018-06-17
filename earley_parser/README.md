Комментарии-1

В программе на языке Python можно писать комментарии, которые начинаются с символа #. Такой комментарий простирается до конца строки. Помогите Васе написать программу, которая будет печатать все такие комментарии из его программы (включая символ #).
Формат ввода

На вход подаются строки программы.
Формат вывода

Напечатайте все комментарии из данной программы, включая символ #. Отступов перед комментариями быть не должно.

Пример-1

Ввод: 
\# Import necessary modules
import sys

for line in sys.stdin: # Iterate over lines
line += "#" # Add '#' sign to the line
my_module.do_first(line) # Call do_first
\# These comments are useless
my_module.do_second(line) # Do not write useless comments in your programs

Вывод:
\# Import necessary modules
\# Iterate over lines
\# Add '#' sign to the line
\# Call do_first
\# These comments are useless
\# Do not write useless comments in your programs

Пример-2

Ввод:
\# First comment
a = "Hello, ###" # Second comment
b = "'Citation' inside a #string\
continuation" # Third comment
\# Last comment

Вывод:
\# First comment
\# Second comment
\# Third comment
\# Last comment

Примечания

Вася пока не освоил строки документации, заключенные в тройные кавычки, поэтому можно считать, что в его программе таких строк нет. Еще Вася никогда не пишет символ \ перед кавычками и апострофами (но может писать его в конце строки).
