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

# === Configuration ===
input_file = "file.csv"
output_file = "clean_sales_data.csv"
min_total = 100

# === Logging setup ===
lg.basicConfig(level=lg.INFO, format="%(levelname)s - %(message)s")

# === Load data ===
lg.info("Loading data...")
try:
    df = pd.read_csv(input_file)
except FileNotFoundError:
    lg.error("File was not found!")
    exit()
except pd.errors.EmptyDataError:
    lg.error("File is empty!")
    exit()

lg.info(f"File loaded successfully: {len(df)} rows")

# === Clean data ===
lg.info("Deleting empty values in 'Product' and 'Price'...")
df.dropna(subset=["Product", "Price"], inplace=True)

lg.info("Converting data types...")
df["Quantity"] = pd.to_numeric(df["Quantity"], errors="coerce").fillna(0).astype(int)
df["Price"] = pd.to_numeric(df["Price"], errors="coerce").fillna(0).astype(float)

lg.info("Normalizing 'Region'...")
df["Region"] = df["Region"].str.lower()

lg.info("Parsing 'Date' column...")
df["Date"] = pd.to_datetime(df["Date"], errors="coerce")

lg.info("Filling missing 'Quantity' values with 0...")
df.fillna({"Quantity": 0}, inplace=True)

lg.info("Calculating 'Total' column...")
df["Total"] = df["Quantity"] * df["Price"]

# === Filter data ===
lg.info(f"Filtering rows where Total > {min_total}...")
df = df[df["Total"] > min_total]

lg.info(f"Rows left after filtering: {len(df)}")

# === Save cleaned data ===
lg.info("Saving cleaned data...")
try:
    df.to_csv(output_file, index=False)
except Exception as e:
    lg.error(f"Saving failed: {e}")
    exit()
else:
    lg.info(f"Success! Cleaned file saved as '{output_file}'")
