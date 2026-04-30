#classify setosa vs non-setora using decision tree
from sklearn import datasets
from sklearn.tree import DecisionTreeClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score

#Loading Iris Flower Dataset.
iris = datasets.load_iris()
x=iris.data
y=iris.target 
#classify class 0 as non-setosa and class 1 as setosa
y=(y==0).astype(int)
#split data into training and testing
x_train, x_test, y_train, y_test = train_test_split(x,y,test_size=0.3, random_state=42)  #means 70% train / 30% test

#Train Model
DT = DecisionTreeClassifier()
model = DT.fit(x_train,y_train)
y_pred=model.predict(x_test)
print("Predictions: ", y_pred)  #0=non-setosa, 1=setosa

#Training Accuracy
accDT=DT.score(x_train,y_train)
trainingAccDT=accDT*100
print("Training Accuracy: ",trainingAccDT,"%")

#Testing Accuracy
accDT=accuracy_score(y_test,y_pred)
testingaccDT=accDT*100
print("Testing Accuracy: ",testingaccDT,"%")
#both are 100 bcz petal-length easily seperates them