n = int(raw_input())
first = 0
second = 1
times = 1
while times <= n:
    first , second = second, first + second
    times += 1
print first