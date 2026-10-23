from GA import GA

# 4 位策略仅用于手算演示；GUI 默认允许 20 或 50 位。
ga = GA(rows=3, cols=3, length=4, mutRate=0, seed=42)
ga.initialize("CCCC")
print("全 C 得分：", ga.findBest().getFitness())  # 64

# 修改左上角，再重算所有细胞得分
ga.pop[0][0].setCode("DDDD")
ga.calculateFitness()
for row in ga.pop:
    print([cell.getFitness() for cell in row])
# [96, 56, 56]
# [56, 56, 56]
# [56, 56, 56]

print("更新前 C 比例：", ga.cooperation())  # 8/9

ga.createNewPop()
print("当前代数：", ga.generation)  # 1
for row in ga.pop:
    print([cell.getCode() for cell in row])