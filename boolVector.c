#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char* LogAdd(unsigned char *VecA, unsigned char *VecB)
{
    if(VecA&&VecB){
        int i=0;
        int Sizeres=0;
        if(sizeof(VecA)>sizeof(VecB))
            Sizeres=sizeof(VecA);
        else
            Sizeres=sizeof(VecB);
        unsigned char *res=(unsigned char*)calloc(Sizeres,sizeof(unsigned char));
        if(res)
        {
            while(VecA[i]&&VecB[i])
            {
                res[i]=VecA[i]|VecB[i];
                i++;
            }
            while(VecA[i]){
                res[i]=VecA[i];
                i++;
            }
            while(VecB[i])
            {
                res[i]=VecB[i];
                i++;
            }
        return res;
        }
    }
    return NULL;
}

unsigned char* LogMultip(unsigned char *VecA, unsigned char *VecB)
{
    if(VecA&&VecB){
        int i=0;
        int Sizeres=0;
        if(sizeof(VecA)<sizeof(VecB))
        Sizeres=sizeof(VecA);
        else
        Sizeres=sizeof(VecB);
        unsigned char *res=(unsigned char*)calloc(Sizeres,sizeof(unsigned char));
        if(res)
        {
            while(VecA[i]&&VecB[i])
            {
                res[i]=VecA[i]&VecB[i];
                i++;
            }
            return res;
        }
    }
    return NULL;
}

unsigned char* Xor(unsigned char *VecA, unsigned char *VecB)
{
    if(VecA&&VecB){
        int i=0;
        int Sizeres=0;
        if(sizeof(VecA)>sizeof(VecB))
        Sizeres=sizeof(VecA);
        else
        Sizeres=sizeof(VecB);
        unsigned char *res=(unsigned char*)calloc(Sizeres,sizeof(unsigned char));
        if(res){
            while(VecA[i]&&VecB[i])
            {
                res[i]=VecA[i]^VecB[i];
                i++;
            }
            while(VecA[i])
            {
                res[i]=VecA[i];
                i++;
            }
            while(VecB[i])
            {
                res[i]=VecB[i];
                i++;
            }
            return res;
        }
    }
    return NULL;
}

unsigned char* InvertVec(unsigned char *VecA)
{
    if(VecA)
    {
        int i=0;
        while(VecA[i])
        {
            VecA[i]=VecA[i]^0xFF;
            i++;
        }
        return VecA;
    }
    return NULL;
}

void Shift(unsigned char *VecA, int shiftval)
{
    if(VecA)
    {
        unsigned short shiftcell=shiftval/8;
        shiftval=shiftval%8;

        if(shiftval>0)
        {
            unsigned short mask=(0xFF >> (8-shiftval)) << (8-shiftval);
            int i=0;
            for(;VecA[i+1];i++);
            for(;i>shiftcell;i--)
            {
                VecA[i]=(VecA[i-shiftcell] << shiftval);
                VecA[i]=VecA[i]|(VecA[i-1-shiftcell]&mask);
            }
            VecA[i]=VecA[i-shiftcell] << shiftval;
            for(i=i-1;i>=0;i--)
            VecA[i]=VecA[i]&0;
        }

        if(shiftval<0){
            unsigned short mask=(0xFF >> (8+shiftval)) << (8+shiftval);
            for(int i=shiftcell;VecA[i];i++)
            {
                VecA[i]=(VecA[i+shiftcell] << shiftval);
                VecA[i]=VecA[i]|(VecA[i+1-shiftcell]&mask);
            }
            for(int i=0;i>=shiftcell;i--)
            VecA[i]=VecA[i] << shiftval;
        }
    }
}

unsigned short* ConvertInBool(unsigned char *VecA)
{
    if(VecA)
    {
        unsigned short *BoolVec=(unsigned short*)calloc(sizeof(VecA),sizeof(unsigned short));
        if(BoolVec)
        {
            for(int i=0;VecA[i];i++)
            BoolVec[i]=VecA[i];
            return BoolVec;
        }
    }
    return NULL;
}

unsigned char* ConvertInStr(unsigned short *BoolVec)
{
    if(BoolVec)
    {
        int size=0;
        for(;BoolVec[size+1];size++);
        unsigned char *VecA=(unsigned char*)malloc(size*sizeof(unsigned char));
        if(VecA)
        {
            for(int i=0;BoolVec[i];i++)
            {
                VecA[i]=BoolVec[i];
            }
            return VecA;
        }
    }
    return NULL;
}

void SetBit(unsigned char *VecA, unsigned long value)
{
    if(VecA&&(value>0))
    {
        int cell=value/8;
        value=(value%8)-1;
        VecA[cell]=VecA[cell]|(1 << value);
    }
}

void DelBit(unsigned char *VecA, unsigned long value)
{
    if(VecA && (value > 0))
    {
        int i = 0;
        int cell = value / 8;
        value = (value % 8) - 1;
        VecA[cell] = VecA[cell] & (0xFF ^ (1 << value));
    }
}

unsigned char* ScanVec()
{
    int len=0;
    int size=1;
    unsigned char *vec=(unsigned char*) malloc(size*sizeof(unsigned char));
    if(!vec) return NULL;
    unsigned char c=getchar();
    while(c!='\n')
    {
        if(c!='1'&&c!='0') return NULL;
        vec[len/8]=vec[len/8] << 1;
        if(c=='1')
        vec[len/8]=vec[len/8]|1;
        len++;
        if(len==8)
        {
            size=size*2;
            vec=(unsigned char*) realloc(vec,size*sizeof(unsigned char));
            if (!vec) return NULL;
        }
        c=getchar();
    }
    if(len % 8) vec[len / 8] = vec[len / 8] << (8 - len % 8);
    vec[len/8+1]='\0';
    return vec;
}

void PrintVec(unsigned char *vec)
{
    if(vec)
    {
        int i=0;
        for(;vec[i];i++)
        {
            short bit=1;
            for(int j=7;j>=0;j--)
            {
                bit=vec[i]&(1 << j);
                if(bit) printf("1");
                else printf("0");
            }
        }
    }
}

void PrintBoolVec(unsigned short *vec)
{
    if(vec)
    {
        for(int i=0;vec[i];i++)
        printf(" %hu",vec[i]);
    }
}

int main()
{
    unsigned char *res=NULL;
    unsigned char *vec=ScanVec();
    //unsigned char *vec2=ScanVec();
    //res=Xor(vec,vec2);
    //res=LogMultip(vec,vec2);
    //res=LogAdd(vec,vec2);
    vec=InvertVec(vec);
    //int value=-3;
    //SetBit(vec,value);
    //DelBit(vec,value);
    //Shift(vec,value);
    //unsigned short *b=ConvertInBool(a);
    //unsigned char *A=ConvertInStr(b);
    PrintVec(vec);
    //A=InvertVec(A);
    //b=ConvertInBool(A);
}