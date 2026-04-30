#objective: classify iris flowers as setosa v/s non-setosa using SVM+RBF kernel
from sklearn import datasets
from sklearn.svm import SVC
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
svm = SVC(kernel='rbf', C=1, gamma='scale') #higher C = narrow margin/less misclassification and higher gamma=more reach of training examples
# fit model by training on (x,y) predict y from x and comapre with real y
svm.fit(x_train,y_train)
y_pred=svm.predict(x_test)
acc_score = accuracy_score(y_test,y_pred)
print("SVM Accuracy: ", acc_score)