#include<bits/stdc++.h>
using namespace std;
//#pragma GCC optimize("Ofast")
//#pragma GCC target("avx,avx2,fma")
//#pragma GCC target ("avx2")
//#pragma GCC optimization ("O3")
//#pragma GCC optimization ("unroll-loops")
#define mx 100005
#define ll long long
#define mod 1000000009

ll ar[mx];
#define block 320
int kk_disce[block+5][mx],heavy[mx];
vector<int>v[mx],sovai[mx];
ll sum[block+5],update[block+5];

void solve()
{

    int n,m,q;
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++)scanf("%lld",&ar[i]);
    int heavy_num=0;
    for(int i=1;i<=m;i++)
    {
        int x;
        scanf("%d",&x);
        if(x>=block)heavy[i]=++heavy_num;
        for(int j=1;j<=x;j++)
        {
            int idx;
            scanf("%d",&idx);
            v[i].push_back(idx);
            sovai[idx].push_back(i);
            if(x>=block)
            {
                sum[heavy[i]]+=ar[idx];
            }
        }
    }

    for(int i=1;i<=m;i++)
    {
        if(heavy[i]==0)continue;
        for(auto it:v[i])
        {
            for(auto it1:sovai[it])
            {
                kk_disce[heavy[i]][it1]++;
            }
        }
    }
    while(q--)
    {
        char ti;
        int l,r;
        scanf(" %c%d",&ti,&l);
        if(ti=='?')
        {
            ll val=0;
            if(heavy[l])val+=sum[heavy[l]];
            else
            {
                for(auto it:v[l])val+=ar[it];
            }
            for(int i=1;i<=block;i++)
            {
                val+=kk_disce[i][l]*update[i];
            }

            printf("%lld\n",val);
        }
        else
        {
            scanf("%d",&r);
            if(heavy[l])update[heavy[l]]+=r;
            else
            {
            for(auto it:v[l])ar[it]+=r;
            for(int i=1;i<=block;i++)sum[i]+=1LL*kk_disce[i][l]*r;
            }
        }
    }

}

int main()
{
    int t=1;
    //scanf("%d",&t);
    while(t--)solve();
    return 0;
}
