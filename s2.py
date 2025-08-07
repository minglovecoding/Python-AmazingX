""" 
3
7 1
8 4 10 1 2 6 7
2 9 3
7 2
8 4 10 1 2 6 7
2 9 3
1 10 1
7 2
8 4 10 1 2 6 7
2 9 3
1 10 4

4
4
3
"""
import bisect
def solve():
    N,K=map(int,input().split())
    A=list(map(int,input().split()))
    _K=[]
    for _ in range(K):
        l,r,t=map(int,input().split())
        _K.append((r,l,t))
    _K.sort()
    stack=[]
    planted=[]
    A.sort()
    index=0
    for r,l,t in _K:
        #将可种植的树放入stack里
        while index<N and A[index]<=r:
            stack.append(A[index])
            index+=1
        _t=bisect.bisect_right(planted,r)-bisect.bisect_left(planted,l)
        while _t<t:
            assert stack,"Error"
            #选最右侧的
            pos=stack.pop()
            bisect.insort(planted,pos)
            _t+=1
    print(N-len(planted))

def main():
    T=int(input())
    for _ in range(T):
        solve()

if __name__=="__main__":
    main()