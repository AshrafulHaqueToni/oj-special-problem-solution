#include<bits/stdc++.h>
using namespace std;
//#pragma GCC optimize("Ofast")
//#pragma GCC target("avx,avx2,fma")
//#pragma GCC target ("avx2")
//#pragma GCC optimization ("O3")
//#pragma GCC optimization ("unroll-loops")
#define mx 100005
#define ll long long
#define mod 1000000007

deque<int>v[320];
int freq[320][mx];
int n,m,block;

void update(int st,int en)
{
    int st_bl=st/block;
    int en_bl=en/block;
    int last=v[en_bl][en%block];
    v[en_bl].erase(v[en_bl].begin()+(en%block));
    freq[en_bl][last]--;
    v[st_bl].insert(v[st_bl].begin()+(st%block),last);
    freq[st_bl][last]++;
    while(st_bl<en_bl)
    {
        int val=v[st_bl].back();
        v[st_bl].pop_back();
        freq[st_bl][val]--;
        st_bl++;
        v[st_bl].push_front(val);
        freq[st_bl][val]++;
    }
}

int query(int st,int en,int k)
{
    int st_bl=st/block;
    int en_bl=en/block;
    int re=0;
    if(st_bl==en_bl)
    {
        for(int i=st%block;i<=en%block;i++)re+=(v[st_bl][i]==k);
        return re;
    }
    for(int i=st%block;i<block;i++)re+=(v[st_bl][i]==k);
    for(int i=0;i<=en%block;i++)re+=(v[en_bl][i]==k);
    for(int i=st_bl+1;i<en_bl;i++)re+=freq[i][k];
    return re;
}

void solve()
{
  scanf("%d",&n);
  block=sqrt(n)+1;
  for(int i=0;i<n;i++)
  {
      int x;
      scanf("%d",&x);
      v[i/block].push_back(x);
      freq[i/block][x]++;
  }
  int q;
  int re=0;
  scanf("%d",&q);
  while(q--)
  {
      int ti,u,v;
      scanf("%d%d%d",&ti,&u,&v);

        u=(u+re-1)%n;
       v=(v+re-1)%n;

      if(v<u)swap(u,v);
      if(ti==1)
      {
          update(u,v);
      }
      else
      {
          int k;
          scanf("%d",&k);
          k=(k+re-1)%n+1;
          re=query(u,v,k);
          printf("%d\n",re);
      }
  }
}

int main()
{
    int t=1;
    while(t--)solve();
    return 0;
}
