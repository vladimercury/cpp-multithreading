import matplotlib.pyplot as pt
from multiprocessing import cpu_count

n_cpu_list = list(range(1, cpu_count() + 1))
base_time = 1

for n_cpu in n_cpu_list:
    try:
        with open(str(n_cpu) + ".txt") as file:
            stats = list(map(float, file.read().split()))
            avg = sum(stats) / len(stats)
            if n_cpu == 1:
                base_time = avg
            else:
                print(n_cpu, "CPUs:", base_time / avg, "x boost")
            parts = (n_cpu, "CPUs:", int(avg), "msec")
            pt.figure()
            pt.title("".join(map(str, parts)))
            avg_line = [avg] * len(stats)
            pt.plot(range(len(stats)), stats, color="blue")
            pt.plot(range(len(stats)), avg_line, color="red")
            pt.savefig(str(n_cpu) + ".png", dpi=75)
    except FileNotFoundError:
        pass
pt.show()