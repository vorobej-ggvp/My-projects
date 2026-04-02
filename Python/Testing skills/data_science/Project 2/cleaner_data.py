import pandas as pd
import numpy as np

df = pd.read_csv("./dirty_store_data.csv")

df.columns = df.columns.str.lower()
df['customer_name'] = df['customer_name'].fillna('Unknown').str.lower()
df['product'] = df['product'].str.lower()
df['region'] = df['region'].str.lower()
df['price'] = pd.to_numeric(df['price'].str.replace('$', ''))

df.set_index('transaction_id', inplace=True)

df = df.drop_duplicates()

df['date'] = pd.to_datetime(df['date'], errors='coerce')

df['date'] = df['date'].ffill()

df['price'] = df['price'].fillna(df['price'].mean())

print(df)

group_by_region = df.groupby('region')['price'].sum().reset_index()

print(df.isna().sum())
print(df.duplicated().sum())
print(df.info())
print()
print(group_by_region)