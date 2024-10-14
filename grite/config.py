from pydantic_settings import BaseSettings, SettingsConfigDict
import pandas as pd

class Settings(BaseSettings):
    size_path: float

    model_config = SettingsConfigDict(env_file=".env")


settings = Settings()
# filename = "../../data/example.txt"
# dataset = pd.read_csv(filename, header=0, sep="\s+")

filename = "../../data/gri_data/meteo_data/downld02_clean.txt"
dataset = pd.read_csv(filename, sep="\s+")

# filename = "../paraminer/paraminer-1.0/data/gri/I4408_78.dat"
# dataset = pd.read_csv(filename, header=0, sep=",")
# filename = "data.txt"
# dataset = pd.read_csv(filename, header=0, sep="\s+")
# print(dataset.shape)
# import random
# b = list(dataset.columns)
# print(len(b))
# random.shuffle(b)
# col_size = random.randint(20, 40)
# print(col_size)
# print(b)
# pd.DataFrame(dataset[b[:col_size]]).to_csv(f"../paraminer/paraminer-1.0/data/gri/I4408_{col_size}.dat", index=False)
# print(dataset[b[:col_size]].shape)
# filename = "../../explainability/train_data.txt"
# dataset = pd.read_csv(filename, header=0, sep="\s+")
# filename = "../../data/hcv_data.csv"
# dataset = pd.read_csv(filename, header=0, sep=";")
# filename = "data_1.txt"
# dataset = pd.read_csv(filename, header=0, sep="\s+")
# if "0" in dataset.columns:
#     dataset.drop(["0"], inplace=True)
# filename = "data_grap.csv"
# dataset = pd.read_csv(filename, header=0, sep="\s+")
