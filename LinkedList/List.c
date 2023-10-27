#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

struct Node
{
    int key; // Информационное поле, для хранения целого числа
    struct Node *next;// адрес следующего элемента
    struct Node *prew;// адрес предыдущего элемента
};

bool AddToHead(struct Node **list, int key)
{
    struct Node *PtrIx=(struct Node*)malloc(sizeof(struct Node));
    if(PtrIx)
    {
        PtrIx->key=key;
        PtrIx->next=NULL;
        PtrIx->prew=NULL;
        if(*list==NULL)
            *list=PtrIx;
        else
        {
            PtrIx->next=*list;
            (*list)->prew=PtrIx;
            *list=PtrIx;
        }
        return true;
    }
    return false;
}

bool AddToTail(struct Node *list,int key)
{
    struct Node *PtrIx=(struct Node*)malloc(sizeof(struct Node));
    if (PtrIx){
        PtrIx->key=key;
        PtrIx->next=NULL;
        PtrIx->prew=NULL;
        if(list==NULL)
            return false;
        else
        {
            while((list)->next!=NULL)
                list=(list)->next;
            PtrIx->prew=list;
            (list)->next=PtrIx;
        }
        return true;
    }
    return false;
}

bool AddBeforeValue(struct Node **list,int key,int newkey)
{
    if(*list)
    {
        struct Node *PtrIx=(struct Node*)malloc(sizeof(struct Node));
        if (PtrIx)
        {
            PtrIx->key=newkey;
            PtrIx->next=NULL;
            PtrIx->prew=NULL;
            struct Node *ptr=*list;
            if(ptr->key==key)
            {
                PtrIx->next=ptr;
                ptr->prew=PtrIx;
                *list=(*list)->prew;
                return true;
            }
            for(;ptr&&ptr->key!=key;ptr=ptr->next);
            if(ptr)
            {
                PtrIx->next=ptr;
                PtrIx->prew=ptr->prew;
                (ptr->prew)->next=PtrIx;
                ptr->prew=PtrIx;
                return true;
            }
        }
    }
    return false;
}

bool AddAfterValue(struct Node **list, int key, int newkey)
{
    if(*list){
        struct Node *PtrIx=(struct Node*)malloc(sizeof(struct Node));
        if (PtrIx){
            PtrIx->key=newkey;
            PtrIx->next=NULL;
            PtrIx->prew=NULL;
            struct Node *ptr=NULL;
            for(ptr=(*list);ptr&&ptr->key!=key;ptr=ptr->next);
            if(ptr){
                if(ptr->next)
                    (ptr->next)->prew=PtrIx;
                PtrIx->next=ptr->next;
                PtrIx->prew=ptr;
                ptr->next=PtrIx;
                return true;
            }
        }
    }
    return false;
}

bool AddInValue(struct Node **list, int key, int newkey)
{
    if(list){
        struct Node *PtrIx=(struct Node*)malloc(sizeof(struct Node));
        if (PtrIx){
            PtrIx->key=newkey;
            PtrIx->next=NULL;
            PtrIx->prew=NULL;
            struct Node *ptr=*list;
            for(ptr=(*list);ptr&&ptr->key!=key;ptr=ptr->next);
            if(ptr){
                PtrIx->next=ptr->next;
                PtrIx->prew=ptr->prew;
                if(ptr->next)
                    (ptr->next)->prew=PtrIx;
                if(ptr->prew)
                    (ptr->prew)->next=PtrIx;
                else 
                    *list=PtrIx;
                free(ptr);
                return true;
            }
        }
    }
    return false;
}

bool DelHead(struct Node **list)
{
    if(*list)
    {
        if((*list)->next){
            struct Node *ptrix=*list;
            *list=(*list)->next;
            (*list)->prew=NULL;
            ptrix->next=NULL;
            free(ptrix);
            return true;
        }
        else
        { 
            free(*list); 
            *list=NULL; 
            return true;
        }
    }
    return false;
}

bool DelTail(struct Node **list)
{
    if(*list){
        struct Node *ptr=*list;
        while(ptr->next!=NULL)
            ptr=ptr->next;
        if(ptr->prew){
            (ptr->prew)->next=NULL;
            ptr->prew=NULL;
            free(ptr);
            return true;
        }
        else
        { 
            free(*list); 
            *list=NULL; 
            return true;
            }
    }
    return false;
}

