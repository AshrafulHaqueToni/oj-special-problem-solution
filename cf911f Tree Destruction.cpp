#include<bits/stdc++.h>
using namespace std;

#define mx 200005
#define inf 1e7
vector<int>g[mx],dis_st,dis_en,tem,deg(mx,0);
int n,st,en;

int dfs(int u,vector<int>&dis)
{
    dis=vector<int>(n+1,inf);
    dis[u]=0;
    queue<int>q;
    q.push(u);
    while(!q.empty())
    {
        u=q.front();
        q.pop();
        for(auto v:g[u])
        {
            if(dis[v]==inf)
            {
                dis[v]=dis[u]+1;
                q.push(v);
            }
        }
        if(q.empty())return u;
    }
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        g[x].push_back(y);
        g[y].push_back(x);
        deg[x]++;
        deg[y]++;
    }
    st=dfs(1,tem);
    en=dfs(st,dis_st);
    dfs(en,dis_en);
    queue<int>q;
    for(int i=1;i<=n;i++)
    {
        if(deg[i]==1 && i!=st && en!=i)
        {
            q.push(i);
        }
    }
    vector<pair<int,int>>ans;
    long long re=0;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        if(dis_st[u]>=dis_en[u])
        {
            re+=dis_st[u];
            ans.push_back({u,st});
        }
        else
        {
            re+=dis_en[u];
            ans.push_back({u,en});
        }
        for(auto v:g[u])
        {
            deg[v]--;
            if(deg[v]==1 && v!=st && v!=en)
            {
                q.push(v);
            }
        }
    }
    q.push(st);
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        re+=dis_en[u];
        ans.push_back({u,en});
        for(auto v:g[u])
        {
            deg[v]--;
            if(deg[v]==1 && v!=st && v!=en)
            {
                q.push(v);
            }
        }
    }
    printf("%lld\n",re);
    for(auto it:ans)printf("%d %d %d\n",it.first,it.second,it.first);

    return 0;
}

