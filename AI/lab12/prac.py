import matplotlib.pyplot as plt
from sklearn.cluster import KMeans
from sklearn.preprocessing import StandardScaler
import pandas as pd

df = pd.read_csv('house_prices_practice.csv')
X = df[['Annual Income (k$)','Spending Score (1-100)']].values
wcss = []

for i in range(1,11):
    kmeans = KMeans(n_clusters=i, init="k-means++", random_state=42)
    kmeans.fit(X)
    wcss.append(kmeans.inertia_)

plt.figure(figsize=(10,5))
plt.plot(range(1,11),wcss,marker='o',color='blue',linestyle='--')
plt.title('K means')
plt.xlabel('Number of Clusters')
plt.ylabel('k value')
plt.show()

scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)
kmeans = KMeans(n_clusters=5, init="k-means++", random_state=42)
y_pred = kmeans.fit_predict(X_scaled)

plt.scatter(X[y_pred==0,0],X[y_pred==0,1],s=100,c='Blue',label='Cluster 1')
plt.scatter(X[y_pred==1,0],X[y_pred==1,1],s=100,c='Blue',label='Cluster 2')
plt.scatter(X[y_pred==2,0],X[y_pred==2,1],s=100,c='Blue',label='Cluster 3')
plt.scatter(X[y_pred==3,0],X[y_pred==3,1],s=100,c='Blue',label='Cluster 4')
plt.scatter(X[y_pred==4,0],X[y_pred==4,1],s=100,c='Blue',label='Cluster 5')
centroid = scaler.inverse_transform(kmeans.cluster_centers_)
plt.scatter(centroid[:0],centroid[:1],s=50,c='yellow',label='Centroid')

plt.figure(figsize=(10,5))
plt.title('Clustering')
plt.xlabel('Annual Income')
plt.ylabel('Spending Score')
plt.legend()
plt.show()