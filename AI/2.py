import numpy as np
#打乱样本顺序、划分训练集和测试集
rng = np.random.default_rng(42)
indices = rng.permutation(5)
print(indices)