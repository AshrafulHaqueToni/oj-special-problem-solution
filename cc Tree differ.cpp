#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mx 200005

int ar[mx];
vector<int> g[mx];
int par[mx][25];
int depth[mx];
int n,m,q,LOG;


void dfs(int u,int p,int lvl)
{
    par[u][0]=p;
    depth[u]=lvl;

    for(auto v:g[u])
    {
        if(v==p)continue;
        dfs(v,u,lvl+1);
    }
}

void init()
{
    dfs(1,-1,1);

    for(int j=1;j<LOG;j++)
    {
        for(int i=1;i<=n;i++)
        {
            if(par[i][j-1]!=-1)
            {
                par[i][j]=par[par[i][j-1]][j-1];

            }
            else par[i][j]=-1;
        }
    }
}

int lca(int u,int v)
{
    if(depth[u]<depth[v])swap(u,v);
    int log=1;
    while(1)
    {
        int next=log+1;
        if(depth[u]<(1<<next))break;
        log++;
    }

    for(int i=log;i>=0;i--)
    {
        if(depth[u]-(1<<i)>=depth[v])
        {
            u=par[u][i];
        }
    }
    if(u==v)return u;

    for(int i=log;i>=0;i--)
    {
        if(par[u][i]!=-1 && par[u][i]!=par[v][i])
        {
            u=par[u][i];
            v=par[v][i];
        }
    }
    return par[v][0];
}

int dist(int u,int v)
{
    return depth[u]+depth[v]-2*depth[lca(u,v)];
}

int last_cal(vector<int>tem)
{
    int re=102;
    int sz=tem.size();
    sort(tem.begin(),tem.end());
    for(int i=1;i<sz;i++)
    {
        re=min(re,tem[i]-tem[i-1]);
    }
    return re;
}

void solve()
{
   scanf("%d%d",&n,&q);
   LOG=log2(n);
   LOG++;
   for(int i=1;i<=n;i++)
   {
    scanf("%d",&ar[i]);
   }
   for(int i=1;i<n;i++)
   {
    int x,y;
    scanf("%d%d",&x,&y);
    g[x].push_back(y);
    g[y].push_back(x);
   }
   init();
   while(q--)
   {
    int x,y;
    scanf("%d%d",&x,&y);
    if(dist(x,y)>=100)
    printf("0\n");
    else
    {
      vector<int>path;
     while(x!=y)
     {
         if(depth[x]>depth[y])
         {
             path.push_back(ar[x]);
             x=par[x][0];
         }
         else
         {
             path.push_back(ar[y]);
             y=par[y][0];
         }
     }
     path.push_back(ar[x]);

    printf("%d\n",last_cal(path) );
    }
   }

   for(int i=1;i<=n;i++)
   {
    g[i].clear();
   }
}
int main()
{
//#ifndef ONLINE_JUDGE
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
//#endif
    int t=1;
    scanf("%d",&t);
    while(t--)
    {
        solve();
    }
   return 0;
}
