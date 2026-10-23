#表示一个细胞的策略：保存 C/D 字符串和适应度，提供策略交叉、变异操作。


def payoff(move1, move2):
    if move1 not in ('C', 'D') or move2 not in ('C', 'D'):
        raise ValueError('Moves must be C or D')
    if move1 == 'C' and move2 == 'C':
        return 2, 2
    elif move1 == 'C' and move2 == 'D':
        return 0, 3
    elif move1 == 'D' and move2 == 'C':
        return 3, 0
    else:
        return 1, 1


def play_game(strategy1, strategy2):
    if len(strategy1) != len(strategy2):
        raise ValueError('Strategies must have equal lengths')
    score1 = score2 = 0
    for move1, move2 in zip(strategy1, strategy2):
        points1, points2 = payoff(move1, move2)
        score1 += points1
        score2 += points2
    return score1, score2


if __name__ == '__main__':
    score1, score2 = play_game('CCCC', 'DDDD')
    print('1 score:', score1)
    print('2 score:', score2)
