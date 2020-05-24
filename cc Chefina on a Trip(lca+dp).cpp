#include<bits/stdc++.h>
using namespace std;

#define mx 100005

int par[mx][25];
int depth[mx],choto[mx],boro[mx],ar[mx];
vector<int>g[mx];
int n,LOG,q;
char re[mx];

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


int kth_parent(int u,int k)
{
    for(int i=LOG-1;i>=0;i--)
    {
        if(k>=(1<<i))
        {
            k-=(1<<i);
            u=par[u][i];
        }
        if(u==-1)return u;
    }
    return u;
}
void dfs_for_choto(int u,int p)
{
    for(auto it:g[u])
    {
        if(it==p)continue;
        if(ar[it]>ar[u])choto[it]=choto[u]+1;
        else choto[it]=1;
        dfs_for_choto(it,u);
    }
}
void dfs_for_boro(int u,int p)
{
    for(auto it:g[u])
    {
        if(it==p)continue;
        if(ar[it]<ar[u])boro[it]=boro[u]+1;
        else boro[it]=1;
        dfs_for_boro(it,u);
    }
}
void solve()
{
    scanf("%d%d",&n,&q);
    LOG=log2(n)+1;
    for(int i=1;i<n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    for(int i=1;i<=n;i++)scanf("%d",&ar[i]);
    choto[1]=1;
    boro[1]=1;
    dfs_for_choto(1,-1);
    dfs_for_boro(1,-1);
//    for(int i=1;i<=n;i++)
//    {
//        cout<<"choto-boro "<<choto[i]<<" "<<boro[i]<<endl;
//    }
    init(1);
    int pos=0;
    while(q--)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(x==y)
        {
            re[pos++]='1';
            continue;
        }
        int p=lca(x,y);
       // cout<<p<<endl;
        int a=kth_parent(x,boro[x]-1); /// x er cheye sovar boror jonno
        int b=kth_parent(y,boro[y]-1);

        if(depth[a]<=depth[p])a=p;
        if(depth[b]<=depth[p])b=p;
       // cout<<a<<" "<<b<<endl;
        if(a==b)
        {
            re[pos++]='1';
            continue;
        }
        if(a!=p && b!=p)
        {
            re[pos++]='0';
            continue;
        }
        if(a!=p)
        {
            if(ar[a]==ar[par[a][0]])
            {
                re[pos++]='0';
                continue;
            }
            int aa=kth_parent(a,choto[a]-1);
            if(depth[aa]<=depth[p])
            {
                re[pos++]='1';
                continue;
            }
            re[pos++]='0';

        }
         if(b!=p)
        {
            if(ar[b]==ar[par[b][0]])
            {
                re[pos++]='0';
                continue;
            }
            int bb=kth_parent(b,choto[b]-1);
            if(depth[bb]<=depth[p])
            {
                re[pos++]='1';
                continue;
            }
            re[pos++]='0';
        }

    }

    for(int i=1;i<=n;i++)
    {
       // printf("%c",re[i-1]);
        choto[i]=0;
        boro[i]=0;
        g[i].clear();
       // for(int j=0;j<LOG;j++)par[i][j]=0;
    }
    for(int i=0;i<pos;i++)printf("%c",re[i]);
    printf("\n");

}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
