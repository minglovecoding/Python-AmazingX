#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int N,K;
    cin>>N>>K;

    vector<ll>layers;
    layers.push_back(0);
    for(int i=0;i<N;i++){
        ll year;
        cin>>year;
        ll layer=(year+11)/12;
        layers.push_back(layer);
    }
    
    //sort and unique
    sort(layers.begin(),layers.end());
    layers.erase(unique(layers.begin(),layers.end()),layers.end());

    ll answer=layers.back()*12;  //biggest gap time
    vector<ll>gaps;

    for(int i=1;i<layers.size();i++){
        ll empty=layers[i]-layers[i-1]-1; //must -1
        gaps.push_back(empty*12);
    }
    
    sort(gaps.rbegin(),gaps.rend());
    int skip=min(K-1,(int)gaps.size());
    
    for( int i=0;i<skip;i++){
        answer-=gaps[i];
    }
    
    cout<<answer<<"\n";
    return 0;
}