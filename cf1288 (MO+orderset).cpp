#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define orderset tree< int, null_type, less<int>, rb_tree_tag , tree_order_statistics_node_update>

#define mx 300005

int block;
int n,m;
int mi[mx],ma[mx],last[mx],freq[mx],cnt,ar[mx];
bool visit[mx];

struct node
{
    int x,y,idx;
    node(int x,int y,int idx)
    {
        this->x=x;
        this->y=y;
        this->idx=idx;
    }
    bool operator<(const node& other)const
    {
        if(x/block<other.x/block)return true;             ///condition
        else if(x/block==other.x/block)return y<other.y;
        return false;
    }
    ///sort korte chaile vector<node>v niye sort korte hobe.sort(v.begin(),v.end())
    /// push korte v.push_back(node(parameter....)
};

void check(int pos)
{
    int val=ar[pos];
    if(!visit[pos])
    {
        visit[pos]=true;
        freq[val]++;
        if(freq[val]==1)cnt++;
    }
    else
    {
        visit[pos]=false;
        freq[val]--;
        if(freq[val]==0)cnt--;
    }

}
vector<node>q;

int main()
{
    scanf("%d%d",&n,&m);
    block=sqrt(n)+1;
    for(int i=1;i<=n;i++)mi[i]=ma[i]=i;
    orderset os;
    for(int i=1;i<=m;i++)
    {
        int x;
        scanf("%d",&x);
        ar[i]=x;
        mi[x]=1;
        os.insert(x);
        if(!last[x])
        {
            int samne_boro=os.size()-os.order_of_key(x+1);
            ma[x]=x+samne_boro;
        }
        else
        {
            q.push_back(node(last[x],i,x));
        }
        last[x]=i;
    }
    for(int i=1;i<=n;i++)
    {
        if(!last[i])
        {
            int samne_boro=os.size()-os.order_of_key(i+1);
            ma[i]=i+samne_boro;
        }
        else
        {
             q.push_back(node(last[i],m,i));
        }
    }
    sort(q.begin(),q.end());
   // cout<<"aci\n";
    if(!q.empty())
    {
        int left=q[0].x;
        int right=left-1;
        for(auto it:q)
        {
           // cout<<it.idx<<endl;
            while(left<it.x)check(left++);
           // cout<<"aci\n";
            while(left>it.x)check(--left);
           // cout<<"aci\n";
            while(right<it.y)check(++right);
            //cout<<"aci\n";
            while(right>it.y)check(right--);
          //  cout<<it.idx<<" "<<cnt<<endl;
            ma[it.idx]=max(ma[it.idx],cnt);
        }
    }
   // cout<<endl;
    for(int i=1;i<=n;i++)
    {
        printf("%d %d\n",mi[i],ma[i]);
    }

    return 0;
}
