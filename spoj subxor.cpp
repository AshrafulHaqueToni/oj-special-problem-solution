#include<bits/stdc++.h>
using namespace std;

#define ll long long

struct node
{
    node *child[2];
    int val[2];
    node()
    {
        child[0]=child[1]=NULL;
        val[0]=val[1]=0;
    }
}*root;
int t,n,k;

void insert(int xor_value)
{
    node *curr=root;
    for(int i=20;i>=0;i--)
    {
        bool chk=xor_value & (1<<i);
        curr->val[chk]++;
        if(curr->child[chk]==NULL)
            curr->child[chk]=new node();
        curr=curr->child[chk];
    }
}

int query(int xor_value)
{
    node *curr=root;
    int re=0;
    for(int i=20;i>=0;i--)
    {
        bool chk1=k & (1<<i);
        bool chk2=xor_value & (1<<i);

        if(chk1)
        {
            re+=curr->val[chk2];
           // cout<<re<<endl;
            if(curr->child[1-chk2]==NULL)return re;
            curr=curr->child[1-chk2];
        }
        else
        {
            //cout<<re<<endl;
            if(curr->child[chk2]==NULL)return re;
            curr=curr->child[chk2];
        }
    }

    return re;

}

void solve()
{
    scanf("%d%d",&n,&k);
    int xor_value=0;
    root=new node();
    insert(xor_value);
    ll re=0;
    for(int i=0;i<n;i++)
    {
        int x;
        scanf("%d",&x);
        xor_value^=x;
        re+=query(xor_value);
        insert(xor_value);
        //cout<<re<<endl;
    }
    printf("%lld\n",re);
}
int main()
{
    scanf("%d",&t);
    for(int i=1;i<=t;i++)solve();
    return 0;
}
