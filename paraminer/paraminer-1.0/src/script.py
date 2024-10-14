import subprocess
import sys
import re

DATA_PATH = "/home/kndb/Dev/Phd-Code/gradual/paraminer/paraminer-1.0/data/gri/test.dat"
PARAMINER_EXE = (
    "/home/kndb/Dev/Phd-Code/gradual/paraminer/paraminer-1.0/src/paraminer_graduals"
)


def mine_gp(data_path=DATA_PATH, exe_path=PARAMINER_EXE, seuil=20, num_cores=10):
    def find_all_matches(pattern, string):
        pat = re.compile(pattern)
        pos = 0
        out = []
        while (match := pat.search(string, pos)) is not None:
            pos = match.start() + 1
            out.append(match[1])
        return out
    result = subprocess.run(
        [
            exe_path,
            data_path,
            f"{seuil}",
            "-t",
            f"{num_cores}",
        ],
        capture_output=True,
        text=True,
    )
    r = result.stdout.split("\n")[4:]

    pattern = r" (\d*[\+\-])+"
    l = list()

    # Extract numbers, signs, and numbers in brackets
    for string in r:
        match = find_all_matches(pattern, string)
        m = re.search(r"\((\d+)\)", string)

        if match and m:
            if len(match) > 1:
                l.append((match, len(match) / int(m.group(1))))
    return sorted(l, key=lambda x: x[1], reverse=True)

print(mine_gp())