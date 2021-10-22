from random import randint

colors = ["red", "white", "green", "blue", "yellow", "orange"]

N = randint(2, 11)
M = randint(2, min(4, 2 ** N - 1))

print(N)
print(M)

used_vertices = set()
for i in range(M):
    col = colors[randint(0, 5)]
    vertex = None

    while (vertex is None or vertex in used_vertices):
        maxpow = min(N, 6)
        vertex = randint(1, 2 ** maxpow - 1)

    used_vertices.add(vertex)

    print('{} {}'.format(vertex, col))

