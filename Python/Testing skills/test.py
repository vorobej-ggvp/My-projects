import pandas as pd

df = pd.read_csv("file.csv")

df.dropna(subset=["Product", "Price"], inplace=True)

df["Region"] = df["Region"].str.lower()

df["Date"] = pd.to_datetime(df["Date"], format='mixed')

df.fillna({"Quantity": 0}, inplace=True)

df["Total"] = df["Quantity"] * df["Price"]

df = df[df["Total"] > 100]

df.to_csv("clean_sales_data.csv", mode="a")
# print(df)
