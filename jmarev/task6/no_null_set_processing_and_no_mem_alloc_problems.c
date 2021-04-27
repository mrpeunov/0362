#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <math.h>

char** GetAllSubsets(int m,char* set)
{
    size_t i,k,counter_for_element,element_len;
    char** array;
    array=(char**)malloc((pow(2,m)-1)*sizeof(char*));
    if(array==NULL)
    {
        printf("Error\n");
        return NULL;
    };
    for(i=1;i<pow(2,m);i++)
    {
        element_len=0;
        for(k=0;i>=pow(2,k);k++)
        {
            if((i>>k)%2==1)
            {
                element_len++;
            };
        };
        array[i-1]=(char*)malloc((element_len+1)*sizeof(char));
        if(array[i-1]==NULL)
        {
            printf("Error\n");
            return NULL;
        };
        counter_for_element=0;
        for(k=0;i>=pow(2,k);k++)
        {
            if((i>>k)%2==1)
            {
                array[i-1][counter_for_element]=set[k];
                counter_for_element++;
            };
        };
        array[i-1][element_len]='\0';
        //printf("%s\n",array[i-1]);
    };
    return array;
};

void GetKElementsSubsets(int n, int m,char** array_p)
{
    size_t i;
    if(n==0)
    {
        printf("%s\n",array_p[0]);
    }
    for(i=0;i<(pow(2,m)-1);i++)
    {
        if(strlen(array_p[i])==n)
        {
            printf("{%s}\n",array_p[i]);
        };
    };
};

void GetSubsetsContainingElement(char subset_element,int m,char** array_p)
{
    size_t i,t;
    for(i=0;i<(pow(2,m)-1);i++)
    {
        for(t=0;t<strlen(array_p[i]);t++)
        {
            if(array_p[i][t]==subset_element)
            {
                printf("{%s}\n",array_p[i]);
            };
        }
    };
};

int main()
{
    size_t i,N,M,mode;
    char symbol;
    char* set;
    char** array_p;
    scanf("%zu",&mode);
    scanf("%zu",&M);
    set=(char*)malloc((M+1) * sizeof(char));
    scanf("%s",set);
    set[M]='\0';
    array_p=GetAllSubsets(M,set);
    if(array_p==NULL)
    {
        return 1;
    };
    switch (mode)
    {
    case 1:
    {
        for(i=0;i<(pow(2,M)-1);i++)
        {
            printf("{%s}\n",array_p[i]);
        };
        break;
    }
    case 2:
    {
        scanf("%zu",&N);

        GetKElementsSubsets(N,M,array_p);
        break;
    }
    case 3:
    {
        fflush(stdin);
        symbol=getc(stdin);

        GetSubsetsContainingElement(symbol,M,array_p);
        break;
    }
    };
    free(set);
    for(i=0;i<(pow(2,M)-1);i++)
    {
        free(array_p[i]);
    };
    free(array_p);
    return 0;
}
