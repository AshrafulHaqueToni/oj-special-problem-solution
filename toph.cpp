#include<bits/stdc++.h>
using namespace std;

#define mx 100005
#define LOG 22

int par[mx][LOG];
int cal[mx][LOG];
int depth[mx];
vector<pair<int,int>>g[mx];
int n;

void dfs(int u,int p,int lvl)
{
    par[u][0]=p;
    depth[u]=lvl;

    for(auto v:g[u])
    {
        if(v.first==p)
            continue;
        cal[v.first][0]=v.second;
        dfs(v.first,u,lvl+1);
    }
}

void init(int root)
{
    dfs(root,-1,1);

    for(int j=1; j<LOG; j++)
    {
        for(int i=1; i<=n; i++)
        {
            if(par[i][j-1]!=-1)
            {
                par[i][j]=par[par[i][j-1]][j-1];
                cal[i][j]=__gcd(cal[i][j-1],cal[par[i][j-1]][j-1]);
            }
            else
                par[i][j]=-1;
        }
    }
}

int query(int u,int cost)
{
    int diff=log2(depth[u]);

    for(int i=diff; i>=0; i--)
    {
        if(par[u][i]!=-1 && __gcd(cal[u][i],cost)==cost)
        {
            u=par[u][i];
        }
    }
    return u;
}


int main()
{
    int t;
    scanf("%d",&t);
    for(int ii=1; ii<=t; ii++)
    {
        for(int i=1; i<=n; i++)
        {
            g[i].clear();
            depth[i]=0;
        }
        memset(cal,0,sizeof cal);
        memset(par,0,sizeof par);
        scanf("%d",&n);

        for(int i=1; i<n; i++)
        {
            int x,y,w;
            scanf("%d%d%d",&x,&y,&w);
            g[x].push_back({y,w});
            g[y].push_back({x,w});
        }
        init(1);
        int q;
        scanf("%d",&q);
        printf("Case %d:\n",ii);
        while(q--)
        {
            int x,p;
            scanf("%d%d",&x,&p);
            printf("%d\n",query(x,p));
        }
    }

    return 0;
}
