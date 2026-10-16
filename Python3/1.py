import numpy as np

values = [1, 2, 3]
array = np.array(values, dtype=float) #将 values 转换成 NumPy 数组，并指定数组元素的数据类型为浮点数（float）
print(values * 2)  # [1, 2, 3, 1, 2, 3]：重复
print(array * 2)   # [2. 4. 6.]：元素级乘法
print(array + 1)   # [2. 3. 4.]