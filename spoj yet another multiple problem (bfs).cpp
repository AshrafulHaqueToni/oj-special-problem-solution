#include<bits/stdc++.h>
using namespace std;

#define mx 10005
#define ll long long 


vector<int>allowed;
int m,n,k,ii,dek;

void bfs()
{
	bool f=true;
	int par[mx][2];
    int visit[mx]={0};
	queue<int>q;
	for(int v:allowed)
	{
		if(!visit[v%n] && v!=0)
		{
			visit[v%n]=1;
			par[v%n][0]=-1;
			par[v%n][1]=v;
			q.push(v%n);
		}
	}
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int v:allowed)
		{
			int val=(u*10)+v;
			val%=n;
			//cout<<u<<" "<<v<<endl;
			if(!visit[val])
			{
				visit[val]=1;
                par[val][0]=u;
                par[val][1]=v;
                q.push(val);
			}
		}
		if(visit[0]==1)
		{
			string re;
			int p=0;
			while(p!=-1)
			{
				re+=par[p][1]+'0';
				p=par[p][0];
			}
			reverse(re.begin(),re.end());
			//cout<<re<<endl;
			printf("Case %d: %s\n",++ii,re.c_str() );
			f=false;
			break;
		}
	}
	if(f)printf("Case %d: -1\n", ++ii);
}

void solve()
{
	allowed.clear();
	int val[11]={0};
	for(int i=1;i<=k;i++)
	{
		int x;
		scanf("%d",&x);
		val[x]=1;
	}
	for(int i=0;i<=9;i++)
	{
		if(val[i]==0)allowed.push_back(i);
	}
	bfs();

}

int main()
{
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	#endif
	int t=1;
	//scanf("%d",&t);
	while(scanf("%d%d",&n,&k)!=EOF)
	{
		solve();
	}
	return 0;
}
