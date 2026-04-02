import pandas as pd
import numpy as np

df = pd.read_csv("./dirty_store_data.csv")

# Everything in lower case
df.columns = df.columns.str.lower()
df['customer_name'] = df['customer_name'].fillna('Unknown').str.lower() # If no name -> Unknown
df['product'] = df['product'].str.lower()
df['region'] = df['region'].str.lower()
df['price'] = pd.to_numeric(df['price'].str.replace('$', '')) # All prices to numerics

# First column is index
df.set_index('transaction_id', inplace=True)

# No duplicates
df = df.drop_duplicates()

# Every date to NaT => prev. date
df['date'] = pd.to_datetime(df['date'], errors='coerce')
df['date'] = df['date'].ffill()

# All NaN prices to mean
df['price'] = df['price'].fillna(df['price'].mean())

# Make another group by region
group_by_region = df.groupby('region')['price'].sum().reset_index()

if __name__ == "__main__":
    print(df)
    print(df.isna().sum())
    print(df.duplicated().sum())
    print(df.info())
    print()
    print(group_by_region)