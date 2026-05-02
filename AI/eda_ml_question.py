#EDA
import warnings

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

warnings.filterwarnings('ignore')

#A1 - understanding dataset
df = pd.read_csv('lab11/mall_customers.csv')
print("First 5 Rows\n",df.head())
print("Shape\n",df.shape)
print("Data Types\n",df.dtypes)
print("Description\n",df.describe())
print("Missing Values Per Column: ", df.isnull().sum())

#A2 - Histogram
plt.figure(figsize=(10,5))
sns.histplot(df['Annual Income (k$)'], color='blue', bins=20, kde=True)
plt.title("Distribution of Annual Income")
plt.xlabel("Annual Income (k$")
plt.ylabel("Frequency")
plt.show()

plt.figure(figsize=(10,5))
sns.histplot(df['Spending Score (1-100)'], color='blue', bins=20, kde=True)
plt.title("Distribution of Spending Score")
plt.xlabel("Spending Score (1-100)")
plt.ylabel("Frequency")
plt.show()

#A3 - numeric values and correlation matrix
df_numeric = df.select_dtypes(include=['int64','float64'])
print("Numeric Only\n", df_numeric.head())
#customer_id is an identifier not a feature so remove from heatmap
df_numeric = df_numeric.drop(columns=['CustomerID'])
corr_matrix = df_numeric.corr()
print("Correlation Matrix\n",corr_matrix)
spending_corr = corr_matrix['Spending Score (1-100)'].drop('Spending Score (1-100)')
print("Correlations With Spending Score\n",spending_corr.sort_values(ascending=False))
stronger_corr = spending_corr.abs().idxmax()
print("Highest Correlation: ", stronger_corr)
plt.figure(figsize=(10,5))
sns.heatmap(corr_matrix,annot=True,cmap='coolwarm')
plt.title("Correlation Heatmap")
plt.show()

#A4 - scatterplot
plt.figure(figsize=(10,5))
sns.scatterplot(data=df,x='Annual Income (k$)', y='Spending Score (1-100)', hue='Gender', palette=['Blue', 'Green'])
plt.xlabel('Annual Income')
plt.ylabel('Spending Score')
plt.title('Annual Income vs Spending Score by Gender')
plt.legend(title='Gender')
plt.show()

# K-means

#B1 - elbow method
from sklearn.cluster import KMeans
from sklearn.preprocessing import StandardScaler
X = df[['Annual Income (k$)','Spending Score (1-100)']].values
print(X)
wcss = []
for i in range(1,11):
    kmeans = KMeans(n_clusters=i, init="k-means++" ,random_state=42)
    kmeans.fit(X)
    wcss.append(kmeans.inertia_)

plt.figure(figsize=(10,5))
plt.plot(range(1,11),wcss,marker='o',color='red',linestyle='--')
plt.title('Elbow Method')
plt.xlabel('Number of Clusters')
plt.ylabel('WCSS')
plt.show()  #k will be 5

#B2 - Train K means and viz clusters
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)
kmeans = KMeans(n_clusters=5, init="k-means++" ,random_state=42)
y_predict = kmeans.fit_predict(X_scaled)

plt.scatter(X[y_predict == 0, 0], X[y_predict == 0, 1], s = 100, c = 'blue', label = 'Cluster 1') #for first cluster
plt.scatter(X[y_predict == 1, 0], X[y_predict == 1, 1], s = 100, c = 'green', label = 'Cluster 2') #for second cluster
plt.scatter(X[y_predict == 2, 0], X[y_predict == 2, 1], s = 100, c = 'red', label = 'Cluster 3') #for third cluster
plt.scatter(X[y_predict == 3, 0], X[y_predict == 3, 1], s = 100, c = 'black', label = 'Cluster 4') #for fourth cluster
plt.scatter(X[y_predict == 4, 0], X[y_predict == 4, 1], s = 100, c = 'purple', label = 'Cluster 5') #for fifth cluster
centroid = scaler.inverse_transform(kmeans.cluster_centers_)
plt.scatter(centroid[:, 0], centroid[:,1], s = 50, c = 'yellow', label = 'Centroid')
plt.title('Clusters of customers')
plt.xlabel('Annual Income (k$)')
plt.ylabel('Spending Score (1-100)')
plt.legend()
plt.show()

# Supervised
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.svm import SVC
from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import mean_squared_error, f1_score, confusion_matrix, accuracy_score, r2_score

#C1-target variable
df['High Spender'] = (df['Spending Score (1-100)']>50).astype(int)
X = df[['Age','Annual Income (k$)',]]
Y = df[('High Spender')]

X_train, X_test, Y_train, Y_test = train_test_split(X, Y, test_size = 0.3, random_state = 42)
print("Train Data\n", X_train)
print("Test Data\n", X_test)

#C2 - Decision Tree and SVM
dt = DecisionTreeClassifier(random_state=42)
dt.fit(X_train, Y_train)
dt_train_acc = dt.score(X_train, Y_train)
dt_test_acc = accuracy_score(Y_test, dt.predict(X_test))
print("Decision Tree")
print("F1 Score: ", f1_score(Y_test, dt.predict(X_test), average='weighted'))
print("Training Accuracy: ", dt_train_acc)
print("Test Accuracy: ", dt_test_acc)
print("Confusion Matrix: ", confusion_matrix(Y_test, dt.predict(X_test)))

svm = SVC(kernel='rbf',C=1,gamma='scale')
svm.fit(X_train, Y_train)
svm_train_acc = svm.score(X_train, Y_train)
svm_test_acc = accuracy_score(Y_test, svm.predict(X_test))
print("SVM")
print("F1 Score: ", f1_score(Y_test, svm.predict(X_test), average='weighted'))
print("Training Accuracy: ", svm_train_acc)
print("Test Accuracy\n", svm_test_acc)
print("Confusion Matrix\n", confusion_matrix(Y_test, svm.predict(X_test)))

#C3 - Linear Regression
lr = LinearRegression()
lr.fit(X_train, Y_train)
y_pred = lr.predict(X_test)
r2 = r2_score(Y_test, y_pred)*100
mse = mean_squared_error(Y_test, y_pred)*100
print("Linear Regression")
print("R2 Score: ", r2)
print("MSE: ", mse)
#predicting new customer
new_customer = np.array([[30,60]])
prediction = lr.predict(new_customer)
if prediction[0]>=0.7:
    print("High Spender")
else:
    print("Low Spender")