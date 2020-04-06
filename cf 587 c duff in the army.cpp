#include<bits/stdc++.h>
using namespace std;

#define mx 100005
#define LOG 21

int depth[mx];
int par[mx][LOG];
int ar[mx];
vector<int>g[mx],node[mx][LOG];
int n,m,q;

void dfs(int u,int p,int lvl)
{
    depth[u]=lvl;
    par[u][0]=p;
    for(auto v:g[u])
    {
        if(v==p)continue;
        dfs(v,u,lvl+1);
    }
}

vector<int> _merge(vector<int>&a,vector<int>&b)
{
    vector<int>c;
    merge(a.begin(),a.end(),b.begin(),b.end(),back_inserter(c));
    while(c.size()>10)c.pop_back();
    return c;
}

void init(int root)
{
    dfs(root,-1,1);
    for(int j=1;j<LOG;j++)
    {
        for(int i=1;i<=n;i++)
        {
            if(par[i][j-1]!=-1)
            {
                par[i][j]=par[par[i][j-1]][j-1];
                node[i][j]=_merge(node[i][j-1],node[par[i][j-1]][j-1]);
            }
            else par[i][j]=-1;
        }
    }
}

vector<int> lca(int u,int v)
{
    if(depth[u]<depth[v])swap(u,v);
    int diff=depth[u]-depth[v];
    vector<int>re;
    for(int i=LOG-1;i>=0;i--)
    {
        if(diff>=(1<<i))
        {
            diff-=(1<<i);
            re=_merge(re,node[u][i]);
            u=par[u][i];
        }
    }
    if(u==v)return _merge(re,node[u][0]);

    for(int i=LOG-1;i>=0;i--)
    {
        if(par[u][i]!=par[v][i])
        {
            re=_merge(re,node[u][i]);
            re=_merge(re,node[v][i]);
            u=par[u][i];
            v=par[v][i];
        }
    }
    re=_merge(re,node[u][0]);
    re=_merge(re,node[v][0]);
    re=_merge(re,node[par[v][0]][0]);
    return re;
}

int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    for(int i=1;i<=m;i++)
    {
        int x;
        scanf("%d",&x);
        node[x][0].push_back(i);

    }
    for(int i=1;i<=n;i++)
    {
        sort(node[i][0].begin(),node[i][0].end());
        while(node[i][0].size()>10)node[i][0].pop_back();
    }
    init(1);
    while(q--)
    {
        int x,y,a;
        scanf("%d%d%d",&x,&y,&a);
        vector<int>re=lca(x,y);
        int k=re.size();
        int ans=min(a,k);
        printf("%d ",ans);
        for(int i=0;i<ans;i++)
        {
            printf("%d ",re[i]);
        }
        printf("\n");
    }
    return 0;
}
