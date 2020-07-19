#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define mx 10000005

bool is_composite[mx];
vector<int>prime;
int phi[mx],ii;
ll csum[mx];

void seive(int n)
{
    phi[1]=1;

    for(int i=2;i<=n;i++)
    {
        if(!is_composite[i])
        {
            prime.push_back(i);
            phi[i]=i-1;              ///i is prime
        }

        for(int j=0;j<prime.size() && i*prime[j]<=n;j++)
        {
            is_composite[i*prime[j]]=true;

            if(i%prime[j]==0)
            {
                phi[i*prime[j]]=phi[i]*prime[j];   ///prime[j] divides i
                break;
            }
            else
            {
                phi[i*prime[j]]=phi[i]*phi[prime[j]];  ///prime[j] do not divide i
            }
        }
    }
    for(int i=1;i<=n;i++)csum[i]=csum[i-1]+phi[i];
  //  for(int i=1;i<=12;i++)printf("%lld ",csum[i]);
}

void solve()
{
    int n;
    ll p;
     scanf("%d%lld",&n,&p);
     int re=-1;
     int lo=1,hi=n;
    // cout<<csum[n]<<endl;
     while(lo<=hi)
     {
         int mid=(lo+hi)/2;
         if(csum[mid]>=p)
         {
             re=mid;
             hi=mid-1;
         }
         else lo=mid+1;
     }
    // cout<<re<<endl;
     if(re!=-1)re=n/re;
        printf("Case %d: %d\n",++ii,re);
}

int main()
{
   //freopen("in.txt","r",stdin);
   //freopen("out.txt","w",stdout);
   int t=1;
   seive(mx-5);
   scanf("%d",&t);
   while(t--)solve();
   return 0;
}
