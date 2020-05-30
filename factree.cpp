#include<bits/stdc++.h>
using namespace std;

#define mx 100005
#define mod 1000000007
#define ll long long
ll inv[mx*20];
vector<int>g[mx];
ll ans[mx];
int Euler[2*mx],visit[mx];
int ar[mx],st[mx],en[mx];
int depth[mx],par[mx][25];
int Time=1,LOG;
vector<pair<int,int>>pf[mx];  /// using vector instand of map
ll tem[1000005];

#define query pair<pair<int,int>,pair<int,int>>
vector<query>q;
#define L first.first
#define R first.second
#define lca second.first
#define idx second.second
int block=sqrt(mx);
int n,m;
ll re=1;

bool cmp(const query &a,const query &b)
{
    if(a.L/block!=b.L/block)return a.L/block<b.L/block;
    if((a.L/block)&1)return a.R>b.R;
    return a.R<b.R;
}

void dfs(int cur,int pre,int lvl)
{
    par[cur][0]=pre;
    depth[cur]=lvl;
    Euler[Time]=cur;
    st[cur]=Time++;
    for(auto it:g[cur])
    {
        if(it!=pre)
        {
            dfs(it,cur,lvl+1);
        }
    }
    Euler[Time]=cur;
    en[cur]=Time++;
}

void init()
{
    dfs(1,-1,1);
    for(int j=1; j<=LOG; j++)
    {
        for(int i=1; i<=n; i++)
        {
            if(par[i][j-1]!=-1)
            {
                par[i][j]=par[par[i][j-1]][j-1];
            }
            else par[i][j]=-1;
        }
    }
}

int LCA(int u,int v)
{
    if(depth[u]<depth[v])swap(u,v);
    int log=1;
    while(1)
    {
        int next=log+1;
        if(depth[u]<(1<<next))break;
        log++;
    }

    for(int i=log; i>=0; i--)
    {
        if(depth[u]-(1<<i)>=depth[v])
        {
            u=par[u][i];
        }
    }
    if(u==v)return u;

    for(int i=log; i>=0; i--)
    {
        if(par[u][i]!=-1 && par[u][i]!=par[v][i])
        {
            u=par[u][i];
            v=par[v][i];
        }
    }
    return par[v][0];
}

void Add(int node)
{
    for(auto it:pf[node])
    {
        re=(re*inv[tem[it.first]+1])%mod;
        tem[it.first]+=it.second;
        re=(re*(tem[it.first]+1))%mod;
    }
}
void Remove(int node)
{
    for(auto it:pf[node])
    {
        re=(re*inv[tem[it.first]+1])%mod;
        tem[it.first]-=it.second;
        re=(re*(tem[it.first]+1))%mod;
    }
}
void func(int pos)
{
    int node=Euler[pos];
    if(visit[node])
    {
        Remove(node);
    }
    else Add(node);
    visit[node]^=1;
}


void solve()
{
    scanf("%d",&n);
    LOG=log2(n)+1;
    for(int i=1; i<n; i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    for(int i=1; i<=n; i++)
    {
        scanf("%d",&ar[i]);
        int x=ar[i];
        for(int j=2; j*j<=x; j++)
        {
            int cnt=0;
            while(x%j==0)
            {
                x/=j;
                cnt++;
            }
            if(cnt)pf[i].push_back({j,cnt});
        }
        if(x>1)pf[i].push_back({x,1});
    }
    init();
    scanf("%d",&m);
    for(int i=1; i<=m; i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        if(st[u]>st[v])swap(u,v);
        int p=LCA(u,v);
        if(p!=u)
        {
            q.push_back({{en[u],st[v]},{st[p],i}});
        }
        else q.push_back({{st[u],st[v]},{-1,i}});
    }
    sort(q.begin(),q.end(),cmp);
    int l=1,r=0;
    for(auto it:q)
    {
        while(l>it.L)func(--l);
        while(r<it.R)func(++r);
        while(l<it.L)func(l++);
        while(r>it.R)func(r--);
        if(it.lca!=-1)func(it.lca);
        ans[it.idx]=re;
        if(it.lca!=-1)func(it.lca);
    }
    for(int i=1; i<=m; i++)printf("%lld\n",ans[i]);

    for(int i=1;i<=n;i++)
    {
        g[i].clear();
        visit[i]=0;
        pf[i].clear();
    }
    memset(tem,0,sizeof(tem));
    q.clear();
    Time=1;
    re=1;

}
int main()
{
    int t;
    inv[0]=1;
    inv[1]=1;
    for(int i=2;i<20*mx;i++)inv[i] = ((inv[mod%i])*(mod - mod/i)) % mod;
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
