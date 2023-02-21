#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define _scan_ui(__x__)scanf("%u",&__x__)
#define max(x,y)((x)>(y)?x:y)
struct triangle
{
    unsigned*dat;
    unsigned len;
};
void destroy_triangle(struct triangle*this)
{
    free(this->dat);
}
int init_triangle(struct triangle*this,unsigned*restrict arr,unsigned len)
{
    unsigned depth=1,cnt=1;
    unsigned area,pos,inc;
    if(len>1)
        cnt=depth=2;
    for(;len>cnt;++depth)
        cnt+=cnt>>1;
    this->len=len;
    this->dat=malloc(depth*(area=len*(len+1)>>1)*sizeof(*this->dat));
    if(this->dat==NULL)
        return-1;
    memcpy(this->dat,arr,area*sizeof(unsigned));
    for(unsigned i=0;i+1<len;++i)
    {
        for(unsigned j=0;j+i+1<len;++j)
        {
            pos=len*i-(i*(i-1)>>1)+j;
            this->dat[area+pos]=max(this->dat[pos], max(this->dat[pos+1], this->dat[pos+len-i]));
        }
    }
    cnt = 2;
    for(unsigned i=2;i<depth;++i)
    {
        inc=cnt>>1;
        for(unsigned j=0;j+(cnt>>1)+cnt<=len;++j)
        {
            for(unsigned k=0;k+j+(cnt>>1)+cnt<=len;++k)
            {
                pos=len*j-(j*(j-1)>>1)+k;
                this->dat[i*area+pos] = max(this->dat[(i-1)*area+pos], max(this->dat[(i-1)*area+pos+inc], this->dat[(i-1)*area+pos+(len-j)*inc-(inc*(inc-1)>>1)]));
            }
        }
        cnt+=inc;
    }
    return 0;
}
unsigned query_triangle(const struct triangle*this,unsigned r,unsigned c,unsigned ind)
{
    unsigned total=this->len*(this->len+1)>>1;
    return this->dat[total*ind+this->len*r-((r-1)*r>>1)+c];
}
int main(int argl,char**argv)
{
    struct triangle t;
    unsigned n=0,k=0;
    unsigned r=0,c=0;
    _scan_ui(n);
    _scan_ui(k);
    unsigned size=n*(n+1)/2;
    unsigned*arr=(unsigned*)malloc(size*sizeof(unsigned));
    for(unsigned i=0;i<size;++i)
    {
        _scan_ui(arr[n*r-(r*(r-1)>>1)+c]);
        c++;
        if(r==0)
        {
            r=c;
            c=0;
        }
        else
            --r;
    }
    unsigned dist=2,ind=1;
    for(;dist<k;++ind,dist+=dist>>1);
    if(k==1)
        dist=1,ind=0;
    if(dist!=k)
    {
        dist-=dist/3;
        --ind;
    }
    long tot=0;
    unsigned f,g,h;
    init_triangle(&t,arr,n);
    for(unsigned i=0;i+k<=n;++i)
    {
        for(unsigned j=0;j+i+k<=n;++j)
        {
            if(k==dist)
                tot+=query_triangle(&t,i,j,ind);
            else
            {
                f=query_triangle(&t,i,j,ind);
                g=query_triangle(&t,i+k-dist,j,ind);
                h=query_triangle(&t,i,j+k-dist,ind);
                tot+=max(f,max(g,h));
            }
        }
    }
    destroy_triangle(&t);
    free(arr);
    printf("%ld\n",tot);
    return 0;
}
