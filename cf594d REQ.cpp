#include<bits/stdc++.h>
using namespace std;
//#pragma GCC optimize("Ofast")
//#pragma GCC target("avx,avx2,fma")
//#pragma GCC target ("avx2")
//#pragma GCC optimization ("O3")
//#pragma GCC optimization ("unroll-loops")
#define mx 200005
#define mod 1000000007
#define N 1000000
#define ll long long
int ar[mx],cnt[N+5],block;
vector<int>pf[mx];
ll re=1,ans[mx],minu=1,plu=1;

ll bigmod(ll e,ll x)
{
    if(!x)return 1;
    ll p=bigmod(e,x/2);
    p=(p*p)%mod;
    if(x%2)p=(p*e)%mod;
    return p;
}

struct me
{
    int l,r,idx,ld;
    bool operator < (const me &p) const {
        if(ld < p.ld) return true;
        else if(ld == p.ld) {
            if(ld&1) {
                if(r < p.r) return true;
                else return false;
            }
            else {
                if(r > p.r) return true;
                else return false;
            }
        }
        else return false;
    }
} tree[mx*4];


void Add(int pos)
{
    re*=ar[pos];
    re%=mod;
   // cout<<ar[pos]<<": ";
    for(auto it:pf[pos])
    {
        cnt[it]++;
       // cout<<it.first<<" ";
        if(cnt[it]==1)
        {
            plu*=it-1;
            plu%=mod;
            minu*=it;
            minu%=mod;
        }
    }
   // cout<<endl;
}

void Remove(int pos)
{
    minu*=ar[pos];
    minu%=mod;
    for(auto it:pf[pos])
    {
        cnt[it]--;
        if(cnt[it]==0)
        {
            plu*=it;
            plu%=mod;
            minu*=it-1;
            minu%=mod;
        }
    }
}

ll fina()
{
    ll tot=re*plu;
    tot%=mod;
    tot*=bigmod(minu,mod-2);
    return tot%mod;
}
void for_pf(int tem)
{
    int x=ar[tem];
    if(x%2==0)
    {
        pf[tem].push_back(2);
        while(x%2==0)x/=2;
    }
    for(int i=3;i*i<=x;i+=2)
    {
        if(x%i==0)
        {
            pf[tem].push_back(i);
            while(x%i==0)x/=i;
        }
    }
    if(x>1)pf[tem].push_back(x);
}
int main()
{
    int n;
    scanf("%d",&n);
    block=sqrt(n);
    for(int i=0; i<n; i++)
    {
        scanf("%d",ar+i);
        for_pf(i);
    }
    int q;
    scanf("%d",&q);

    for(int i=0; i<q; i++)
    {
        scanf("%d%d",&tree[i].l,&tree[i].r);
        tree[i].l--;
        tree[i].r--;
        tree[i].idx=i;
        tree[i].ld=tree[i].l/block;
    }
    sort(tree,tree+q);
    int cur_l=0,cur_r=0;
    for(int i=0; i<q; i++)
    {
        int l=tree[i].l,r=tree[i].r;
        while(cur_l>l)
            Add(--cur_l);
        while(cur_r<=r)
            Add(cur_r++);
        while(cur_l<l)
            Remove(cur_l++);
        while(cur_r>r+1)
            Remove(--cur_r);
        ans[tree[i].idx]=fina();
       // cout<<tree[i].idx<<endl;
    }
    for(int i=0; i<q; i++)
    {
        printf("%lld\n",ans[i]);
    }

    return 0;
}



