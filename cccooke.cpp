#include <bits/stdc++.h>
using namespace std;

#define intt long long

struct Node
{
    intt sum;
    intt prefix;
    intt suffix;
};

Node tree[4 * 100000];
intt a[100005];
intt n,x,ty,ans;


void build(intt a[], intt index, intt beg, intt end)
{
    if (beg == end)
    {
        tree[index].sum = a[beg];
        tree[index].prefix = a[beg];
        tree[index].suffix=a[beg];
    }
    else
    {
        intt mid = (beg + end) / 2;
        build(a, 2 * index + 1, beg, mid);
        build(a, 2 * index + 2, mid + 1, end);

        tree[index].sum = tree[2 * index + 1].sum + tree[2 * index + 2].sum;
        tree[index].prefix = max(tree[2 * index + 1].prefix,tree[2 * index + 1].sum +tree[2 * index + 2].prefix);
        tree[index].suffix = max(tree[2 * index + 2].suffix,tree[2 * index + 2].sum +tree[2 * index + 1].suffix);
    }
}

Node query(intt index, intt beg, intt end, intt l, intt r)
{
    Node result;
    result.sum = result.suffix=result.prefix = -1e15;


    if (beg > r || end < l)
        return result;

    if (beg >= l && end <= r)
        return tree[index];

    intt mid = (beg + end) / 2;

    if (l > mid)
        return query(2 * index + 2, mid + 1, end,
                     l, r);
    if (r <= mid)
        return query(2 * index + 1, beg, mid,
                     l, r);

    Node left = query(2 * index + 1, beg, mid,
                      l, r);
    Node right = query(2 * index + 2, mid + 1,
                       end, l, r);

    // adds the sum of the left and right
    // segment
    result.sum = left.sum + right.sum;

    // stores the max of prefix-sum
    result.prefix = max(left.prefix, left.sum +
                        right.prefix);
    result.suffix = max(right.suffix, right.sum +
                        left.suffix);
    // returns the value
    return result;
}

void update(intt a[], intt index, intt beg, intt end,intt pos,intt val)
{

    if (beg == end)
    {
        //a[beg]=val;
        tree[index].sum = val;
        tree[index].prefix = val;
        tree[index].suffix=val;
    }
    else
    {
        intt mid = (beg + end) / 2;

        if(pos<=mid)build(a, 2 * index + 1, beg, mid);
        else build(a, 2 * index + 2, mid + 1, end);


        tree[index].sum = tree[2 * index + 1].sum + tree[2 * index + 2].sum;

        tree[index].prefix = max(tree[2 * index + 1].prefix,tree[2 * index + 1].sum +tree[2 * index + 2].prefix);
        tree[index].suffix = max(tree[2 * index + 2].suffix,tree[2 * index + 2].sum +tree[2 * index + 1].suffix);
    }
}

int main()
{

    intt q;
    scanf("%lld%lld", &n,&q);
    for(intt i = 0; i <n; i++) scanf("%lld",&a[i]);

    build(a, 0, 0, n - 1);

    for(intt i = 0; i < q; i++){
       intt ti;
       string cc;
       cin>>cc;
        scanf("%lld%lld",&ti,&x);

        if(cc=="Q")
        {
            ti--;
            x--;
            Node tem=query(0,0,n-1,ti,x);

            ans=tem.sum;

            if(ti>0)
            {
              tem=query(0,0,n-1,0,ti-1);
              if(tem.suffix>0)ans+=tem.suffix;

            }
            if(x-1<n)
            {
                tem=query(0,0,n-1,x+1,n-1);
                if(tem.prefix>0)ans+=tem.prefix;
            }
            printf("%lld\n",ans);
        }
        else
        update(a,0, 0, n-1, ti-1,x);


    }

    return 0;
}
