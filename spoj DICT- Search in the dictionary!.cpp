#include<bits/stdc++.h>
using namespace std;

struct node
{
    map<int,node*>next;
    bool endmark;
    map<int,int>mp;
    node()
    {
        endmark=false;
        next.clear();
        mp.clear();

    }
}*root,*curr;

int n,q;
char ch[25005],ans[25];
bool f;
int qlen;

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
        }
        else curr->mp[s]+=1;

        curr=curr->next[s];
    }
    curr->endmark=true;
}

int cntword(char ch[],int len)
{
    int re=0;
    curr=root;
    for(int i=0;i<len;i++)
    {
        int s=ch[i]-'a';
        if(curr->mp[s]==0)
        {
            return -1;
        }
        curr=curr->next[s];
    }
    return re;
}

void print(node* tem,int len)
{
    if(tem->endmark==true && len>qlen)
    {
        f=true;
        ans[len]=0;
        puts(ans);
    }
    for(int i=0;i<26;i++)
    {
        if(tem->mp[i])
        {
            ans[len]='a'+i;
            print(tem->next[i],len+1);
        }
    }
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
    scanf("%d",&n);
    root=new node();
    for(int i=1;i<=n;i++)
    {
        scanf("%s",ch);
        insert(ch,strlen(ch));
    }
    scanf("%d",&q);
    for(int i=1;i<=q;i++)
    {
        char qq[25];
        scanf("%s",qq);
        int val=cntword(qq,strlen(qq));
        if(val==-1)
        {
            printf("Case #%d:\nNo match.\n",i);

        }
        else
        {
             strcpy(ans,qq);
             f=false;
             printf("Case #%d:\n",i);
             print(curr,qlen=strlen(ans));
             if(f==false)
             {
                  printf("No match.\n");
             }
        }
    }

    //del(root);///destroy trie

    return 0;
}
