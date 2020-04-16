#include<bits/stdc++.h>
using namespace std;

#define mx 100005
vector<pair<int,int>>g[mx];
int n,edge,k;
int ar[mx];
vector<int>dis;
vector<bool>vis;

int min_distance()
{
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater< pair<int,int> > >pq;

    int re=INT_MAX;
    for(int i=1; i<=n; i++)
    {
        if(ar[i]==0)
            continue;

        dis.assign(n+3,INT_MAX);
        vis.assign(n+3,false);

        while(!pq.empty())
            pq.pop();

        dis[i]=0;
        pq.push({0,i});

        int good=0;
        while(!pq.empty())
        {
            int u=pq.top().second;
            pq.pop();

            if(vis[u])
                continue;

            vis[u]=true;

            good+=ar[u];

            if(dis[u]>re)
                break;

            if(good==3 && ar[u]==1)
            {
                re=min(re,dis[u]);
                break;
            }
            for(auto it:g[u])
            {
                int v=it.first;
                int w=it.second;
                if(dis[u]+w<dis[v])
                {
                    dis[v]=dis[u]+w;
                    pq.push({dis[v],v});
                }

            }
        }

    }

    return re;
}

int main()
{
    scanf("%d%d%d",&n,&edge,&k);

    for(int i=1; i<=k; i++)
    {
        int x;
        scanf("%d",&x);
        ar[x]=1;
    }

    for(int i=0; i<edge; i++)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        g[x].push_back({y,w});
        g[y].push_back({x,w});
    }
    printf("%d\n",min_distance());
    return 0;
}
