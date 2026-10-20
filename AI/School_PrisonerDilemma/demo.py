"""
from GA import GA

# 创建 3行 × 3列，共9个细胞的小网格
ga = GA(rows=3, cols=3, length=20, mutRate=0, seed=42)

# 将所有细胞的策略设为20个C
ga.initialize("C" * 20)

# 逐行打印策略
for row in ga.pop:
    print([cell.getCode() for cell in row])

# 逐行打印得分
for row in ga.pop:
    print([cell.getFitness() for cell in row])
"""

#所有人全合作、没有变异，且没有严格更优秀的邻居，策略保持不变。
from GA import GA

ga = GA(rows=3, cols=3, length=20, mutRate=0, seed=42)
ga.initialize("C" * 20)

print(ga.findBest().getFitness())  # 320
print(ga.cooperation())           # 1.0

ga.createNewPop()
print(ga.cooperation())           # 1.0