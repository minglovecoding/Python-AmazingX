#表示一个细胞的策略：保存 C/D 字符串和适应度，提供策略交叉、变异操作。
import random


class Chromosome:
    def __init__(self, in_code=None, length=20, rng=None):#rng 是随机数生成工具。如果外部传入带种子的生成器，就使用它
        self.rng = rng if rng is not None else random
        if in_code is None:
            if length < 2:
                raise ValueError('Strategy length must be at least 2')
            in_code = ''.join(self.randChar() for _ in range(length)) #随机产生 length 个 C/D，再拼成字符串
        self.setCode(in_code)

    def getCode(self):
        return self.code

    def setCode(self, in_code):#修改策略
        if not isinstance(in_code, str) or len(in_code) < 2 or set(in_code) - set('CD'):
            raise ValueError('Strategy must contain at least two C/D characters')
        self.code = in_code
        # 适应度来自与邻居的对局，不能仅根据字符串本身计算。
        self.fitness = 0

    def getFitness(self):
        return self.fitness

    def setFitness(self, fitness):
        self.fitness = fitness

    def randInt(self, min_val, max_val):
        return self.rng.randrange(min_val, max_val)

    def randChar(self):
        return self.rng.choice('CD')

    def mutate(self):#变异
        # 沿用学校“一个染色体发生一次单点变异”的方式。
        # C/D 翻转保证真正改变该位，不生成其他字符。
        index = self.randInt(0, len(self.code))
        code_arr = list(self.code)
        code_arr[index] = 'D' if code_arr[index] == 'C' else 'C'
        return Chromosome(''.join(code_arr), rng=self.rng)

    def makeChildren(self, partner):#交叉
        if len(self.code) != len(partner.code):
            raise ValueError('Parents must have equal lengths')
        crossover_index = self.randInt(1, len(self.code))
        return [
            Chromosome(self.code[:crossover_index] + partner.code[crossover_index:], rng=self.rng),
            Chromosome(partner.code[:crossover_index] + self.code[crossover_index:], rng=self.rng),
        ]

    def compareFitness(self, g):#比较得分
        # 保留学校“负数表示自己更好”的接口，但现在分数越高越好。
        if self.fitness > g.fitness:
            return -1
        if self.fitness < g.fitness:
            return 1
        return 0

    def __eq__(self, other):#判断两个对象是否相等
        return (isinstance(other, Chromosome)
                and self.code == other.code and self.fitness == other.fitness)
