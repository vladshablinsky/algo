from random import randint

n = 10
print(n)

st = "RGB";
res = []
for i in xrange(n):
    res.append(st[randint(0, 2)])

print(''.join(res))
