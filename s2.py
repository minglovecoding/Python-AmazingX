import bisect

def solve():
    # 读取 N（候选树的位置数量）和 K（约束区间数量）
    N, K = map(int, input().split())

    # 读取 N 个候选树的位置
    X = list(map(int, input().split()))

    # 读取每个约束区间 (l, r, t)
    ivals = []
    for _ in range(K):
        l, r, t = map(int, input().split())
        # 我们用 r 放前面是为了排序时优先按 r 升序排列（贪心策略）
        ivals.append((r, l, t))

    # 将树的位置排序（方便后续依次选择）
    X.sort()

    # 将所有区间按右端点 r 排序（贪心处理）
    ivals.sort()

    iX = 0  # 当前处理到第几个候选树
    stk = []  # 候选可以种植的树（候选池，栈结构，从右往左取）
    planted = []  # 已经种植的树的位置（保持升序，便于 bisect 查询）

    for r, l, t_low in ivals:
        # 将所有位置 <= r 的候选树加入“可以考虑种植”的候选池中
        while iX < len(X) and X[iX] <= r:
            # 添加一个二元组（位置, 索引），索引主要为了唯一性，防止位置重复
            stk.append((X[iX], iX))
            iX += 1

        # 查询当前区间 [l, r] 中，已经种植的树的数量
        # 使用二分查找：左边界和右边界的差值就是数量
        left = bisect.bisect_left(planted, l)
        right = bisect.bisect_right(planted, r)
        t_current = right - left

        # 如果不满足该区间需要至少种 t_low 棵树的约束，就从栈顶种树
        while t_current < t_low:
            # 没有树可选就会出错（题目保证有解）
            assert stk, "无可选树但约束未满足，说明题目输入有误"

            # 贪心地从最右边（后加入的）选择种植
            pos, _ = stk.pop()

            # 将该树插入到已种植列表中，并保持有序（使用 bisect.insort）
            bisect.insort(planted, pos)

            # 当前区间已种树数 +1
            t_current += 1

    # 输出未被种植的树的数量
    print(N - len(planted))


def main():
    # 读取测试用例数量
    T = int(input())
    for _ in range(T):
        solve()


if __name__ == "__main__":
    main()
