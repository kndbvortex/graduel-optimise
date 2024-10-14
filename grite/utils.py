import numpy as np
from numpy.typing import NDArray

def val_to_write(val, cycle):
    val_mod = val % cycle
    return val_mod if val_mod else cycle


def increase_gradual(data, file, col, cycle=None):
    seq = False
    if cycle is None:
        raise "cycle is required"

    for j in range(1, data.shape[0]):
        if data[j, col] >= data[j - 1, col]:
            if seq:
                file.write(f"{val_to_write(j + 1, cycle)} ")
            else:
                file.write(f"{val_to_write(j, cycle)} {val_to_write(j + 1, cycle)} ")
                seq = True
        else:
            if seq:
                file.write("-1 ")
                seq = False
    if seq:
        file.write("-1 ")
    file.write("-2 \n")


def decrease_gradual(data, file, col, cycle=None):
    seq, first = True, False
    if cycle is None:
        raise "cycle is required"

    for j in range(1, data.shape[0]):
        if data[j, col] <= data[j - 1, col]:
            if seq:
                file.write(f"{val_to_write(j + 1, cycle)} ")
            else:
                file.write(f"{val_to_write(j, cycle)} {val_to_write(j + 1, cycle)} ")
                seq = True
        else:
            if seq:
                file.write("-1 ")
                seq = False
    if seq:
        file.write("-1 ")
    file.write("-2 \n")


def num_to_sequential(data: NDArray, destination_file, size_of_one_cycle):
    nb_columns = data.shape[1]
    with open(destination_file, 'w') as file:
        for col in range(nb_columns):
            increase_gradual(data, file, col, size_of_one_cycle)
            decrease_gradual(data, file, col, size_of_one_cycle)
