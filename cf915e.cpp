///Dynamic Segment tree
///only build when u need it
/// if left and right child not created , create  by  giving then new inndex
/// k=2 means all value from l,r will be one
/// k=1 means all value from l,r will be zero
#include<bits/stdc++.h>
using namespace std;

#define mx 18000005 /// n=10^9

struct me
{
    int left,right,val;
    me()
    {
        left=0;
        right=0;
        val=0;
    }
};

me tree[mx];
short lazy[mx];
int n,q,idx=1;

void propagate(int node,int be,int en)
{
    if(lazy[node]==0)return;
    if(tree[node].left==0)tree[node].left=idx++;
    if(tree[node].right==0)tree[node].right=idx++;
    if(be!=en)
    {
        lazy[tree[node].left]=lazy[node];
        lazy[tree[node].right]=lazy[node];
    }
    if(lazy[node]==2)
    {
        tree[node].val=en-be+1;
    }
    else tree[node].val=0;
    lazy[node]=0;
}

void update(int node,int be,int en,int i,int j,int k)
{
    if(lazy[node])
    {
        if(lazy[node]==1)tree[node].val=0;
        else tree[node].val=en-be+1;
    }
    if(i>en || j<be)return;
    if(i<=be && en<=j)
    {
        lazy[node]=k;
        propagate(node,be,en);
        return;
    }
    propagate(node,be,en);
    int mid=(be+en)/2;
    if(tree[node].left==0)tree[node].left=idx++;
    if(tree[node].right==0)tree[node].right=idx++;
    update(tree[node].left,be,mid,i,j,k);
    update(tree[node].right,mid+1,en,i,j,k);
    tree[node].val=tree[tree[node].left].val+tree[tree[node].right].val;
}

int main()
{
    scanf("%d%d",&n,&q);
    update(0,1,n,1,n,2);
    while(q--)
    {
        int l,r,k;
        scanf("%d%d%d",&l,&r,&k);
        update(0,1,n,l,r,k);
        printf("%d\n",tree[0].val);
    }

    return 0;
}
