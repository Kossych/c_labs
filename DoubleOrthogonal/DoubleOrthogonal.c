#include <stdio.h>
#include <stdbool.h>

int IsDoubleOrthogonal(int a, int b)
{ 
    int OrthB=(a^b)&a;
    int OrthA=(a^b)&b;
    if(OrthA>OrthB){
        if((OrthA-1)&OrthB==OrthB) return true;
    }
    else
    if(OrthA<OrthB)
    {
        if((OrthB-1)&OrthA==OrthA) return true;
    }
    return false;
}

int main(){
    int a=5;
    int b=2;
    int c=IsDoubleOrthogonal(a,b);
    printf("%d",c);
}