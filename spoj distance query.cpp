#include<bits/stdc++.h>
using namespace std;

#define LOG 17
#define mx 100005

int par[mx][LOG];
int depth[mx];
int min_val[mx][LOG];
int max_val[mx][LOG];
vector<pair<int,int>>g[mx];
int n;

void dfs(int u,int p,int lvl)
{
    depth[u]=lvl;
    par[u][0]=p;
    for(auto it:g[u])
    {
        int v=it.first;
        int w=it.second;
        if(p==v)continue;
        max_val[v][0]=w;
        min_val[v][0]=w;
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
                max_val[i][j]=max(max_val[i][j-1],max_val[par[i][j-1]][j-1]);
                min_val[i][j]=min(min_val[i][j-1],min_val[par[i][j-1]][j-1]);
            }
            else par[i][j]=-1;
        }
    }
}

pair<int,int> lca(int u,int v)
{
    if(u==v)return {0,0};

    if(depth[u]<depth[v])swap(u,v);
    int diff=depth[u]-depth[v];
    int choto=1000005,boro=0;
    for(int i=LOG-1;i>=0;i--)
    {
        if(diff>=(1<<i))
        {
            diff-=(1<<i);
            choto=min(choto,min_val[u][i]);
            boro=max(boro,max_val[u][i]);
            u=par[u][i];
        }
    }

    if(u==v)return {choto,boro};
    //cout<<choto<<" "<<boro<<endl;
    for(int i=LOG-1;i>=0;i--)
    {
        if(par[u][i]!=par[v][i])
        {
            choto=min({choto,min_val[u][i],min_val[v][i]});
            boro=max({boro,max_val[u][i],max_val[v][i]});
            u=par[u][i];
            v=par[v][i];
        }
    }
    choto=min({choto,min_val[u][0],min_val[v][0]});
    boro=max({boro,max_val[u][0],max_val[v][0]});

    return {choto,boro};
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        g[x].push_back({y,w});
        g[y].push_back({x,w});
    }
    memset(min_val,1000005,sizeof(min_val));
    init(1);
    int q;
    scanf("%d",&q);
    while(q--)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        pair<int,int>p=lca(x,y);
        printf("%d %d\n",p.first,p.second);
    }

    return 0;
}
