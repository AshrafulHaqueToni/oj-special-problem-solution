#include<bits/stdc++.h>
using namespace std;

#define mx 10005
#define LOG 22
#define pii pair<int,int>

int par[mx][LOG];
int dis[mx][LOG];
int depth[mx];

vector<pair<int,int>>g[mx];
int n,val;

void dfs(int u,int p,int lvl)
{
    par[u][0]=p;
    depth[u]=lvl;

    for(auto it:g[u])
    {
        int v=it.first;
        if(v==p)
            continue;
        dis[v][0]=it.second;
        dfs(v,u,lvl+1);
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
                dis[i][j]=dis[i][j-1]+dis[par[i][j-1]][j-1];
            }
            else
                par[i][j]=-1;
        }
    }
}

int lca_dis(int u,int v)
{
    if(depth[u]<depth[v])
        swap(u,v);
    int diff=depth[u]-depth[v];
    int val=0;

    for(int i=LOG-1; i>=0; i--)
    {
        if(diff>=(1<<i))
        {
            diff-=(1<<i);
            val+=dis[u][i];
            u=par[u][i];
        }
    }
    if(u==v)
        return val;

    for(int i=LOG-1; i>=0; i--)
    {
        if(par[u][i]!=par[v][i])
        {
            val+=dis[u][i];
            val+=dis[v][i];
            u=par[u][i];
            v=par[v][i];
        }

    }

    val+=dis[u][0];
    val+=dis[v][0];

    return val;
}

int lca(int u,int v)
{
    if(depth[u]<depth[v])
        swap(u,v);
    int diff=depth[u]-depth[v];

    for(int i=LOG-1; i>=0; i--)
    {
        if(diff>=(1<<i))
        {
            diff-=(1<<i);
            u=par[u][i];
        }
    }
    if(u==v)
        return u;

    for(int i=LOG-1; i>=0; i--)
    {
        if(par[u][i]!=par[v][i])
        {
            u=par[u][i];
            v=par[v][i];
        }
    }
    return par[u][0];
}

int dist(int u,int v)
{
    return depth[u]+depth[v]-2*depth[lca(u,v)];
}

int kth_parent(int u,int k)
{
    for(int i=LOG-1; i>=0; i--)
    {
        if(k>=(1<<i))
        {
            k-=(1<<i);
            u=par[u][i];
        }
        if(u==-1)
            return u;
    }
    return u;
}

int main()
{
    int t;
    scanf("%d",&t);
    for(int ii=1; ii<=t; ii++)
    {
        for(int i=1;i<=n;i++)g[i].clear();
        memset(par,0,sizeof par);
        memset(depth,0,sizeof depth);
        memset(dis,0,sizeof dis);
        scanf("%d",&n);

        for(int i=1; i<n; i++)
        {
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            g[x].push_back({y,z});
            g[y].push_back({x,z});
        }
        init(1);
        while(1)
        {
            // char ch[10];
            string ch;
            cin>>ch;
            if(ch=="DONE")
                break;
            int x,y;
            scanf("%d%d",&x,&y);
            if(ch=="DIST")
            {
                printf("%d\n",lca_dis(x,y));
            }
            else
            {
                int z;
                scanf("%d",&z);
                z--;
                int p=lca(x,y);
                int pa=dist(x,p);
                if(pa>=z)
                {
                    printf("%d\n",kth_parent(x,z));
                }
                else
                {
                    int tem=dist(p,y);
                    z-=pa;
                    printf("%d\n",kth_parent(y,tem-z));

                }
            }
        }
        printf("\n");
    }


    return 0;
}
