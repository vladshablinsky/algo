import random

random.seed(9001)
N = 10
parents = []
for i in range(2, N + 1):
    value = random.randint(1, N)
    while value == i:
        value = random.randint(1, N)

    parents.append(value)

print(N)
for vertex, parent in enumerate(parents, start=2):
    print('{} {}'.format(vertex, parent))
