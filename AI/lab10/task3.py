import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder, StandardScaler
from sklearn.impute import SimpleImputer
from sklearn.svm import SVC
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import (confusion_matrix, accuracy_score,
                             precision_score, recall_score, f1_score,
                             classification_report)
import warnings
warnings.filterwarnings("ignore")

np.random.seed(42)
n = 600

contract_type   = np.random.choice(["Month-to-Month", "One Year", "Two Year"], n, p=[0.5, 0.3, 0.2])
internet_type   = np.random.choice(["DSL", "Fiber Optic", "No Internet"], n, p=[0.4, 0.4, 0.2])
tenure          = np.random.randint(1, 72, n).astype(float)
monthly_charges = np.random.uniform(20, 120, n)
support_calls   = np.random.randint(0, 10, n).astype(float)

contract_map = {"Month-to-Month": 0, "One Year": 1, "Two Year": 2}
internet_map = {"No Internet": 0, "DSL": 1, "Fiber Optic": 2}
c_num = np.array([contract_map[c] for c in contract_type])
i_num = np.array([internet_map[i] for i in internet_type])

churn_prob = (
    0.4 * (1 - c_num / 2)
    + 0.25 * (1 - tenure / 72)
    + 0.2 * (monthly_charges / 120)
    + 0.15 * (support_calls / 9)
    + np.random.normal(0, 0.05, n)
)
churn = (churn_prob > 0.45).astype(int)

df = pd.DataFrame({
    "tenure":          tenure,
    "monthly_charges": monthly_charges,
    "support_calls":   support_calls,
    "contract_type":   contract_type,
    "internet_type":   internet_type,
    "churn":           churn,
})

for col, count in [("tenure", 40), ("monthly_charges", 35), ("support_calls", 30)]:
    df.loc[np.random.choice(df.index, count, replace=False), col] = np.nan

outlier_idx = np.random.choice(df.index, 15, replace=False)
df.loc[outlier_idx, "monthly_charges"] = np.random.uniform(400, 600, 15)

print("=" * 58)
print("DATASET OVERVIEW")
print("=" * 58)
print(df.head())
print(f"\nShape  : {df.shape}")
print(f"\nMissing values:\n{df.isnull().sum()}")
print(f"\nClass distribution:\n{df['churn'].value_counts()}")

print("\n" + "=" * 58)
print("CLEANING — MISSING VALUES")
print("=" * 58)

num_cols = ["tenure", "monthly_charges", "support_calls"]
imputer  = SimpleImputer(strategy="median")
df[num_cols] = imputer.fit_transform(df[num_cols])
print(f"Missing after imputation:\n{df.isnull().sum()}")

print("\n" + "=" * 58)
print("CLEANING — OUTLIER DETECTION & TREATMENT (IQR)")
print("=" * 58)

for col in num_cols:
    Q1, Q3 = df[col].quantile(0.25), df[col].quantile(0.75)
    IQR    = Q3 - Q1
    lower, upper = Q1 - 1.5 * IQR, Q3 + 1.5 * IQR
    outliers = ((df[col] < lower) | (df[col] > upper)).sum()
    df[col]  = df[col].clip(lower, upper)
    print(f"  {col:20s} → {outliers} outliers clipped  [{lower:.2f}, {upper:.2f}]")

print("\n" + "=" * 58)
print("ENCODING CATEGORICAL VARIABLES")
print("=" * 58)

le = LabelEncoder()
df["contract_enc"] = le.fit_transform(df["contract_type"])
print(f"Contract   : {dict(zip(le.classes_, le.transform(le.classes_)))}")
df["internet_enc"] = le.fit_transform(df["internet_type"])
print(f"Internet   : {dict(zip(le.classes_, le.transform(le.classes_)))}")

features = ["tenure", "monthly_charges", "support_calls", "contract_enc", "internet_enc"]
X = df[features]
y = df["churn"]

