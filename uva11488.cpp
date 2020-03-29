///একটা ডিকশনারিতে অনেকগুলো শব্দ আছে। এখন কোনো একটা শব্দ কয়বার “prefix” হিসাবে এসেছে সেটা বের করতে হবে
#include<bits/stdc++.h>
using namespace std;

#define ll long long

struct node
{
    map<int,node*>next;
    bool endmark;
    map<int,ll>mp;
    node()
    {
        endmark=false;
        next.clear();
        mp.clear();

    }
}*root;

int n;
char ch[50005][205];

void insert(char ch[],int len)
{
    node* curr=root;
    for(int i=0;i<len;i++)
    {
        int  s=ch[i]-'a';
        if(curr->next.find(s)==curr->next.end())
        {
            curr->next[s]=new node();
            curr->mp[s]=1;
           // cout<<ch[i]<<endl;
        }
        else curr->mp[s]+=1;

        curr=curr->next[s];

        //cout<<curr->mp[s]<<endl;
    }
    curr->endmark=true;
}

ll cntword(char ch[],int len)
{
    ll re=0;
    node* curr=root;
    for(int i=0;i<len;i++)
    {
        int s=ch[i]-'a';
        //cout<<curr->mp[s]<<endl;
        if(curr->next.find(s)==curr->next.end())
        {
            return 0;
        }
        re=max(curr->mp[s]*(i+1),re);
        curr=curr->next[s];
    }
    return re;
}

void del(node* root)
{
    for(int i=0;i<26;i++)
    {
        if(root->next.find(i)!=root->next.end())del(root->next[i]);
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
    for(int i=1;i<=n;i++)
    {
        scanf("%s",ch[i]);
        insert(ch[i],strlen(ch[i]));
    }
    ll num=0;
    for(int i=1;i<=n;i++)
    {
        ll val=cntword(ch[i],strlen(ch[i]));
        //cout<<val<<endl;
        num=max(num,val);
    }
    printf("%lld\n",num);

    del(root);///destroy trie
    }

    return 0;
}
