'''This module is for testing the efficiency of different algorithms under various conditions'''
import subprocess
from random import choices, randint
import pandas as pd
import re

alphabet = ['A', 'T', 'C', 'G', 'U']


def generate_random_patterns(min_length, max_length, patterns_list):
    for length in range(min_length, max_length + 1):
        pattern = choices(alphabet, k=length, weights=[10, 10, 10, 10, 3])
        patterns_list.append(''.join(pattern))


def get_patterns_from_file(file_path, min_length, max_length, patterns_list):
    # read the whole file
    string = ""
    with open(file_path, 'r') as f:
        f.readline()  # get dummy line
        for line in f:
            string += line

    for length in range(min_length, max_length + 1):
        start_id = randint(0, len(string) - length)
        patterns_list.append(string[start_id:start_id+length])


def process_output(output):
    records = pd.DataFrame(columns=['length', 'time', '#occurances', '#collision'])
    length = 0

    results = output.decode('utf-8').strip().split("Type the target pattern to search (type -1 to exit the program):")
    for result in results:
        if not result.strip():
            continue
        length += 1
        if length > max_length:
            length = length - max_length
        time = 0
        occurrences_num = 0
        collisions_num = 0
        for record in result.split('\n'):
            if "Execution time" in record:  # parse execution record
                time = re.findall("\d+\.\d+", record)[0]
            elif "occurrences found in total" in record:  # parse number of occurrences
                occurrences_num = re.findall("\d+", record)[0]
            elif "times of collisions" in record:  # parse number of collisions
                collisions_num = re.findall("\d+", record)[0]

        records = records.append({'length': length, 'time': float(time), "#occurances": int(occurrences_num),
                        '#collision': int(collisions_num)}, ignore_index=True)

    print(records)
    return records


patterns = []
max_length = 20
generate_random_patterns(1, max_length, patterns)
get_patterns_from_file("dataset/dna.200MB", min_length=1, max_length=max_length, patterns_list=patterns)
patterns.append("-1")
patterns = " ".join(patterns)

for algorithm in ['b','kmp','rk-nt', 'rk']:
    process = subprocess.run(["./PatternSearchProgram", algorithm, "dna.200MB"], input=patterns.encode(),
                          capture_output=True)

    records = process_output(process.stdout)
    records.to_csv(algorithm+".csv")
