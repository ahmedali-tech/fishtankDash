import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import confusion_matrix, ConfusionMatrixDisplay
import matplotlib.pyplot as plt

df = pd.read_csv('FishMonitoringData_with_status.csv')
features = ['Temperature (C)', 'Dissolved Oxygen(g/ml)', 'PH', 'Height']
target = 'Tank_Status'

X = df[features]
y = df[target]

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

clf = DecisionTreeClassifier(random_state=42)
clf.fit(X_train, y_train)

accuracy = clf.score(X_test, y_test)
print(f'Model Accuracy: {accuracy:.2%}')

conf_matrix = confusion_matrix(y_test, clf.predict(X_test))

disp = ConfusionMatrixDisplay(conf_matrix, display_labels=clf.classes_)
disp.plot(cmap=plt.cm.Blues, values_format='d')
plt.title('Confusion Matrix')
plt.show()
