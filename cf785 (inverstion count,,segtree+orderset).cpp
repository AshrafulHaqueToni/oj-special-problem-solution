#include<bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC target("avx,avx2,fma")
//#pragma GCC target ("avx2")
//#pragma GCC optimization ("O3")
//#pragma GCC optimization ("unroll-loops")
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/Tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define orderset tree< int, null_type, less<int>, rb_tree_tag , tree_order_statistics_node_update>

#define mx 200005
#define ll long long

orderset Tree[mx*4];
int ar[mx];
ll re;

void build(int node,int be,int en)
{
    for(int i=be;i<=en;i++)
    {
        Tree[node].insert(ar[i]);
    }
    if(be==en)return;
    int mid=(be+en)/2;
    build(node*2,be,mid);
    build(node*2+1,mid+1,en);
}

void update(int node,int be,int en,int i,int j)
{
    bool aci_i=(be<=i && i<=en);
    bool aci_j=(be<=j && en>=j);

    if(aci_j && aci_i)
    {
        ///no_change for this range;
    }
    else if(aci_j)
    {
        Tree[node].erase(ar[j]);
        Tree[node].insert(ar[i]);
    }
    else if(aci_i)
    {
        Tree[node].erase(ar[i]);
        Tree[node].insert(ar[j]);
    }
    else
    {
        /// i r j jehetu range ye nai tai subTree te r jabo na
        return;
    }
    if(be==en)return;
    int mid=(be+en)/2;
    update(node*2,be,mid,i,j);
    update(node*2+1,mid+1,en,i,j);
}

ll max_count(int node,int be,int en,int i,int j,int val)
{
    if(be>j || en <i || be>en)return 0;
    if(be>=i && en<=j)
    {
        return Tree[node].size()-Tree[node].order_of_key(val+1);
    }
    int mid=(be+en)/2;
    return max_count(node*2,be,mid,i,j,val)+max_count(node*2+1,mid+1,en,i,j,val);
}
ll min_count(int node,int be,int en,int i,int j,int val)
{
    if(be>j || en <i || be>en)return 0;
    if(be>=i && en<=j)
    {
        return Tree[node].order_of_key(val);
    }
    int mid=(be+en)/2;
    return min_count(node*2,be,mid,i,j,val)+min_count(node*2+1,mid+1,en,i,j,val);
}

int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)ar[i]=i;
    build(1,1,n);
    while(q--)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        if(l!=r)
        {
            if(l>r)swap(l,r);
            re-=max_count(1,1,n,l+1,r-1,ar[r]);
            re+=max_count(1,1,n,l+1,r-1,ar[l]);
            re+=min_count(1,1,n,l+1,r-1,ar[r]);
            re-=min_count(1,1,n,l+1,r-1,ar[l]);
            if(ar[r]>ar[l])re++;
            else re--;
            update(1,1,n,l,r);
            swap(ar[l],ar[r]);
        }
        printf("%lld\n",re);
    }

    return 0;
}
