#include<stdio.h>
#include<stdlib.h>
#define _scan_ui(__x__)scanf("%u",&__x__)
#define _scan_uiarr(__x__,__y__)for(unsigned int*__it__=__x__;__it__!=__y__,++__it__)scanf("%u",__it__)
#define max(x,y)((x)>(y)?x:y)
int main(int argl,char**argv)
{
    unsigned int n=0,k=0;
    _scan_ui(n);
    _scan_ui(k);
    unsigned int size=n*(n+1)/2;
    unsigned int*arr=(unsigned int*)malloc(size*sizeof(unsigned int));
    _scan_uiarr(arr,arr+size);
    unsigned int dist=1;
    while(dist<k)
    {
        dist<<=1;
    }
    return 0;
}