bool DelBeforeValue(struct Node **list, int key)
{
    if (*list)
    {
        struct Node *ptr=*list;
        for(;ptr&&ptr->key!=key;ptr=ptr->next);
        if(ptr)
        {
            if(ptr->prew==NULL) return false;
            ptr=ptr->prew;
            if(ptr->prew==NULL)
            {
                (ptr->next)->prew=NULL;
                *list=ptr->next;
                ptr->next=NULL;
                free(ptr);
                return true;
            }
            (ptr->prew)->next=ptr->next;
            (ptr->next)->prew=ptr->prew;
            ptr->next=NULL; ptr->prew=NULL;
            free(ptr);
            return true;
        }
    }
    return false;
}

bool DelAfterValue(struct Node **list, int key)
{
    if (*list)
    {
        struct Node *ptr=*list;
        for(;ptr&&ptr->key!=key;ptr=ptr->next);
        if(ptr)
        {
            if(ptr->next==NULL) return false;
            ptr=ptr->next;
            if(ptr->next==NULL)
            {
                (ptr->prew)->next=NULL;
                ptr->prew=NULL;
                free(ptr);
                return true;
            }
            (ptr->prew)->next=ptr->next;
            (ptr->next)->prew=ptr->prew;
            ptr->next=NULL; ptr->prew=NULL;
            free(ptr);
            return true;
        }
    }
    return false;
}

bool DelValue(struct Node **list, int key)
{
    if (*list)
    {
        struct Node *ptr=*list;
        for(;ptr&&ptr->key!=key;ptr=ptr->next);
        if(ptr)
        {
            if(ptr->prew)
                (ptr->prew)->next=ptr->next;
            else
            {
                if(ptr->next)
                    *list=ptr->next;
                else
                {
                    *list=NULL;
                    free(ptr);
                    return true;
                }
            }
            if(ptr->next)
            {
                (ptr->next)->prew=ptr->prew;
                ptr->next=NULL;
            }
            ptr->prew=NULL;
            free(ptr);
            return true;
        }
    }
    return false;
}

bool DelList(struct Node **list)
{
    if(*list)
    {
        struct Node *ptr=*list;
        while(*list)
        {
            *list=(*list)->next;
            if(ptr->next)
            {
                (ptr->next)->prew=NULL;
                ptr->next=NULL;
            }
            free(ptr);
            ptr=*list;
        }
        return true;
    }
    return false;
}

bool SearchValue(struct Node **PtrIx, int key)
{
    for(;(*PtrIx)&&(*PtrIx)->key!=key;*PtrIx=(*PtrIx)->next);
    if(PtrIx) return true;
    return false;
}

bool PrintList(struct Node *PtrIx)
{
    if(PtrIx)
    {
        int seq=0;
        printf("-1 or 1? ");
        scanf("%d",&seq);
        if(seq==1){
            while(PtrIx->prew!=NULL) PtrIx=PtrIx->prew;
            while(PtrIx){ printf("%d\n",PtrIx->key); PtrIx=PtrIx->next;}
            return true;
        }
        else if(seq==-1)
        {
            while(PtrIx->next!=NULL) PtrIx=PtrIx->next;
            while(PtrIx){ printf("%d\n",PtrIx->key); PtrIx=PtrIx->prew;}
            return true;
        }
    }
    return false;
}

int main()
{
    struct Node *head=NULL;
    int key=1;
    //AddToHead(&head,key);

    for(int i=2;i<=10;i++)
    AddToTail(head,i);

    int newkey=15;
    key=2;
    //AddBeforeValue(&head,key,newkey);
    //AddAfterValue(&head,key,newkey);
    //AddInValue(&head,key,newkey);
    //DelHead(&head);
    //DelTail(&head);
    //DelBeforeValue(&head,key);

    //DelAfterValue(&head,key);
    //DelValue(&head,key);
    //DelList(&head);
    //SearchValue(&PtrIx,key);
    //printf("Key = %d\n",PtrIx->key);

    struct Node *PtrIx=head;
    PrintList(PtrIx);
}
