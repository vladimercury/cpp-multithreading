import matplotlib.pyplot as pt

files = {
    # "1s1": "1static1_5x1000000_1000000x5",
    # "1s100": "1static1_100x100000_100000x100",
    # "1s1K": "1static1_1000x1000_1000x1000",
    # "2d11": "2dynamic1_5x1000000_1000000x5",
    # "2d1100": "2dynamic1_100x100000_100000x100",
    # "2d11K": "2dynamic1_1000x1000_1000x1000",
    # "2d101": "2dynamic10_5x1000000_1000000x5",
    # "2d10100": "2dynamic10_100x100000_100000x100",
    # "2d101K": "2dynamic10_1000x1000_1000x1000",
    # "2g11": "2guided1_5x1000000_1000000x5",
    # "2g1100": "2guided1_100x100000_100000x100",
    # "2g11K": "2guided1_1000x1000_1000x1000",
    # "2g101": "2guided10_5x1000000_1000000x5",
    # "2g10100": "2guided10_100x100000_100000x100",
    # "2g101K": "2guided10_1000x1000_1000x1000",
    # "2s1": "2static1_5x1000000_1000000x5",
    # "2s100": "2static1_100x100000_100000x100",
    # "2s1K": "2static1_1000x1000_1000x1000"
    "1": "1static1_100x100000_100000x100",
    "2D10": "2dynamic10_100x100000_100000x100",
    "2D100": "2dynamic100_100x100000_100000x100",
    "2G10": "2guided10_100x100000_100000x100",
    "2G100": "2guided100_100x100000_100000x100"
}

files_stats = {}

for slug, filename in files.items():
    try:
        with open(filename + ".txt") as file:
            stats = list(map(float, file.read().split()))[1:]
            avg = round(sum(stats) / len(stats), 6)
            files_stats[slug] = (avg, stats)
    except FileNotFoundError:
        pass

groups = {
    # "1K": ["1s1K", "2d11K", "2d101K", "2g11K", "2g101K", "2s1K"],
    # "100": ["1s100", "2d1100", "2d10100", "2g1100", "2g10100", "2s100"]
    "TST": ["1", "2D10", "2D100", "2G10", "2G100"]
}

for group_name, values in groups.items():
    lines = []
    pt.figure()
    for file_slug in values:
        stat = files_stats[file_slug]
        line, = pt.plot(range(len(stat[1])), stat[1])
        mpl = files_stats[values[0]][0] / stat[0]
        lines.append((file_slug + ": x" + str(mpl), line))
    pt.legend([line[1] for line in lines], [line[0] for line in lines])
    pt.savefig(group_name + ".png", dpi=100)
pt.show()
