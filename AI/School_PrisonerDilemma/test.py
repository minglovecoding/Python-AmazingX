#验证计分
from PrisonerDilemma import play_game

print(play_game("CCCC","CCCC"))
print(play_game("DDDD","CCCC"))
print(play_game("DDDD","DDDD"))

#观察交叉和变异
from Chromosome import Chromosome
a = Chromosome("CCCCCCCC")
b = Chromosome("DDDDDDDD")

children = a.makeChildren(b)
print("孩子1：", children[0].getCode())
print("孩子2：", children[1].getCode())

new_a = a.mutate()
print("变异后：", new_a.getCode())
print("原来的a：", a.getCode())

#运行没有窗口的小网格
from GA import GA

ga = GA(rows=3, cols=3, length=20, mutRate=0, seed=42)
ga.initialize("C" * 20)

print(ga.findBest().getFitness())  # 320
print(ga.cooperation())           # 1.0

ga.createNewPop()
print(ga.cooperation())           # 1.0