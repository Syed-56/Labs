import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import warnings

warnings.filterwarnings('ignore')
plt.style.use('bmh')

# 1. Loading Data
df = pd.read_csv('house_prices_practice.csv')

# 2. Data Cleaning (Handling Missing Values)
# Keeping only columns that have at least 70% of their data (dropping those with >30% NaN)
df2 = df[[column for column in df if df[column].count() / len(df) >= 0.3]]
if 'Id' in df2.columns:
    del df2['Id']
df = df2

# 3. Distribution Analysis
print(df['SalePrice'].describe())
plt.figure(figsize=(9, 8))
sns.distplot(df['SalePrice'], color='g', bins=100, hist_kws={'alpha': 0.4})
plt.title('Housing Price Distribution')
plt.show()

# 4. Numerical Feature Analysis
df_num = df.select_dtypes(include=['float64', 'int64'])
# Plotting histograms for all numerical features
df_num.hist(figsize=(16, 20), bins=50, xlabelsize=8, ylabelsize=8)
plt.show()

# 5. Correlation Analysis ("Golden Features")
df_num_corr = df_num.corr()['SalePrice'][:-1] # Exclude SalePrice correlation with itself
golden_features_list = df_num_corr[abs(df_num_corr) > 0.5].sort_values(ascending=False)

print(f"There are {len(golden_features_list)} strongly correlated values with SalePrice:")
print(golden_features_list)