#include<bits/stdc++.h>
using namespace std;

#define mx 100005
#define LOG 22

int par[mx][LOG];
int val[mx][LOG];
int depth[mx];
vector<pair<int,int>>g[mx];
int n;

void dfs(int u,int p,int lvl)
{
    par[u][0]=p;
    depth[u]=lvl;

    for(auto it:g[u])
    {
        int v=it.first;
        int w=it.second;
        if(v==p)continue;
        val[v][0]=w;
        dfs(v,u,lvl+1);
    }
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
                val[i][j]=val[i][j-1]+val[par[i][j-1]][j-1];
            }
            else par[i][j]=-1;
        }
    }
}

int lca(int u,int v)
{
    if(depth[u]<depth[v])swap(u,v);
    int diff=depth[u]-depth[v];
    int re=0;
    for(int i=LOG-1;i>=0;i--)
    {
        if(diff>=(1<<i))
        {
            diff-=(1<<i);
            re+=val[u][i];
            u=par[u][i];

        }
    }
    if(u==v)return re;

    for(int i=LOG-1;i>=0;i--)
    {
        if(par[u][i]!=par[v][i])
        {
            re+=val[u][i]+val[v][i];
            u=par[u][i];
            v=par[v][i];
        }
    }
    re+=val[u][0]+val[v][0];
    return re;
}

int main()
{
    scanf("%d",&n);

    for(int i=1;i<n;i++)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        ++x,++y;
        g[x].push_back({y,w});
        g[y].push_back({x,w});
    }
    init(1);
    int q;
    scanf("%d",&q);
    while(q--)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        printf("%d\n",lca(x+1,y+1));
    }

    return 0;
}
