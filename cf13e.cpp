#include<bits/stdc++.h>
using namespace std;

#define mx 100005
int n,m,block;
int ar[mx],choto_jump[mx],boro_lav[mx],jump_cost[mx];
void cal_jump(int cur)
{
    int left=(cur/block)*block;
    int right=min(n,left+block);
   // left+=cur%block;
   // cout<<left+block<<" "<<left<<" "<<right<<endl;
    for(int i=right-1;i>=left;i--)
    {

        if(choto_jump[i]>=right)
        {
            boro_lav[i]=choto_jump[i];
            jump_cost[i]=1;
        }
        else
        {
            jump_cost[i]=jump_cost[choto_jump[i]]+1;
            boro_lav[i]=boro_lav[choto_jump[i]];
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    block=sqrt(n)+1;
    for(int i=0;i<n;i++)
    {
        scanf("%d",&ar[i]);
        choto_jump[i]=min(n,ar[i]+i);
    }
    for(int i=0;i<n;i++)
    cal_jump(i);//cout<<choto_jump[i]<<endl;
    while(m--)
    {
        int u,v,ti;
        scanf("%d%d",&ti,&u);
        u--;
        int re=1;
        if(ti==1)
        {
            while(boro_lav[u]<n)
            {
               // cout<<u<<endl;
                re+=jump_cost[u];
                u=boro_lav[u];
            }
            while(choto_jump[u]<n)
            {
                re++;
                u=choto_jump[u];
            }
            printf("%d %d\n",u+1,re);
        }
        else
        {
            scanf("%d",&v);
            choto_jump[u]=u+v;
            cal_jump(u);
        }
    }
    return 0;
}
