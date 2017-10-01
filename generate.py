from random import randint
from multiprocessing import cpu_count

N = 1000

for n_cpu in range(1, cpu_count() + 1):
    filename = str(n_cpu) + ".txt"
    rows, cols = N, N
    with open(filename, "w") as file:
        file.write("%d %d\n" % (rows, cols))
        print(rows * cols)
        for i in range(rows):
            file.write(" ".join([str(randint(1, 10)) for j in range(cols)]))
            file.write("\n")
