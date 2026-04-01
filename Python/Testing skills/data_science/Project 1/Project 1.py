from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_absolute_error
import mlcroissant as mlc
import plotly.graph_objects as go
import pandas as pd
import logging
import warnings

logging.getLogger('absl').setLevel(logging.ERROR)

warnings.filterwarnings("ignore")

# Fetch the Croissant JSON-LD
croissant_dataset = mlc.Dataset('https://www.kaggle.com/datasets/awadhi123/finance-data-sp-500/croissant/download')

# Check what record sets are in the dataset
record_sets = croissant_dataset.metadata.record_sets

# Fetch the records and put them in a DataFrame
record_set_df = pd.DataFrame(croissant_dataset.records(record_set=record_sets[0].uuid))

# Split name values for readability; Default: SP500.csv/{col_name}
record_set_df.columns = [col.split('/')[-1].replace('+', '_').lower() for col in record_set_df.columns]

# ---------------------------------------------------------

# Column 'Date' to date format
record_set_df['date'] = pd.to_datetime(record_set_df['date'])

# Make 'Date' column as index
record_set_df.set_index('date', inplace=True)
clean_df = record_set_df.interpolate(method='time')

# Because 'close' and 'adj_close' are identical
clean_df.drop(columns=['close'], inplace=True)

# ---------------------------------------------------------

# Make lag_1 as price_today - price_yesterday
clean_df['lag_1'] = clean_df['adj_close'].shift(1)
# Make mean for week
clean_df['rolling_mean_5'] = clean_df['adj_close'].rolling(window=5).mean()

# Make daily return
clean_df['daily_return'] = clean_df['adj_close'].pct_change()

# Make volatility for 20 days
clean_df['volatility_20d'] = clean_df['daily_return'].rolling(window=20).std()

# Delete unescessary rows (noise)
clean_df.dropna(inplace=True)

# ---------------------------------------------------------

# Make figure
fig = go.Figure()

fig.add_trace(go.Scatter(x=clean_df.index, y=clean_df['adj_close'], name="Closing price", line=dict(color="blue")))

fig.add_trace(go.Scatter(x=clean_df.index, y=clean_df['rolling_mean_5'], name="Trand (5 days)", line=dict(color="orange", dash="dash")))

fig.update_layout(
    title='Analysis of index S&P 500',
    xaxis_title='Date',
    yaxis_title='Price($)',
    hovermode='x unified',
)

fig.show()

# ---------------------------------------------------------

split_index = len(clean_df) - 252           # 252 – ~ one business year
train_df = clean_df.iloc[:split_index]      # Train data
test_df = clean_df.iloc[split_index:]       # Test data


X_train = train_df[['lag_1', 'rolling_mean_5', 'volatility_20d']]
y_train = train_df['adj_close']

X_test = test_df[['lag_1', 'rolling_mean_5', 'volatility_20d']]
y_test = test_df['adj_close']


# Create a model
model = LinearRegression()
model.fit(X_train, y_train)

predictions = model.predict(X_test)

error = mean_absolute_error(y_test, predictions)    # Result: 31.80264219020117 $

# --------------------------------------------------------

# Make another figure
fig1 = go.Figure()

fig1.add_trace(go.Scatter(x=X_test.index, y=y_test, name="Real prices", line=dict(color="blue")))
fig1.add_trace(go.Scatter(x=X_test.index, y=predictions, name="Predicted prices", line=dict(color="orange", dash='dash')))
fig1.update_layout(
    title='Training model to prognoze tomorrow price',
    xaxis_title='Real values',
    yaxis_title='Predicted values',
    hovermode='x unified',
)

fig1.show()

# --------------------------------------------------------

X_for_tomorrow = clean_df[['lag_1', 'rolling_mean_5', 'volatility_20d']].tail(1) 

print(model.predict(X_for_tomorrow))        # Result: 3225.5669444$

# Conclusion: Line with predicted values goes a bit after line with real values. 