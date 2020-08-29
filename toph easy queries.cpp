#include<bits/stdc++.h>
using namespace std;

///https://toph.co/p/easy-queries

#define mx 1000005
#define ll long long 

void IO()
{
     #ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
}

struct me
{
  int one=0;
  int zero=0;
  int re=0;
  int t_re=0;
};

int ar[mx];
char ch[mx];
int m,n,k,ii,dek;
me Tree[4*mx];
int Lazy[mx*4];

me convert(int bit)
{
    me z;
    if(bit==0)z.zero=1;
    else z.one=1;
    z.re=1;
    z.t_re=1;
    return z;
}

me Merge(me a, me b)
{
   me z;
   int tem0=a.zero+b.zero;
   int tem1=a.one+b.one;
   int val=max(a.re,b.re);
   val=max(val,tem0);
   val=max(val,tem1);
   val=max(val,a.zero+b.one);
   val=max(val,a.re+b.one);
   val=max(val,a.zero+b.re);
   z.zero=tem0;
   z.one=tem1;
   z.re=val;
   val=max(b.t_re,a.t_re);
   val=max(val,b.zero+a.one);
   val=max(val,b.zero+a.t_re);
   val=max(val,b.t_re+a.one);
   val=max(val,tem0);
   val=max(val,tem1);
   z.t_re=val;
   return z;
}

void build(int node,int be,int en)
{
  if(be==en)
  {
    Tree[node]=convert(ar[be]);
    return;
  }
  int mid=(be+en)/2;
  build(node*2,be,mid);
  build(node*2+1,mid+1,en);
  Tree[node]=Merge(Tree[node*2],Tree[node*2+1]);
}

void Relax(int node,int be,int en)
{
    me z;
    z.one=Tree[node].zero;
    z.zero=Tree[node].one;
    z.re=Tree[node].t_re;
    z.t_re=Tree[node].re;
    Tree[node]=z;
    if(be!=en)
    {
      Lazy[node*2]^=1;
      Lazy[node*2+1]^=1;
    }
    Lazy[node]=0;
}

void update(int node,int be,int en,int i,int j)
{
    if(Lazy[node])
    {
       Relax(node,be,en);
    }
    if(i>en || j<be)return;
    if(i<=be && j>=en)
    {
       Lazy[node]^=1;
       if(Lazy[node])Relax(node,be,en);
       return;
    }
    int mid=(be+en)/2;
    update(node*2,be,mid,i,j);
    update(node*2+1,mid+1,en,i,j);
    Tree[node]=Merge(Tree[node*2],Tree[node*2+1]);
}

void solve()
{
  
  scanf("%d%d%s",&n,&m,ch);
  for(int i=1;i<=n;i++)
  {
    ar[i]=ch[i-1]-'0';
  }
  build(1,1,n);
  while(m--)
  {
    char cc[10];
    int x,y;
    scanf("%s",cc);
    {
      if(cc[0]=='p')
      {
        printf("%d\n",Tree[1].re);
      }
      else
      {
        scanf("%d%d",&x,&y);
        update(1,1,n,x,y);

      }
    }
  }

}

int main()
{
    IO();
    int t=1;
   // scanf("%d",&t);
    while(t--)
    {
        solve();
    }
    return 0;
}
