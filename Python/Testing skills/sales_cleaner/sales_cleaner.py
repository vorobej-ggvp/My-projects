"""
sales_cleaner.py

Cleaning data in file:
- removes rows with empty "Product" or "Price"
- normalizes "Region"
- converts "Date" to unified format
- calculates "Total"
- filters rows where "Total" > 100
"""

import pandas as pd
import logging as lg
import os

lg.basicConfig(level=lg.INFO, format="%(levelname)s - %(message)s")

class DataCleaner:
    def __init__(self, input, output):
        self.data = None
        self.input = input
        self.output = output
        self.min_total = 100

    def load(self):
        lg.info("Loading data...")
        try:
            self.data = pd.read_csv(self.input, skipinitialspace=True)
            self.data.columns = self.data.columns.str.strip()
        except FileNotFoundError:
            lg.info("ERROR: File was not found!")
            return False
        except pd.errors.EmptyDataError:
            lg.info("ERROR: File cannot be empty!")
            return False

        lg.info(f"File was uploaded: {len(self.data)} rows")

    def clean(self):
        lg.info("Deleting empty values...")
        self.data.dropna(subset=["Product", "Price"], inplace=True)

        self.data.fillna({"Quantity": 0}, inplace=True)

        self.data["Quantity"] = self.data["Quantity"].astype(int)
        self.data["Price"] = self.data["Price"].astype(float)

        lg.info("Creating new column 'Total' = 'Quantity' * 'Price'...")
        self.data["Total"] = self.data["Quantity"] * self.data["Price"]

        lg.info("Filtering 'Total' > 100'...")
        self.data = self.data[self.data["Total"] > self.min_total]

        lg.info(f"Rows left: {len(self.data)}")

    def export(self):
        lg.info("Saving cleaned file...")
        try:
            self.data.to_csv(self.output, index=False)
        except:
            lg.info("Something went wrong, file have not been created.")
            return False
        else:
            lg.info("Success!")
            return False

class CSVDataCleaner(DataCleaner):
    def __init__(self, input, output):
        super().__init__(input, output)

    def clean(self):
        super().clean()
        self.normalize_text()

    def normalize_text(self):
        lg.info("Normalizing data...")
        text_columns = self.data.select_dtypes(include=["object"]).columns

        self.data["Date"] = pd.to_datetime(self.data["Date"], errors="coerce", infer_datetime_format=True)

        for col in text_columns:
            self.data[col] = self.data[col].astype(str).str.lower().str.replace(r"\s+", " ", regex=True).str.replace(r"[^\w\s]", "", regex=True).str.strip()

base_dir = os.path.dirname(__file__)
input_path = os.path.join(base_dir, "file.csv")
output_path = os.path.join(base_dir, "clean_sales_data.csv")

x = CSVDataCleaner(input_path, output_path)

if x.load():
    x.clean()
    x.export()
    print(x.data.head())
