#include<bits/stdc++.h>
using namespace std;
#define mx 200005
#define mod 1000000007
#define N 1000000
#define ll long long
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

namespace MO
{
const int MAXN = 200005;
const int MAXQ = 200005;

int Sz;
int ar[MAXN];
int blkId[MAXN];
bool vis[MAXN];
int cnt[N];

struct Query
{
    int L,R,id;
    Query() {}
    Query(int x,int y,int i)
    {
        L=x;
        R=y;
        id=i;
    }
    bool operator<(const Query other) const
    {
        int a = blkId[L];
        int b = blkId[other.L];
        return a == b ? (a & 1 ? (R > other.R) : (R < other.R)) : a < b;
    }
} qry[MAXQ];
int perQ[MAXQ];

void Check(int pos)
{
    if(!vis[pos])
    {
        vis[pos]=1;
        re*=ar[pos];
        re%=mod;
        for(auto it:pf[pos])
        {
            cnt[it]++;
            if(cnt[it]==1)
            {
                plu*=it-1;
                plu%=mod;
                minu*=it;
                minu%=mod;
            }
        }
    }
    else
    {
        vis[pos]=0;
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
}
}
using namespace MO;

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
    for(int i=3; i*i<=x; i+=2)
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
    int n,Q;
    scanf("%d",&n);

    //Initiate Global
    Sz=sqrt(n);
    memset(vis,0,sizeof(vis));
    memset(cnt,0,sizeof(cnt));
    for(int i=0; i<=n; i++) blkId[i] = i/Sz;
    for(int i=1; i<=n; i++) scanf("%d",&ar[i]),for_pf(i);
    scanf("%d",&Q);
    for(int i=1; i<=Q; i++)
    {
        int l,r;
        scanf("%d %d",&l,&r);
        qry[i] = Query(l,r,i);
    }
    sort(qry+1,qry+Q+1);

    int left = qry[1].L;
    int right = left-1;

    for(int i=1; i<=Q; i++)
    {
        Query now = qry[i];
        while(left<now.L)  Check(left++);
        while(left>now.L)  Check(--left);
        while(right<now.R) Check(++right);
        while(right>now.R) Check(right--);
        perQ[now.id] = fina();
    }
    for(int i=1; i<=Q; i++)printf("%d\n",perQ[i]);

    return 0;
}
