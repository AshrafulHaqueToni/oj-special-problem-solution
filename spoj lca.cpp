#include<bits/stdc++.h>
using namespace std;

#define mx 1005
#define LOG 22

int par[mx][LOG];
int depth[mx];
int n;

void init()
{
    for(int j=1; j<LOG; j++)
    {
        for(int i=1; i<=n; i++)
        {
            if(par[i][j-1]!=-1)
            {
                par[i][j]=par[par[i][j-1]][j-1];
            }
            else
                par[i][j]=-1;
        }
    }
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


int main()
{
    int t;
    scanf("%d",&t);
    for(int ii=1; ii<=t; ii++)
    {
        for(int i=1; i<=n; i++)
        {
            depth[i]=0;
        }
        memset(par,0,sizeof par);

        scanf("%d",&n);

        par[1][0]=-1;

        for(int i=1; i<=n; i++)
        {
            int x;
            scanf("%d",&x);
            while(x--)
            {
             int y;
             scanf("%d",&y);
             par[y][0]=i;
             depth[y]=depth[i]+1;
            }
        }
        init();
        int q;
        scanf("%d",&q);
        printf("Case %d:\n",ii);
        while(q--)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            printf("%d\n",lca(x,y));
        }

    }

    return 0;
}
