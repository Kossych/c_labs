#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Interval
{
    unsigned long vec;
    unsigned long dnc;
};


int IsOneOrthogonal(struct Interval u, struct Interval v)
{
    unsigned long tmpUV, tmpU, tmpV, UV;
    tmpUV = v.dnc | u.dnc;
    tmpU = u.vec | tmpUV;
    tmpV = v.vec | tmpUV;
    UV=tmpU^tmpV;

    UV = (UV & 0x55555555)+((UV >> 1)  & 0x55555555); //***********************************************************************************************
    UV = (UV & 0x33333333)+((UV >> 2)  & 0x33333333); //*В данном участке кода мы используем метод "Разделяй и властвуй". *
    UV = (UV & 0x0F0F0F0F)+((UV >> 4)  & 0x0F0F0F0F); //*В векторе мы рассматриваем отдельные участки(каждые 2 компонента, 4 и т.д.) *
    UV = (UV & 0x00FF00FF)+((UV >> 8)  & 0x00FF00FF); //*и находим в этих участках кол-во единиц (вектор будет меняться таким образом: ...11 => ...10)*
    UV = (UV & 0x0000FFFF)+((UV >> 16) & 0x0000FFFF); //*в конечном итоге мы найдем вес всего вектора. *

    if (UV == 1) return 1; //если вес равен 1, то ортогонально по 1 компоненте
    else return 0;
}

void main()
{
    struct Interval u, v;
    u.vec=36;
    u.dnc=75; //u=0-10-1— (для теста будем менять значения в тех компенентах, где элементы определенны в одном интервале и другом )
    v.vec=4;
    v.dnc=195; //v=--0001—
    int b=IsOneOrthogonal(u,v);
    printf("%d",b);
}