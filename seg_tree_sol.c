#include<stdio.h>
#include<stdlib.h>
unsigned int max_u_i(unsigned int,unsigned int);
void build_seg_tree(unsigned int*arr,unsigned int*mtree,unsigned int size,unsigned int(*op)(unsigned int,unsigned int));
void build(unsigned int*arr,unsigned int*mtree,unsigned int node,unsigned int l,unsigned int r,unsigned int(*op)(unsigned int,unsigned int));
int main(int argl,char**argv)
{
    unsigned int n=0,k=0;
    scanf("%d %d",&n,&k);
    unsigned int size=n*(n+1)/2;
    unsigned int*arr=(unsigned int*)malloc(size*sizeof(unsigned int));
    for(unsigned int*it=arr;it!=arr+size;++it)
    {
        scanf("%d",it);
    }
    unsigned int dp=0;
    unsigned int m=n;
    while(m<n)
    {
        m<<=1;
        dp++;
    }
    m<<=1;
    dp*=3;
    unsigned int*mt=(unsigned int*)malloc(m*sizeof(unsigned int));
    build_seg_tree(arr,mt,size,&max_u_i);
    return 0;
}
unsigned int max_u_i(unsigned int x,unsigned int y)
{
    return x<y?x:y;
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
