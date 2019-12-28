import random
import string

N = 8
ALPH = 'abc'

ans = ''

print(N)
for i in range(N):
    ans += random.choice(ALPH)

print(ans)

