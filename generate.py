from random import randint

config = [
    ("1Kx1Ka", 1000, 1000),
    ("1Kx1Kb", 1000, 1000),
    ("100x100K", 100, 100000),
    ("100Kx100", 100000, 100),
    ("5x1M", 5, 1000000),
    ("1Mx5", 1000000, 5)
]

for filename, rows, cols in config:
    with open("data/" + filename + ".txt", "w") as file:
        file.write("%d %d\n" % (rows, cols))
        print(rows * cols)
        for i in range(rows):
            for j in range(cols):
                file.write(str(randint(1, 100)) + " ")
            file.write("\n")
