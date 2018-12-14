import random
import subprocess

def make_example():
    n = random.randint(1, 10)
    cur_leaves = []
    gas = []
    edges = []

    for i in range(n):
        gas.append(random.randint(1, 10))

    cur_leaves.append(1)

    for i in range(2, n + 1):
        from_v = random.choice(list(cur_leaves))
        to_v = i
        edges.append((from_v, to_v, random.randint(1, 10)))
        cur_leaves.append(i)

    return n, gas, edges

def gen_example_str(n, gas, edges):
    example_str = ''
    example_str += '{}\n'.format(n)
    for el in gas:
        example_str += '{} '.format(el)

    example_str += '\n'

    for edge in edges:
        example_str += '{} {} {}\n'.format(*edge)

    return example_str

def try_test():
    while True:
        example_str = gen_example_str(*make_example())

        p_bad = subprocess.Popen(['./d.out'],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE
        )

        p_good = subprocess.Popen(['./d_ok.out'],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE
        )

        res_bad, _ = p_bad.communicate(input=example_str)
        res_good, _ = p_good.communicate(input=example_str)

        if res_bad != res_good:
            print('input: {}, good: {}, bad: {}'.format(example_str, res_good, res_bad))
            break


try_test()

