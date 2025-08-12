def cnt_diff(N):
    digits=len(str(N))
    ans=0
    for digit in range(1,digits+1):
        upper=min(N,int('5'+'0'*(digit-1))-1)
        low=int('4'*digit)
        ans+=max(upper-low,0)
    return ans

T=int(input())
for _ in range(T):
    N=int(input())
    print(cnt_diff(N))
