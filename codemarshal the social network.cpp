#include<bits/stdc++.h>
using namespace std;

#define mx 100005
#define ll long long

#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp>
using    namespace __gnu_pbds;

typedef tree<
pair<int, int>,
null_type,
less<pair<int, int>>,
rb_tree_tag,
tree_order_statistics_node_update> ordered_set;

//  how many numbers are smaller than a given value(7)
//    cout << os.order_of_key(7);


ordered_set os[mx];
int par[mx];
int n,m,k,ii;

int Findparent(int x)
{
    return (x==par[x])?x:(par[x]=Findparent(par[x]));
}

void solve()
{
   scanf("%d%d",&n,&m);
   for(int i=1;i<=n;i++)par[i]=i;
   k=1;
   printf("Case %d:\n",++ii);
   while(m--)
   {
       int ti;
       scanf("%d",&ti);
       if(ti==2)
       {
           int x,l,r;
           scanf("%d%d%d",&x,&l,&r);
           x=Findparent(x);
           int up=os[x].order_of_key({r,k});
           int lo=os[x].order_of_key({l,0});
           printf("%d\n",up-lo);
       }
       else if(ti==1)
       {
           int x,y;
           scanf("%d%d",&x,&y);
           x=Findparent(x);
           os[x].insert({y,k++});
       }
       else
       {
           int x,y;
           scanf("%d%d",&x,&y);
           int xx=Findparent(x);
           int yy=Findparent(y);
           if(os[xx].size()<os[yy].size())
           {
               par[xx]=yy;
               for(auto it:os[xx])os[yy].insert(it);
           }
           else
           {
               par[yy]=xx;
               for(auto it:os[yy])os[xx].insert(it);
           }


       }
   }

//   for(int i=1;i<=n;i++)
//   {
//       cout<<i<<endl;
//       int x=Findparent(i);
//       for(auto it:os[x])cout<<it.first<<" "<<it.second<<endl;
//       cout<<endl;
//      // os[i].clear();
//   }
   for(int i=1;i<=n;i++)os[i].clear();
}

int main()
{
   //freopen("in.txt","r",stdin);
   //freopen("out.txt","w",stdout);
   int t=1;
   scanf("%d",&t);
   while(t--)solve();
   return 0;
}
