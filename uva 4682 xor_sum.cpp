#include<bits/stdc++.h>
using namespace std;

struct node
{
    int val;
    node* child[2];
    node()
    {
        child[0]=NULL;
        child[1]=NULL;
        val=0;
    }
}*root;

int n;

void insert(int val)
{
    node* curr=root;

    for(int i=31;i>=0;i--)
    {
        bool chk=val & (1<<i);
        if(curr->child[chk]==NULL)
        {
            curr->child[chk]=new node();
        }
        curr=curr->child[chk];
    }
    curr->val=val;
    //cout<<val<<endl;
}

int query(int val)
{
    node* curr=root;
    for(int i=31;i>=0;i--)
    {
        bool chk=val & (1<<i);
        if(curr->child[1-chk]!=NULL)
            curr=curr->child[1-chk];
        else if(curr->child[chk]!=NULL)
            curr=curr->child[chk];
    }
    //cout<<val<<endl;
    return val^(curr->val);
}

void del(node *curr)
{
    if(curr->child[0])del(curr->child[0]);
    if(curr->child[1])del(curr->child[1]);
    delete(curr);
}

void solve()
{
    scanf("%d",&n);
    root=new node();
    insert(0);
    int pre_xor=0;
    int re=INT_MIN;
    for(int i=0;i<n;i++)
    {
        int x;
        scanf("%d",&x);
        pre_xor^=x;
        insert(pre_xor);
        re=max(re,query(pre_xor));
    }
    printf("%d\n",re);
    del(root);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
