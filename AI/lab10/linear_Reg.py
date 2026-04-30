#objective: classify each flower that how much setosa-like it is.
from sklearn import datasets
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import r2_score

#Loading Iris Flower Dataset.
iris = datasets.load_iris()
x=iris.data
y=iris.target 
#classify class 0 as non-setosa and class 1 as setosa
y=(y==0).astype(int)
#split data into training and testing
x_train, x_test, y_train, y_test = train_test_split(x,y,test_size=0.3, random_state=42)  #means 70% train / 30% test

#Train Model
LR = LinearRegression()
model = LR.fit(x_train,y_train)
y_pred=model.predict(x_test)
print("Predictions: ", y_pred)  #close to 0 means flower might not be setosa and close to 1 means flower might be setosa. <1 or >1 means uncertain/extrapolating.
#find errors
teachLR = r2_score(y_test,y_pred)
accLR = teachLR*100
print("How much data is certain: ",accLR,"%")