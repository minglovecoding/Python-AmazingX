import sys

def solve():
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    it = iter(data)
    T = int(next(it))
    k = int(next(it))

    pick = [
        ['C', 'C', 'W'],
        ['C', 'C', 'O'],
        ['W', 'O', 'C']
    ]

    pos = [
        {'C': 0, 'O': 1, 'W': 2},
        {'O': 0, 'W': 1, 'C': 2},
        {'W': 0, 'C': 1, 'O': 2}
    ]

    def typ(first_char):
        if first_char == ord('C'):
            return 0
        if first_char == ord('O'):
            return 1
        return 2

    out_lines = []
    for _ in range(T):
        FjString = int(next(it))
        S = next(it).decode()
        N = FjString
        L = 3 * N

        if N % 2 == 1:
            out_lines.append("-1")
            continue

        mid = L // 2
        if S[:mid] == S[mid:]:
            out_lines.append("1")
            out_lines.append(" ".join(["1"] * L))
            continue

        half = N // 2
        assign = [0] * L
        Sb = S.encode()

        for i in range(half):
            lb = 3 * i
            rb = 3 * (i + half)

            t1 = typ(Sb[lb])
            t2 = typ(Sb[rb])
            ch = pick[t1][t2]

            p1 = pos[t1][ch]
            p2 = pos[t2][ch]

            assign[lb + p1] = 1
            assign[lb + (p1 + 1) % 3] = 2
            assign[lb + (p1 + 2) % 3] = 2

            assign[rb + p2] = 1
            assign[rb + (p2 + 1) % 3] = 2
            assign[rb + (p2 + 2) % 3] = 2

        out_lines.append("2")
        out_lines.append(" ".join(map(str, assign)))

    sys.stdout.write("\n".join(out_lines))

if __name__ == "__main__":
    solve()
