#include<bits/stdc++.h>
using namespace std;

#define mx 100005
#define N 1000000
#define ll long long
#define mod 1000000007

int ar[mx];
char ch[mx];
int spf[N+5];
int n,m,k,ii;
vector<pair<int,int>>Factor[N+5];
vector<int>st[mx],en[mx];
multiset<int>cnt[N+5];
int hi[N+5];
int ans[mx];

ll bigmod(ll e,ll x)
{
    if(!x)return 1;
    ll p=bigmod(e,x/2);
    p=(p*p)%mod;
    if(x%2)p=(p*e)%mod;
    return p;
}

void solve()
{
   scanf("%d%d",&n,&m);
   for(int i=1;i<=m;i++)
   {
       int x,y,z;
       scanf("%d%d%d",&x,&y,&z);
       st[x].push_back(z);
       en[y].push_back(z);
   }
   ll re=1;
   for(int i=1;i<=n;i++)
   {
       for(auto it:st[i])
       {
           for(auto it1:Factor[it])
           {
               if(hi[it1.first]<it1.second)
               {
                   re=(re*bigmod(bigmod(it1.first,hi[it1.first]),mod-2))%mod;
                   hi[it1.first]=it1.second;
                   re=(re*bigmod(it1.first,hi[it1.first]))%mod;
               }
               cnt[it1.first].insert(it1.second);
           }
       }
       ans[i]=re;
       for(auto it:en[i])
       {
           for(auto it1:Factor[it])
           {
               if(it1.second==hi[it1.first])
               {
                   re=(re*bigmod(bigmod(it1.first,hi[it1.first]),mod-2))%mod;
                   auto it2=cnt[it1.first].end();
                   it2--;
                   cnt[it1.first].erase(it2);
                   if(cnt[it1.first].size())
                   {
                    auto it3=cnt[it1.first].end();
                    it3--;
                   hi[it1.first]=*it3;
                   re=(re*bigmod(it1.first,*it3))%mod;
                   }
                   else
                   {
                       hi[it1.first]=0;
                   }
               }

               else
               {
                   cnt[it1.first].erase(cnt[it1.first].find(it1.second));
               }
           }
       }
       st[i].clear();
       en[i].clear();
   }
   printf("Case %d: ",++ii);
   for(int i=1;i<=n;i++)printf("%d%c",ans[i],(i==n)?'\n':' ');
   memset(hi,0,sizeof(hi));
}

void sieve()
{
    for(int i=1;i<=N;i++)spf[i]=i;
    for(int i=2;i<=N;i+=2)spf[i]=2;
    for(int i=3;i*i<=N;i+=2)
    {
        if(spf[i]==i)
        {
            for(int j=i*i;j<=N;j+=i)
            {
                if(spf[j]==j)spf[j]=i;
            }
        }
    }
    Factor[1].push_back({1,1});
    for(int i=2;i<=N;i++)
    {
        int val=i;
        while(val>1)
        {
            int pr=spf[val];
            int cnt=0;
            while(val%pr==0)cnt++,val/=pr;
            Factor[i].push_back({pr,cnt});
        }
    }
}

int main()
{
   //freopen("in.txt","r",stdin);
   //freopen("out.txt","w",stdout);
   sieve();
   int t=1;
   scanf("%d",&t);
   while(t--)solve();
   return 0;
}
