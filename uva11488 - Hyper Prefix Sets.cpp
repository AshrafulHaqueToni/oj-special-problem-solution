#include<bits/stdc++.h>
using namespace std;

#define ll long long

struct node
{
    node* next[2];
    bool endmark;
    ll mp[2];
    node()
    {
        endmark=false;
        for(int i=0; i<2; i++)
        {
            next[i]=NULL;
            mp[i]=0;
        }

    }
}*root;

int n;
char ch[50005][205];

void insert(char ch[],int len)
{
    node* curr=root;
    for(int i=0; i<len; i++)
    {
        int  s=ch[i]-'0';
        if(curr->next[s]==NULL)
        {
            curr->next[s]=new node();
            curr->mp[s]=1;
        }
        else
            curr->mp[s]+=1;

        curr=curr->next[s];

    }
    curr->endmark=true;
}

ll cntword(char ch[],int len)
{
    ll re=0;
    node* curr=root;
    for(int i=0; i<len; i++)
    {
        int s=ch[i]-'0';
        re=max(curr->mp[s]*(i+1),re);
        curr=curr->next[s];
    }
    return re;
}

void del(node* root)
{
    for(int i=0; i<2; i++)
    {
        if(root->next[i]!=NULL)
            del(root->next[i]);
    }
    delete(root);
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        root=new node();
        for(int i=1; i<=n; i++)
        {
            scanf("%s",ch[i]);
            insert(ch[i],strlen(ch[i]));
        }
        ll num=0;
        for(int i=1; i<=n; i++)
        {
            ll val=cntword(ch[i],strlen(ch[i]));
            num=max(num,val);
        }
        printf("%lld\n",num);

        del(root);///destroy trie
    }

    return 0;
}
