import pandas as pd
import numpy as np
from sklearn.feature_selection import RFE
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split
from imblearn.over_sampling import SMOTE
from sklearn.metrics import confusion_matrix
import warnings


# suppress pandas warning
warnings.simplefilter(action='ignore', category=FutureWarning)


data = pd.read_csv('./data/features_labels.csv', header=0)

print("Data shape:", data.shape)
print("Columns:", list(data.columns))


count_good = len(data[data['label'] == "Label.GOOD"])
count_avg = len(data[data['label'] == "Label.AVERAGE"])
count_bad = len(data[data['label'] == "Label.BAD"])
count_total = count_good + count_avg + count_bad
print("Good, average, bad:", count_good, count_avg, count_bad)
print("Good, average, bad ratios:", count_good/count_total, count_avg/count_total, count_bad/count_total)

# hot labeling categorical variable
data = pd.get_dummies(data, columns=["payment_method"])

print("Means of data by column for each tenant label")
print(data.groupby('label').mean().to_string())


# split the data into train and test

X = data.loc[:, data.columns != 'label']
y = data.loc[:, data.columns == 'label']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=1132132123)
print("data splited - train", len(y_train), "test", len(y_test))

# since the date is not uniform: do oversampling
os = SMOTE(random_state=0)
os_data_X, os_data_y = os.fit_sample(X_train, y_train.values.ravel())
os_data_X = pd.DataFrame(data=os_data_X, columns=X_train.columns)
os_data_y = pd.DataFrame(data=os_data_y, columns=['label'])

count_good = len(os_data_y[os_data_y['label'] == "Label.GOOD"])
count_avg = len(os_data_y[os_data_y['label'] == "Label.AVERAGE"])
count_bad = len(os_data_y[os_data_y['label'] == "Label.BAD"])
count_total = count_good + count_avg + count_bad
print("OVERSAMPLED: Good, average, bad:", count_good, count_avg, count_bad)
print("OVERSAMPLED: Good, average, bad ratios:", count_good/count_total, count_avg/count_total, count_bad/count_total)

# perform feature ranking
print("Feature ranking (Logistic regression)")
rfe = RFE(LogisticRegression(), 20)
rfe = rfe.fit(os_data_X, os_data_y.values.ravel())
print(rfe.ranking_)
print("All features are relevant in the model")

# do the logistic regression
model = LogisticRegression(solver='lbfgs', multi_class='multinomial', max_iter=2000)
result = model.fit(np.array(os_data_X.values), np.array(os_data_y.values).ravel())

score = model.score(X_test, y_test)
y_pred = model.predict(X_test)


print("Confusion matrix:\n", confusion_matrix(y_test, y_pred, labels=["Label.GOOD", "Label.AVERAGE", "Label.BAD"]))

print("Success score:", score)