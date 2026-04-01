import pandas as pd
import numpy as np

# 1. Создаем тестовые данные (имитация потребления энергии)
date_rng = pd.date_range(start='2025-01-01', end='2025-01-10', freq='h')
df = pd.DataFrame(date_rng, columns=['date'])
df['usage'] = np.random.randint(50, 100, size=(len(date_rng)))

# 2. Алгоритм создания лагов (важно для предсказания)
def create_lags(data, n_lags):
    for i in range(1, n_lags + 1):
        data[f'lag_{i}'] = data['usage'].shift(i)
    return data

# 3. Применяем и удаляем пустые строки, возникшие из-за сдвига
df = create_lags(df, 3).dropna()

print("Данные с признаками для предсказания:")
print(df.head())