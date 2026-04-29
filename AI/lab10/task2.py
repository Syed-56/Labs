import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder, StandardScaler
from sklearn.impute import SimpleImputer
from sklearn.ensemble import RandomForestClassifier
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score, classification_report
import warnings
warnings.filterwarnings("ignore")

np.random.seed(42)
n = 500

employment_status = np.random.choice(["Employed", "Self-Employed", "Unemployed"], n, p=[0.6, 0.25, 0.15])
marital_status    = np.random.choice(["Single", "Married", "Divorced"], n, p=[0.4, 0.45, 0.15])
income            = np.random.normal(60000, 20000, n).clip(15000, 150000)
credit_score      = np.random.randint(300, 850, n)
loan_amount       = np.random.uniform(5000, 100000, n)

emp_map = {"Employed": 2, "Self-Employed": 1, "Unemployed": 0}
emp_numeric = np.array([emp_map[e] for e in employment_status])

prob_approve = (
    0.4 * (credit_score / 850)
    + 0.3 * (income / 150000)
    + 0.2 * (emp_numeric / 2)
    - 0.1 * (loan_amount / 100000)
)
loan_approved = (prob_approve + np.random.normal(0, 0.05, n) > 0.45).astype(int)

df = pd.DataFrame({
    "income":            income,
    "credit_score":      credit_score,
    "loan_amount":       loan_amount,
    "employment_status": employment_status,
    "marital_status":    marital_status,
    "loan_approved":     loan_approved,
})

for col, idx_count in [("income", 40), ("credit_score", 35)]:
    df.loc[np.random.choice(df.index, idx_count, replace=False), col] = np.nan

print("DATASET OVERVIEW")
print(df.head())
print(f"\nShape : {df.shape}")
print(f"\nMissing values:\n{df.isnull().sum()}")
print(f"\nClass distribution:\n{df['loan_approved'].value_counts()}")

print("PREPROCESSING")

num_cols = ["income", "credit_score", "loan_amount"]
imputer  = SimpleImputer(strategy="median")
df[num_cols] = imputer.fit_transform(df[num_cols])
print(f"Missing after imputation:\n{df.isnull().sum()}")

le = LabelEncoder()
df["employment_enc"] = le.fit_transform(df["employment_status"])
df["marital_enc"]    = le.fit_transform(df["marital_status"])
print("\nEmployment encoding:", dict(zip(le.classes_, le.transform(le.classes_))))

features = ["income", "credit_score", "loan_amount", "employment_enc", "marital_enc"]
X = df[features]
y = df["loan_approved"]

print("FEATURE IMPORTANCE (Random Forest)")

rf_temp = RandomForestClassifier(n_estimators=100, random_state=42)
rf_temp.fit(X, y)
imp_df = pd.DataFrame({
    "Feature":    features,
    "Importance": rf_temp.feature_importances_
}).sort_values("Importance", ascending=False)
print(imp_df.to_string(index=False))

print("MODEL TRAINING")

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42, stratify=y)
print(f"Train size: {X_train.shape[0]} | Test size: {X_test.shape[0]}")

scaler  = StandardScaler()
X_train_sc = scaler.fit_transform(X_train)
X_test_sc  = scaler.transform(X_test)

lr = LogisticRegression(random_state=42, max_iter=1000)
lr.fit(X_train_sc, y_train)

rf = RandomForestClassifier(n_estimators=200, random_state=42)
rf.fit(X_train, y_train)

print("MODEL EVALUATION")

for name, model, X_t in [("Logistic Regression", lr, X_test_sc), ("Random Forest", rf, X_test)]:
    preds = model.predict(X_t)
    print(f"\n--- {name} ---")
    print(f"  Accuracy  : {accuracy_score(y_test, preds):.4f}")
    print(f"  Precision : {precision_score(y_test, preds):.4f}")
    print(f"  Recall    : {recall_score(y_test, preds):.4f}")
    print(f"  F1-Score  : {f1_score(y_test, preds):.4f}")
    print(f"\n{classification_report(y_test, preds)}")

print("NEW APPLICANT PREDICTION")

new_applicant = pd.DataFrame([{
    "income":          75000,
    "credit_score":    720,
    "loan_amount":     30000,
    "employment_enc":  2,
    "marital_enc":     1,
}])

lr_pred = lr.predict(scaler.transform(new_applicant))[0]
lr_prob = lr.predict_proba(scaler.transform(new_applicant))[0][1]
rf_pred = rf.predict(new_applicant)[0]
rf_prob = rf.predict_proba(new_applicant)[0][1]

print("  Income          : $75,000")
print("  Credit Score    : 720")
print("  Loan Amount     : $30,000")
print("  Employment      : Employed")
print("  Marital Status  : Married")
print(f"\n  Logistic Regression -> {'APPROVED' if lr_pred else 'REJECTED'} (confidence: {lr_prob:.2%})")
print(f"  Random Forest       -> {'APPROVED' if rf_pred else 'REJECTED'} (confidence: {rf_prob:.2%})")