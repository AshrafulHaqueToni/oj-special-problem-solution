// Created by ash_98
 
#include<bits/stdc++.h>
using namespace std;
 
#define mx 100005
#define ll long long
#define mod 998244353
#define base 173

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll my_rand(ll l, ll r) {
    return uniform_int_distribution<ll>(l, r)(rng);
}

 
int P[mx],ar[mx];
int n,m,ii,k;

int add(int a,int b)
{
    a+=b;
    if(a>=mod)a-=mod;
    return a;
}
int sub(int a,int b)
{
    a-=b;
    if(a<0)a+=mod;
    return a;
}
int mul(int a,int b)
{
    ll re=a;
    re*=b;
    if(re>=mod)re%=mod;
    return re;
}

struct SegmentTree
{
    pair<int,int>Tree[mx*4];

    pair<int,int>Merge(int lft,int rgt){
        return {add(mul(Tree[lft].first,P[Tree[rgt].second]),
            Tree[rgt].first),Tree[lft].second+Tree[rgt].second};
    }

    void init(int node,int be,int en,int op){
        if(be==en){
            if(op==1){
                Tree[node]={ar[be],1};
            }
            else Tree[node]={ar[n-be+1],1};
            return;
        }
        int mid=(be+en)/2;
        init(node*2,be,mid,op);
        init(node*2+1,mid+1,en,op);
        Tree[node]=Merge(node*2,node*2+1);
    }

    void update(int node,int be,int en,int pos,int val){
        if(be==en){
            Tree[node]={val,1};
            return;
        }
        int mid=(be+en)/2;
        if(pos<=mid)update(node*2,be,mid,pos,val);
        else update(node*2+1,mid+1,en,pos,val);
        Tree[node]=Merge(node*2,node*2+1);
    }

    pair<int,int>query(int node,int be,int en,int i,int j){
        if(be>=i and en<=j)return Tree[node];
        int mid=(be+en)/2;
        if(j<=mid)return query(node*2,be,mid,i,j);
        else if(i>mid){
            return query(node*2+1,mid+1,en,i,j);
        }
        else{
            pair<int,int>a=query(node*2,be,mid,i,j);
            pair<int,int>b=query(node*2+1,mid+1,en,i,j);

            return {add(mul(a.first,P[b.second]),b.first),a.second+b.second};
        }
        return {0,0};
    }
    
};

SegmentTree st1,st2;

int Size[mx],par[mx];
set<int>s[mx];
int Findparent(int x)
{
    return (x==par[x])?x:(par[x]=Findparent(par[x]));
}

void Union(int x,int y)
{
    int px=Findparent(x);
    int py=Findparent(y);
    if(px==py)return;

    if(Size[px]<Size[py])
    {
        swap(px,py);
    }
    Size[px]+=py;
    par[py]=px;
    for(int val:s[py]){
        s[px].insert(val);
        st1.update(1,1,n,val,ar[px]);
        st2.update(1,1,n,n-val+1,ar[px]);

    }
}

void initialize()
{
    for(int i=0;i<=n;i++)par[i]=i,Size[i]=1,s[i].insert(i);
}


void p_update(int l,int r){
    int be=1,en=(r-l+1)/2;
    int got=0;
   // cout<<l<<" "<<r<<endl;
    while(be<=en){
        int mid=(be+en+1)/2;
      //  cout<<l<<" "<<l+mid-1<<endl;
        assert(l<=n and l+mid-1<=n);

        assert(l>0 and l+mid-1>0);
        pair<int,int>a=st1.query(1,1,n,l,l+mid-1);
        int L=r-mid+1;
        int R=r;
        assert(n-R+1<=n and n-L+1<=n);
        assert(n-R+1>0 and n-L+1>0);
        pair<int,int>b=st2.query(1,1,n,n-R+1,n-L+1);
        if(a.first==b.first){
            got=mid;
            be=mid+1;
        }
        else en=mid-1;
    }
   // cout<<l<<" "<<r<<" "<<got<<endl;
    if(got==(r-l+1)){
        return;
    }
    Union(l+got,r-got);
    if(l+got+1<r-got-1){
        p_update(l+got+1,r-got-1);
    }
}
 
void solve()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        ar[i]=my_rand(1,1e18)%mod;
    }
    P[0]=1;
    for(int i=1;i<=n;i++)P[i]=mul(P[i-1],base);

    initialize();
    st1.init(1,1,n,1);
    st2.init(1,1,n,2);


    while(m--){
        int ti;
        scanf("%d",&ti);
        if(ti==1){
            int l,r;
            scanf("%d%d",&l,&r);
            if(l==r)continue;
            p_update(l,r);
        }
        else{
            int a,b,x,y;
            scanf("%d%d%d%d",&a,&b,&x,&y);
            if((b-a)!=(y-x)){
                printf("Not equal\n");
                continue;
            }
            if(st1.query(1,1,n,a,b)==st1.query(1,1,n,x,y)){
                printf("Equal\n");
            }
            else printf("Unknown\n");
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
