import pandas as pd

df = pd.DataFrame({
    "hours": [4.0, 1.0, 3.0],
    "attendance": [0.9, 0.5, 0.8],
    "label": [1, 0, 1],
})

"""
print(df.head())  #head() 默认显示前 5 行
print(df.shape)   # (3, 3)
print(df.dtypes)  # 数据类型
print(df["label"].value_counts()) #统计各标签的数量
selected = df.loc[df["hours"] >= 3, ["hours", "label"]]  #df.loc[选哪些行, 选哪些列]
print(selected)
print(df.iloc[0])                     # 按位置取第一行
X = df[["hours", "attendance"]].to_numpy(dtype=float)  #选取两列特征，再转换为浮点 NumPy 数组
y = df["label"].to_numpy(dtype=int)  #取出标签列，转换成整数 NumPy 数组
print(X.shape, y.shape)               # (3, 2) (3,)
"""