print("\n" + "=" * 58)
print("FEATURE IMPORTANCE (Random Forest)")
print("=" * 58)

rf_temp = RandomForestClassifier(n_estimators=100, random_state=42)
rf_temp.fit(X, y)
imp_df = pd.DataFrame({
    "Feature":    features,
    "Importance": rf_temp.feature_importances_
}).sort_values("Importance", ascending=False)
print(imp_df.to_string(index=False))

print("\n" + "=" * 58)
print("EXTRACTED DECISION RULES (Top 3 Trees, Depth ≤ 2)")
print("=" * 58)

from sklearn.tree import export_text
small_rf = RandomForestClassifier(n_estimators=3, max_depth=2, random_state=42)
small_rf.fit(X, y)
for i, tree in enumerate(small_rf.estimators_):
    print(f"\n--- Tree {i+1} ---")
    print(export_text(tree, feature_names=features))

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2,
                                                     random_state=42, stratify=y)
print("=" * 58)
print(f"TRAIN/TEST SPLIT  →  Train: {X_train.shape[0]}  |  Test: {X_test.shape[0]}")
print("=" * 58)

scaler     = StandardScaler()
X_train_sc = scaler.fit_transform(X_train)
X_test_sc  = scaler.transform(X_test)

svm = SVC(kernel="rbf", C=1.0, gamma="scale", probability=True, random_state=42)
svm.fit(X_train_sc, y_train)

rf = RandomForestClassifier(n_estimators=200, random_state=42)
rf.fit(X_train, y_train)

print("\n" + "=" * 58)
print("SVM — DECISION BOUNDARY INFO")
print("=" * 58)
print(f"  Kernel           : RBF (non-linear hyperplane in feature space)")
print(f"  C (regularization): 1.0")
print(f"  Support vectors  : {svm.n_support_} (class 0, class 1)")
print(f"  Total SVs        : {sum(svm.n_support_)}")

print("\n" + "=" * 58)
print("MODEL EVALUATION")
print("=" * 58)

for name, model, X_t in [("SVM (RBF)", svm, X_test_sc), ("Random Forest", rf, X_test)]:
    preds = model.predict(X_t)
    cm    = confusion_matrix(y_test, preds)
    print(f"\n{'─'*40}")
    print(f"  {name}")
    print(f"{'─'*40}")
    print(f"  Confusion Matrix:\n{cm}")
    print(f"  TN={cm[0,0]}  FP={cm[0,1]}  FN={cm[1,0]}  TP={cm[1,1]}")
    print(f"\n  Accuracy  : {accuracy_score(y_test, preds):.4f}")
    print(f"  Precision : {precision_score(y_test, preds):.4f}")
    print(f"  Recall    : {recall_score(y_test, preds):.4f}")
    print(f"  F1-Score  : {f1_score(y_test, preds):.4f}")
    print(f"\n{classification_report(y_test, preds)}")

print("=" * 58)
print("NEW CUSTOMER CHURN PREDICTION")
print("=" * 58)

new_customer = pd.DataFrame([{
    "tenure":         5.0,
    "monthly_charges": 95.0,
    "support_calls":  7.0,
    "contract_enc":   0,
    "internet_enc":   2,
}])

svm_pred = svm.predict(scaler.transform(new_customer))[0]
svm_prob = svm.predict_proba(scaler.transform(new_customer))[0][1]
rf_pred  = rf.predict(new_customer)[0]
rf_prob  = rf.predict_proba(new_customer)[0][1]

print("  Tenure          : 5 months")
print("  Monthly Charges : $95")
print("  Support Calls   : 7")
print("  Contract        : Month-to-Month")
print("  Internet        : Fiber Optic")
print(f"\n  SVM           → {'CHURN' if svm_pred else 'STAY'} (churn probability: {svm_prob:.2%})")
print(f"  Random Forest → {'CHURN' if rf_pred  else 'STAY'} (churn probability: {rf_prob:.2%})")
print("=" * 58)