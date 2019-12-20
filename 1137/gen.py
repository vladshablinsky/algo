n = 5
m = 5
d = 3
from random import randrange
print('{} {} {}'.format(n, m, d))



for i in range(1, m + 1):
    u = randrange(1, n + 1)
    v = randrange(1, n + 1, u)
    print('{} {}'.format(u, v))

for i in range(n):
    res = ""
    for i in range(d):
        res += str(randrange(0, 2))
    print(res)
