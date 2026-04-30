import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import OrdinalEncoder
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_absolute_error, mean_squared_error, r2_score
from sklearn.impute import SimpleImputer
import warnings
warnings.filterwarnings("ignore")

np.random.seed(42)
n = 300

participation_levels = np.random.choice(["Low", "Medium", "High"], size=n, p=[0.3, 0.4, 0.3])
study_hours         = np.random.uniform(1, 10, n)
attendance          = np.random.uniform(50, 100, n)
prev_grades         = np.random.uniform(40, 100, n)
internet_usage_hrs  = np.random.uniform(1, 8, n)

part_map = {"Low": 0, "Medium": 1, "High": 2}
part_numeric = np.array([part_map[p] for p in participation_levels])

final_score = (
    0.35 * prev_grades
    + 2.5 * study_hours
    + 0.15 * attendance
    + 3.0 * part_numeric
    - 1.2 * internet_usage_hrs
    + np.random.normal(0, 4, n) #noise
).clip(0, 100)

df = pd.DataFrame({
    "study_hours":       study_hours,
    "attendance":        attendance,
    "prev_grades":       prev_grades,
    "participation":     participation_levels,
    "internet_usage":    internet_usage_hrs,
    "final_score":       final_score,
})

#add missing values in 30 random rows.
missing_idx_sh = np.random.choice(df.index, size=30, replace=False)
missing_idx_at = np.random.choice(df.index, size=30, replace=False)
df.loc[missing_idx_sh, "study_hours"] = np.nan
df.loc[missing_idx_at, "attendance"]  = np.nan

print("DATASET OVERVIEW")
print(df.head())
print(f"\nShape: {df.shape}")
print(f"\nMissing values:\n{df.isnull().sum()}")

print("\nCLEANING")

#replace missing values with column's median
num_cols = ["study_hours", "attendance", "prev_grades", "internet_usage"]
imputer  = SimpleImputer(strategy="median")
df[num_cols] = imputer.fit_transform(df[num_cols])

print(f"Missing values after imputation:\n{df.isnull().sum()}")

encoder = OrdinalEncoder(categories=[["Low", "Medium", "High"]])
df["participation_enc"] = encoder.fit_transform(df[["participation"]])
print(f"\nParticipation encoding: Low=0, Medium=1, High=2")

features = ["study_hours", "attendance", "prev_grades", "participation_enc", "internet_usage"]
X = df[features]
y = df["final_score"]

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

model = LinearRegression()
model.fit(X_train, y_train)

print("\nFEATURE COEFFICIENTS (Linear Regression)")
coef_df = pd.DataFrame({
    "Feature":     features,
    "Coefficient": model.coef_
}).sort_values("Coefficient", ascending=False)
print(coef_df.to_string(index=False))
print(f"\nIntercept: {model.intercept_:.4f}")

y_pred = model.predict(X_test)

mae  = mean_absolute_error(y_test, y_pred)
rmse = np.sqrt(mean_squared_error(y_test, y_pred))
r2   = r2_score(y_test, y_pred)

print("\nMODEL EVALUATION (Test Set)")
print(f"  MAE  : {mae:.2f}")
print(f"  RMSE : {rmse:.2f}")
print(f"  R²   : {r2:.4f}")

new_student = pd.DataFrame([{
    "study_hours":       7.0,
    "attendance":        85.0,
    "prev_grades":       78.0,
    "participation_enc": 2.0,
    "internet_usage":    3.0,
}])

predicted_score = model.predict(new_student)[0]

print("\nNEW STUDENT PREDICTION")
print("  Study Hours      : 7.0")
print("  Attendance       : 85%")
print("  Previous Grades  : 78")
print("  Participation    : High")
print("  Internet Usage   : 3 hrs/day")
print(f"\n  Predicted Final Score: {predicted_score:.2f} / 100")