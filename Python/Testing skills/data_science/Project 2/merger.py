from cleaner_data import df
import pandas as pd

products_data = {
    'product': ['smartphone', 'laptop', 'tablet'],
    'category': ['electronics', 'computers', 'electronics'],
    'cost_price': [300, 800, 200]  # Себестоимость
}
df_products = pd.DataFrame(products_data)

new_df = pd.merge(df, df_products, on="product", how='inner')

new_df['profit'] = abs(new_df['price'] - new_df['cost_price'])
new_df['roi'] = new_df['profit'] / new_df['cost_price'] * 100

ROI = new_df.groupby('category').agg({
    'profit': 'sum',
    'roi': 'mean'
})

if __name__ == '__main__':
    print(new_df)
    print()
    print(ROI.head())