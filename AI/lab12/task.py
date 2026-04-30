import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np
import warnings
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_absolute_error, mean_squared_error, r2_score

warnings.filterwarnings('ignore')

df = pd.read_csv('house_prices_practice.csv')

print(df.head())
print(df.shape)
print(df.columns.tolist())

numerical = df.select_dtypes(include=['float64', 'int64']).columns.tolist()
categorical = df.select_dtypes(include=['object']).columns.tolist()
print("Numerical:", numerical)
print("Categorical:", categorical)

missing = df.isnull().sum()
missing = missing[missing > 0].sort_values(ascending=False)
print(missing)

threshold = 0.5 * len(df)
df = df.drop(columns=missing[missing > threshold].index)

for col in df.select_dtypes(include=['float64', 'int64']).columns:
    df[col].fillna(df[col].median(), inplace=True)

for col in df.select_dtypes(include=['object']).columns:
    df[col].fillna(df[col].mode()[0], inplace=True)

if 'Id' in df.columns:
    df.drop(columns=['Id'], inplace=True)

fig, axes = plt.subplots(1, 2, figsize=(14, 5))
sns.histplot(df['SalePrice'], bins=100, kde=True, color='green', ax=axes[0])
axes[0].set_title('SalePrice Distribution')
sns.boxplot(y=df['SalePrice'], ax=axes[1], color='green')
axes[1].set_title('SalePrice Boxplot')
plt.tight_layout()
plt.show()

print("SalePrice Skewness:", df['SalePrice'].skew())

fig, axes = plt.subplots(1, 2, figsize=(14, 5))
sns.histplot(df['GrLivArea'], bins=100, kde=True, color='blue', ax=axes[0])
axes[0].set_title('GrLivArea Distribution')
sns.boxplot(y=df['GrLivArea'], ax=axes[1], color='blue')
axes[1].set_title('GrLivArea Boxplot')
plt.tight_layout()
plt.show()

print("GrLivArea Skewness:", df['GrLivArea'].skew())

df_num = df.select_dtypes(include=['float64', 'int64'])
corr_with_price = df_num.corr()['SalePrice'].drop('SalePrice').sort_values(ascending=False)
print("Top 5 features:\n", corr_with_price.head(5))

plt.figure(figsize=(8, 5))
sns.scatterplot(x=df['GrLivArea'], y=df['SalePrice'], alpha=0.5, color='blue')
plt.title('GrLivArea vs SalePrice')
plt.xlabel('GrLivArea')
plt.ylabel('SalePrice')
plt.show()

plt.figure(figsize=(8, 5))
sns.barplot(x='OverallQual', y='SalePrice', data=df, palette='viridis')
plt.title('OverallQual vs SalePrice')
plt.xlabel('Overall Quality')
plt.ylabel('Average SalePrice')
plt.show()

plt.figure(figsize=(12, 8))
top_features = corr_with_price.head(10).index.tolist() + ['SalePrice']
sns.heatmap(df[top_features].corr(), annot=True, fmt='.2f', cmap='coolwarm')
plt.title('Correlation Heatmap (Top Features)')
plt.show()

df['HouseAge'] = df['YrSold'] - df['YearBuilt']

top5 = corr_with_price.head(5).index.tolist()
features = top5 + ['HouseAge']
X = df[features]
y = df['SalePrice']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

model = LinearRegression()
model.fit(X_train, y_train)
y_pred = model.predict(X_test)

print("MAE: ", mean_absolute_error(y_test, y_pred))
print("RMSE:", np.sqrt(mean_squared_error(y_test, y_pred)))
print("R2:  ", r2_score(y_test, y_pred))