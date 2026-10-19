"""Run with: python3 -m unittest -v test_model.py"""
import random
import unittest
from unittest.mock import patch
from Chromosome import Chromosome
from GA import GA
from PrisonerDilemma import payoff, play_game


class ModelTests(unittest.TestCase):
    def test_payoffs(self):
        for moves, expected in [(('C','C'),(2,2)), (('C','D'),(0,3)),
                                (('D','C'),(3,0)), (('D','D'),(1,1))]:
            self.assertEqual(payoff(*moves), expected)
        self.assertEqual(play_game('CCCC', 'DDDD'), (0,12))
        with self.assertRaises(ValueError): play_game('C', 'DD')
        with self.assertRaises(ValueError): payoff('X','C')

    def test_eight_unique_neighbors(self):
        for rows, cols in [(3,3), (4,5), (20,20)]:
            ga = GA(rows, cols)
            for row in range(rows):
                for col in range(cols):
                    n = set(ga.neighbors(row,col))
                    self.assertEqual(len(n),8)
                    self.assertNotIn((row,col),n)
            self.assertIn((rows-1,cols-1), set(ga.neighbors(0,0)))

    def test_uniform_scores_and_no_crossover_on_ties(self):
        ga = GA(3,3,mutRate=0)
        for code, score, cooperation in [('C'*20,320,1), ('D'*20,160,0)]:
            ga.initialize(code)
            self.assertTrue(all(c.fitness == score for row in ga.pop for c in row))
            with patch.object(Chromosome, 'makeChildren', side_effect=AssertionError('tie crossed')):
                ga.createNewPop()
            self.assertTrue(all(c.code == code for row in ga.pop for c in row))
            self.assertEqual(ga.cooperation(),cooperation)

    def test_mixed_scores_against_independent_directed_total(self):
        ga = GA(4,5,seed=12)
        for row in range(ga.rows):
            for col in range(ga.cols):
                expected = sum(play_game(ga.pop[row][col].code, ga.pop[r][c].code)[0]
                               for r,c in ga.neighbors(row,col))
                self.assertEqual(ga.pop[row][col].fitness,expected)

    def test_local_selection_and_synchronous_generation(self):
        ga = GA(3,3,mutRate=0,seed=3)
        ga.initialize('C'*20)
        ga.pop[0][0].setCode('D'*20)
        ga.calculateFitness()
        old = ga.pop
        self.assertEqual(old[0][0].fitness,480)
        self.assertIsNone(ga.selectParents(0,0)[1])
        for row in range(3):
            for col in range(3):
                if (row,col)!=(0,0):
                    self.assertIs(ga.selectParents(row,col)[1],old[0][0])
        observed=[]
        def cross(parent,partner):
            self.assertIs(ga.pop,old)
            self.assertEqual(old[0][0].code,'D'*20)
            observed.append((parent,partner))
            return [Chromosome(partner.code), Chromosome(partner.code)]
        with patch.object(Chromosome,'makeChildren',cross): ga.createNewPop()
        self.assertEqual(len(observed),8)
        self.assertTrue(all(c.code=='D'*20 for row in ga.pop for c in row))
        self.assertTrue(all(c.fitness==160 for row in ga.pop for c in row))

    def test_crossover_and_mutation(self):
        rng=random.Random(5)
        a=Chromosome('C'*20,rng=rng);b=Chromosome('D'*20,rng=rng)
        children=a.makeChildren(b)
        self.assertEqual(len(children),2)
        for child in children:
            self.assertEqual(len(child.code),20)
            self.assertEqual(set(child.code),set('CD'))
        mutated=a.mutate()
        self.assertEqual(sum(x!=y for x,y in zip(a.code,mutated.code)),1)
        self.assertEqual(a.code,'C'*20)
        ga=GA(3,3,mutRate=1)
        ga.initialize('C'*20);ga.createNewPop()
        self.assertTrue(all(c.code.count('D')==1 for row in ga.pop for c in row))

    def test_reproducibility_and_fifty_rounds(self):
        a=GA(4,5,length=50,seed=42);b=GA(4,5,length=50,seed=42)
        for _ in range(10):a.createNewPop();b.createNewPop()
        self.assertEqual(a.pop,b.pop)
        self.assertEqual(a.generation,10)
        self.assertTrue(all(len(c.code)==50 and set(c.code)<=set('CD')
                            for row in a.pop for c in row))

    def test_maximizing_fitness(self):
        ga=GA(3,3,seed=1)
        values=[c.fitness for row in ga.pop for c in row]
        self.assertEqual(ga.findBest().fitness,max(values))
        self.assertEqual(ga.findWorst().fitness,min(values))
        self.assertLess(ga.findBest().compareFitness(ga.findWorst()),1)

    def test_invalid_settings(self):
        for settings in [dict(rows=2),dict(cols=2),dict(length=1),dict(mutRate=-.1),dict(mutRate=1.1)]:
            with self.assertRaises(ValueError):GA(**settings)
        for code in ['CCX','C','']:
            with self.assertRaises(ValueError):Chromosome(code)


if __name__=='__main__':
    unittest.main()
