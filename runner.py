import subprocess

executable = "./cmake-build-debug/multithread"
run_configs = [
    # "1 static 1 100x100K.txt 100Kx100.txt",
    # "1 static 1 1Kx1Ka.txt 1Kx1Kb.txt",
    # "1 static 1 5x1M.txt 1Mx5.txt",
    # "2 static 1 100x100K.txt 100Kx100.txt",
    # "2 static 1 1Kx1Ka.txt 1Kx1Kb.txt",
    # "2 static 1 5x1M.txt 1Mx5.txt",
    # "2 dynamic 1 100x100K.txt 100Kx100.txt",
    # "2 dynamic 1 1Kx1Ka.txt 1Kx1Kb.txt",
    # "2 dynamic 1 5x1M.txt 1Mx5.txt",
    # "2 dynamic 10 100x100K.txt 100Kx100.txt",
    # "2 dynamic 10 1Kx1Ka.txt 1Kx1Kb.txt",
    # "2 dynamic 10 5x1M.txt 1Mx5.txt",
    # "2 guided 1 100x100K.txt 100Kx100.txt",
    # "2 guided 1 1Kx1Ka.txt 1Kx1Kb.txt",
    # "2 guided 1 5x1M.txt 1Mx5.txt",
    # "2 guided 10 100x100K.txt 100Kx100.txt",
    # "2 guided 10 1Kx1Ka.txt 1Kx1Kb.txt",
    # "2 guided 10 5x1M.txt 1Mx5.txt"
    "1 static 1 100x100K.txt 100Kx100.txt",
    "2 static 1 100x100K.txt 100Kx100.txt",
    "2 dynamic 10 100x100K.txt 100Kx100.txt",
    "2 dynamic 100 100x100K.txt 100Kx100.txt",
    "2 guided 10 100x100K.txt 100Kx100.txt",
    "2 guided 100 100x100K.txt 100Kx100.txt"
]
for i in range(1):
    print("Iteration %d" % i)
    print()
    for flags in run_configs:
        process = subprocess.Popen(executable + " " + flags, shell=True)
        process.communicate()