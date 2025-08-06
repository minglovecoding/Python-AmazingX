T=int(input())
while T:
    T-=1
    Elsie=0
    N=int(input())
    A=list(map(int,input().split()))
    #print(A)
    pre=[0]*(N+1)
    suf=[0]*(N+2)
    for i in range(1,N+1):
        pre[i]=pre[i-1]+A[i-1]
    for i in range(N,0,-1):
        suf[i]=suf[i+1]+A[i-1]
    for i in range(0,N//2):#0-N//2-1
        Elsie=max(Elsie,pre[i]+suf[N+1-(N//2-1-i)])
    print(pre[N]-Elsie,Elsie)