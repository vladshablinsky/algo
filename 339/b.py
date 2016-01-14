import sys

n = int(input())
res = 1

s = raw_input()

for i in s.split(' '):
    x = int(i)
    res *= x

print res
