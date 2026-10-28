#GA.py 创建策略网格，计算本代比赛总分，为每格选择更优秀邻居，生成并变异孩子，最后同步换成下一代。
import random
from Chromosome import Chromosome
from PrisonerDilemma import play_game


class GA:
    def __init__(self, rows=20, cols=20, length=20, mutRate=0.03, seed=None):
        if rows < 3 or cols < 3:
            raise ValueError('At least 3 rows and 3 columns are required')
        if length < 2:
            raise ValueError('Strategy length must be at least 2')
        if not 0 <= mutRate <= 1:
            raise ValueError('Mutation probability must be between 0 and 1')
        self.rows, self.cols = rows, cols
        self.length = length
        self.mutProb = mutRate
        self.rng = random.Random(seed)
        self.generation = 0
        self.initialize()

    def initialize(self, code=None):
        if code is not None and len(code) != self.length:
            raise ValueError('Initial strategy length differs from configured length')
        #self.pop 是一个二维列表，每个元素是一个独立的 Chromosome 对象。
        self.pop = [
            [Chromosome(code, length=self.length, rng=self.rng) for _ in range(self.cols)]
            for _ in range(self.rows)
        ]
        self.generation = 0
        self.calculateFitness()

    def neighbors(self, row, col):
        # 与学校 count_neighbors 一样使用取模环绕边界。
        for dr in (-1, 0, 1):
            for dc in (-1, 0, 1):
                if dr != 0 or dc != 0:
                    yield (row + dr) % self.rows, (col + dc) % self.cols #yield依次提供八个邻居

    def calculateFitness(self):#计算所有细胞的比赛总分
        for row in self.pop:
            for cell in row:
                cell.setFitness(0)
        # 每对邻居只比赛一次，同时为双方加分，避免双重计分。
        for row in range(self.rows):
            for col in range(self.cols):
                cell = self.pop[row][col]
                for nr, nc in self.neighbors(row, col):
                    if (nr, nc) > (row, col):  #用于避免一对邻居重复比赛，不是比较得分
                        neighbor = self.pop[nr][nc]
                        own_points, other_points = play_game(cell.code, neighbor.code)
                        cell.fitness += own_points
                        neighbor.fitness += other_points

    def selectParents(self, row, col):#	为某个细胞选择更优秀的邻居
        parent = self.pop[row][col]
        neighbors = [self.pop[r][c] for r, c in self.neighbors(row, col)]
        best_score = max(cell.fitness for cell in neighbors)
        if best_score <= parent.fitness:
            return parent, None  #表示没有交叉对象
        best = [cell for cell in neighbors if cell.fitness == best_score]
        return parent, self.rng.choice(best)  #从列表 best 中随机选择一个元素

    def createNewPop(self):#组织交叉、变异，并同步更新整个网格
        self.calculateFitness()
        newPop = []
        for row in range(self.rows):
            newRow = []
            for col in range(self.cols):
                parent, partner = self.selectParents(row, col)
                if partner is not None:
                    # 图片要求有更优秀邻居就交叉，不再额外使用 0.8 的交叉概率。
                    child = self.rng.choice(parent.makeChildren(partner))
                else:
                    child = Chromosome(parent.code, rng=self.rng)  #没有更优秀邻居，就创建一个策略相同的新对象
                # 沿用学校 GA 的含义：以 mutProb 概率对一个孩子变异一位。
                if self.rng.random() < self.mutProb:
                    child = child.mutate()
                newRow.append(child)
            newPop.append(newRow)
        # 读完旧一代后再统一替换，与学校同步更新结构一致。
        self.pop = newPop
        self.generation += 1
        # 为当前显示的一代计算其自身得分，保证鼠标信息与网格一致。
        self.calculateFitness()
   
    def findBest(self):  #查询最好个体
        return max((cell for row in self.pop for cell in row), key=lambda c: c.fitness)

    def findWorst(self):  #查询最差个体
        return min((cell for row in self.pop for cell in row), key=lambda c: c.fitness)

    def cooperation(self):  #统计合作比例
        return sum(cell.code.count('C') for row in self.pop for cell in row) / (
            self.rows * self.cols * self.length)

    def randInt(self, min_val, max_val):
        return self.rng.randrange(min_val, max_val)
