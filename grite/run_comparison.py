import subprocess
import re
from math import ceil
from config import filename, dataset
import pandas as pd
from tqdm import tqdm


def match_result(text, result_dict):
    time_pattern = r"--- (\d+\.\d+) seconds ---"
    patterns_pattern = r"(\d+) Motifs Fréquent"
    candidates_pattern = r"(\d+) nombre de candidats"

    time = re.search(time_pattern, text).group(1)
    patterns = re.search(patterns_pattern, text).group(1)
    candidates = re.search(candidates_pattern, text).group(1)

    result_dict["time"].append(time)
    result_dict["patterns"].append(patterns)
    result_dict["candidates"].append(candidates)

results_dict = {"Grite":{"time":[], "candidates":[], "patterns":[]}, "test":{"time":[], "candidates":[], "patterns":[]}}

percents = [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0]
n_row = dataset.shape[0]

for percent in tqdm(percents):
    r = subprocess.Popen(
            [
                "python3",
                "grite_from_scratch.py",
                f"{ceil(percent*n_row)}"
            ],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )
    output, _ = r.communicate()
    r_2 = subprocess.Popen(
            [
                "python3",
                "grite_column_pruning.py",
                f"{ceil(percent*n_row)}"
            ],

            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
        )
    output_2, _ = r_2.communicate()
    match_result(output, results_dict["Grite"])
    match_result(output_2, results_dict["test"])
    print(results_dict)
    pd.DataFrame.from_dict(results_dict["Grite"]).to_excel(f"results/Grite_{filename.split('/')[-1].split('.')[0]}.xlsx")
    pd.DataFrame.from_dict(results_dict["test"]).to_excel(f"results/test_{filename.split('/')[-1].split('.')[0]}.xlsx")


pd.DataFrame.from_dict(results_dict["Grite"]).to_excel(f"results/Grite_{filename.split('/')[-1].split('.')[0]}.xlsx")
pd.DataFrame.from_dict(results_dict["test"]).to_excel(f"results/test_{filename.split('/')[-1].split('.')[0]}.xlsx")