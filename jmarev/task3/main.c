#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>

typedef struct period
{
    size_t digit;
    struct period* next;
} period;

int ContinuedFractionFromSquare(size_t N,size_t* h,period** head,period** back)
{
    size_t factor=1,b,denomenator;
    int term;
    (*h)=N;

    while(1)
    {
        b=((*h)+N/(*h))/2;
        if(b>=(*h))
        {
            break;
        };
        (*h)=b;
    };
    (*head)=(*back)=(period*)malloc(sizeof(period));
    if((*head)==NULL)
    {
        return 1;
    };
    if(pow(*h,2)==N)
    {
        (*head)->digit=0;
        return 0;
    };
    (*back)->digit=(size_t)(2*(*h))/(N-(powf((*h),2)));
    (*back)->next=0;
    denomenator=N-powf((*h),2);
    if(denomenator==1)
    {
        return 0;
    };
    term=(*h)-(((*back)->digit)*denomenator);
    while(1)
    {
        (*back)->next=(period*)malloc(sizeof(period));
        if(((*back)->next)==NULL)
        {
            return 1;
        };
        if(term==(-1)*(*h))
        {
            (*back)->next->digit=(-2)*term;
            (*back)->next->next=0;
            return 0;
        };
        factor=denomenator;
        denomenator=N-powf(term,2);
        term*=-1;
        denomenator/=factor;
        factor=1;
        (*back)->next->digit=(((*h)+term)/denomenator);
        term=term-(((*back)->next->digit)*denomenator);
        (*back)=(*back)->next;
    };
    if((*back)->next->next!=0)
    {
        (*back)->next=0;
    };
    printf("%zu=[%zu;(",N,*h);
    while(((*head)->next))
    {
        (*back)=(*head);
        printf("%zu; ",((*back)->digit));
        (*head)=(*head)->next;
    };
    printf("%zu)]\n",((*head)->digit));
    return 0;
};

int print_and_free_memory(size_t N)
{
    size_t i,h;
    int result;
    period* head,* back;

    for(i=1;i<=N;i++)
    {
        result=ContinuedFractionFromSquare(i,&h,&head,&back);
        if(result!=0)
        {
            return 1;
        };
        if(head->digit==0)
        {
            printf("%zu=[%zu]\n",i,h);
            continue;
        };
        printf("%zu=[%zu;(",i,h);
        back=head;
        while(back->next)
        {
            printf("%zu; ",back->digit);
            head=back;
            back=back->next;
            free(head);
        };
        printf("%zu)]\n",back->digit);
        free(back);
        };
    return 0;
};

int main()
{
    size_t N;
    int result;

    scanf("%zu",&N);
    result=print_and_free_memory(N);
    if(result!=0)
    {
        printf("Error\n");
    };
    return 0;
};
