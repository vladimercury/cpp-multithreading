# General

> I used *CLion* to create and run this program

This program counts matrix multiplicity in parallel

Run `generate.py` first to generate data files

Main program takes 5 required arguments:

1. Number of threads
2. Schedule type (static/dynamic/guided). Required but will not make an effect if number of threads = 1
3. Chunk size
4. First file
5. Second file

You can see result in file `result.txt`

# Autorun

You can use `runner.py` to run main program automatically with different flags. It uses folder `cmake-build-debug` where Clion creates executable file

# Stats

Also program counts working time and writes it into `stats/{nCPU}{schedule}{chunk_size)_{first_matrix_size}{second_matrix_size}.txt`

You can draw stats using `stats/draw_stats.py`
