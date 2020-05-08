#include<bits/stdc++.h>
using namespace std;
namespace MO{
    const int MAXN = 100005;
    const int MAXQ = 100005;

    int Sz,somoy=0;
    int col[MAXN];
    int blkId[MAXN];
    bool vis[MAXN],visit[MAXN];
    vector<int>g[MAXN];
    int st[MAXN],en[MAXN];
    int time_col[MAXN];
    int freq[MAXN];
    struct Query{
        int L,R,id,k;
        Query(){}
        Query(int x,int y,int i,int K){L=x;R=y;id=i;k=K;}
        bool operator<(const Query other) const{
            int a = blkId[L]; int b = blkId[other.L];
            return a == b ? (a & 1 ? (R > other.R) : (R < other.R)) : a < b;
        }
    }qry[MAXQ];
    int perQ[MAXQ];
    int Count[MAXN];

    void Check(int x){
        if(!vis[x]){
            vis[x]=1;
            int color=time_col[x];
            Count[color]++;
            if(Count[color]>=0) freq[Count[color]]++;
        }
        else{
            vis[x]=0;
             int color=time_col[x];
            if(Count[color]>=0) freq[Count[color]]--;
            Count[color]--;
        }
    }
    void dfs(int u)
    {
        visit[u]=1;
        st[u]=++somoy;
        time_col[somoy]=col[u];
        for(auto it:g[u])
        {
            if(visit[it])continue;
            dfs(it);
        }
        en[u]=somoy;
    }
}

using namespace MO;

int main(){
    int N,Q;
    scanf("%d %d",&N,&Q);

    //Initiate Global
    Sz=sqrt(N);
    memset(vis,0,sizeof(vis));
    memset(visit,0,sizeof(visit));
    memset(Count,0,sizeof(Count));
    for(int i=0;i<=N;i++) blkId[i] = i/Sz;

    for(int i=1;i<=N;i++) scanf("%d",&col[i]);
    for(int i=1;i<N;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dfs(1);
    for(int i=1;i<=Q;i++){
        int l,k;
        scanf("%d %d",&l,&k);
        qry[i] = Query(st[l],en[l],i,k);
    }
    sort(qry+1,qry+Q+1);

    int left = qry[1].L;
    int right = left-1;

    for(int i=1;i<=Q;i++){
        Query now = qry[i];
        while(left<now.L)  Check(left++);
        while(left>now.L)  Check(--left);
        while(right<now.R) Check(++right);
        while(right>now.R) Check(right--);
        perQ[now.id] = freq[now.k];
    }
    for(int i=1;i<=Q;i++)
    {
        printf("%d\n",perQ[i]);
    }
    return 0;
}
