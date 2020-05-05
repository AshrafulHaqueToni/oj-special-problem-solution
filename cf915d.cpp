#include<bits/stdc++.h>
using namespace std;

#define mx 505
vector<int>g[mx];
vector<pair<int,int>>cycle;
int visit[mx],par[mx];
int n,m;
bool f;

void cycle_ace(int u)
{
    //cout<<u<<endl;
    visit[u]=1;
    for(auto v:g[u])
    {
        if(cycle.size())return;
        if(visit[v]==1)
        {
            int k=u;
            cycle.push_back({k,v});
            //cout<<par[3]<<endl;
            while(par[k]!=v)
            {
               // cout<<k<<endl;
                cycle.push_back({par[k],k});
                k=par[k];
            }
            cycle.push_back({v,k});
            return;
        }
        if(visit[v]==0)
        {
            par[v]=u;
           // cout<<v<<" "<<u<<endl;
            cycle_ace(v);
        }
    }
    visit[u]=2;
}

void cycle_without(int u,int x,int y)
{
    visit[u]=1;
    for(auto it:g[u])
    {
        if(u==x && y==it)continue;
        if(visit[it]==1)
        {
            f=true;
            return;
        }
        if(visit[it]==0)cycle_without(it,x,y);
    }
    visit[u]=2;
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        g[u].push_back(v);
    }
    for(int i=1;i<=n;i++)
    {
        if(visit[i]==0)
        {
            cycle_ace(i);
            if(cycle.size())break;
        }
    }
    if(cycle.empty())
    {
        printf("YES\n");
        return 0;
    }
    for(auto it:cycle)
    {
        int u=it.first;
        int v=it.second;
      //  cout<<u<<" "<<v<<endl;
        fill(visit,visit+n+1,0);
        f=false;
        for(int i=1;i<=n;i++)
        {
            if(visit[i]==0)
            {
                cycle_without(i,u,v);
                if(f)break;
            }
        }
        if(!f)
        {
             printf("YES\n");
        return 0;
        }
    }
    printf("NO\n");

    return 0;
}
