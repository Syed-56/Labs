import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import warnings

warnings.filterwarnings('ignore')

# 1. Loading and Inspection
df = pd.read_csv('telecom_churn.csv') 
print(df.head())
print(df.shape)
print(df.info())

# 2. Data Transformation
df['churn'] = df['churn'].astype('int64')
d = {'no': False, 'yes': True}
df['international plan'] = df['international plan'].map(d)
df['voice mail plan'] = df['voice mail plan'].map(d)

# 3. Feature Engineering
total_calls = df['total day calls'] + df['total eve calls'] + df['total night calls'] + df['total intl calls']
df.insert(loc=len(df.columns), column='Total calls', value=total_calls)

# 4. Statistical Analysis
print(df.describe(include=['object', 'bool']))
print(df.sort_values(by='total day charge', ascending=False).head())

# Grouping example: Average daytime minutes for churned users
print(df[df['churn'] == 1]['total day minutes'].mean())

# Summary Tables (Crosstab)
print(pd.crosstab(df['churn'], df['international plan'], margins=True))

# 5. Visualizations
plt.figure(figsize=(10,6))
sns.countplot(x='international plan', hue='churn', data=df)
plt.title('Churn vs International Plan')
plt.show()

sns.countplot(x='customer service calls', hue='churn', data=df)
plt.show()