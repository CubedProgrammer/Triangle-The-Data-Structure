#include<stdio.h>
#include<stdlib.h>
unsigned int max_u_i(unsigned int,unsigned int);
void build_seg_tree(unsigned int*arr,unsigned int*mtree,unsigned int size,unsigned int(*op)(unsigned int,unsigned int));
void build(unsigned int*arr,unsigned int*mtree,unsigned int node,unsigned int l,unsigned int r,unsigned int(*op)(unsigned int,unsigned int));
unsigned int query(unsigned int*arr,unsigned int*mtree,unsigned int size,unsigned int k,unsigned int x,unsigned int y,unsigned int dp);
unsigned int query_seg_tree(unsigned int*mtree,unsigned int node,unsigned int nl,unsigned int nr,unsigned int l,unsigned int r,unsigned int(*op)(unsigned int,unsigned int));
int main(int argl,char**argv)
{
    unsigned long long ans=0;
    unsigned int n=0,k=0;
    scanf("%d %d",&n,&k);
    unsigned int size=n*(n+1)/2;
    unsigned int*arr=(unsigned int*)malloc(size*sizeof(unsigned int));
    for(unsigned int*it=arr;it!=arr+size;++it)
    {
        scanf("%d",it);
    }
    unsigned int dp=0;
    unsigned int m=1;
    while(m<size)
    {
        m<<=1;
        dp++;
    }
    m<<=1;
    dp*=3;
    unsigned int*mt=(unsigned int*)malloc(m*sizeof(unsigned int));
    build_seg_tree(arr,mt,size,&max_u_i);
    for(unsigned int i=0;i<n-k+1;i++)
    {
        for(unsigned int j=0;j<=i;j++)
        {
            ans+=query(arr,mt,size,k,j,i,dp);
        }
    }
    printf("%llu\n",ans);
    return 0;
}
unsigned int max_u_i(unsigned int x,unsigned int y)
{
    return x>y?x:y;
}
void build_seg_tree(unsigned int*arr,unsigned int*mtree,unsigned int size,unsigned int(*op)(unsigned int,unsigned int))
{
    build(arr,mtree,0,0,size,op);
}
void build(unsigned int*arr,unsigned int*mtree,unsigned int node,unsigned int l,unsigned int r,unsigned int(*op)(unsigned int,unsigned int))
{
    if(l+1==r)
    {
        mtree[node]=arr[l];
        return;
    }
    build(arr,mtree,(node<<1)+1,l,l+r+1>>1,op);
    build(arr,mtree,node+1<<1,l+r+1>>1,r,op);
    mtree[node]=(*op)(mtree[(node<<1)+1],mtree[node+1<<1]);
}
unsigned int query(unsigned int*arr,unsigned int*mtree,unsigned int size,unsigned int k,unsigned int x,unsigned int y,unsigned int dp)
{
    unsigned int ans=0;
    for(unsigned int i=0;i<k;i++)
    {
        if(i<dp)
        {
            for(unsigned int j=0;j<=i;j++)
            {
                ans=max_u_i(arr[(y+i)*(y+i+1)/2+x+j],ans);
            }
        }
        else
        {
            ans=max_u_i(query_seg_tree(mtree,0,0,size,(y+i)*(y+i+1)/2+x,(y+i)*(y+i+1)/2+x+i+1,&max_u_i),ans);
        }
    }
    return ans;
}
unsigned int query_seg_tree(unsigned int*mtree,unsigned int node,unsigned int nl,unsigned int nr,unsigned int l,unsigned int r,unsigned int(*op)(unsigned int,unsigned int))
{
    if(nr<=l||nl>=r)
        return 0;
    if(nl>=l&&nr<=r)
        return mtree[node];
    return(*op)(query_seg_tree(mtree,(node<<1)+1,nl,nl+nr+1>>1,l,r,op),query_seg_tree(mtree,node+1<<1,nl+nr+1>>1,nr,l,r,op));
}
