// Created by ash_98
 
#include<bits/stdc++.h>
using namespace std;
 
#define mx 100005
#define ll long long
#define mod 1000000007 //998244353
 
int ar[mx];
int n,m,ii,k;

int lp[10005];
vector<int>prime;
vector<int>factorize[10005];
int p_num[10005];
bitset<1230>dummy;


void sieve()
{
    for(int i=2;i<=10000;i++)
    {
        if(lp[i]==0)
        {
            prime.push_back(i);
            p_num[i]=++k;
            lp[i]=i;
        }
        for(int j=0;j<prime.size()&&prime[j]<=lp[i]&&i*prime[j]<=10000;j++)
            lp[i*prime[j]]=prime[j];
    }

    for(int i=2;i<=10000;i++)
    {
        int cur=i;
        while(cur>1)
        {
            int sp=lp[cur];
            int cnt=0;
            while(cur%sp==0)
            {
                cnt++;
                cur/=sp;
            }
            if(cnt&1)factorize[i].push_back(p_num[sp]);
        }
    }
   // cout<<k<<endl;
}

namespace Segment_Tree
{
    const int N=100005;
    bitset<1230>Tree[N*4];
   

    void init(int node,int be,int en)
    {
        Tree[node].reset();
        if(be==en)
        {
            for(int bit:factorize[ar[be]])Tree[node][bit]=1;
            return;
        }
        int mid=(be+en)/2;
        init(node*2,be,mid);
        init(node*2+1,mid+1,en);
        Tree[node]=Tree[node*2]^Tree[node*2+1];
    }

    void update(int node,int be,int en,int pos,int val)
    {
        if(be> pos || en<pos)return;
        if(be==en)
        {
            Tree[node].reset();
            for(int bit:factorize[val])Tree[node][bit]=1;
            return;
        }
        int mid=(be+en)/2;
        update(node*2,be,mid,pos,val);
        update(node*2+1,mid+1,en,pos,val);
        Tree[node]=Tree[node*2]^Tree[node*2+1];
    }

   
    bitset<1230>query(int node,int be,int en,int i,int j)
    {
        //Relax(node,be,en);
        if(be>j || en<i)return dummy;
        if(be>=i && en<=j)return Tree[node];
        int mid=(be+en)/2;
        return (query(node*2,be,mid,i,j)^query(node*2+1,mid+1,en,i,j));
    }
}

using namespace Segment_Tree;
 
void solve()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&ar[i]);
    init(1,1,n);
    printf("Case %d:\n",++ii);
    while(m--)
    {
        int x,y,ti;
        scanf("%d%d%d",&ti,&x,&y);
        if(ti==1)
        {
            if(query(1,1,n,x,y).count())
            {
                printf("NO\n");
            }
            else printf("YES\n");
        }
        else update(1,1,n,x,y);
    }

 
}
 
int main()
{
    int t=1;
    sieve();
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
