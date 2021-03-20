#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>

int DiophantEquation(int* a,int* b,int c,int* d,int* x_private,int* y_private,char* psign_x,char* psign_y)
{
    int X[3];
    int Y[3];
    int q,z;
    size_t i;
    int r[2];

    psign_x[0]='+';
    psign_x[1]='+';
    psign_y[0]='+';
    psign_y[1]='-';
    if((*a)<0)
    {
        (*a)=-(*a);
        psign_x[0]='-';
        psign_x[1]='-';
    };
    if((*b)<0)
    {
        *b=-(*b);
        psign_y[0]='-';
        psign_y[1]='+';
    };
    if((*a)>(*b))
    {
        r[0]=(*a);
        r[1]=(*b);
        X[0] = 1;
        X[1] = 0;
        Y[0] = 0;
        Y[1] = 1;
    }
    else
    {
        r[0]=(*b);
        r[1]=(*a);
        X[0] = 0;
        X[1] = 1;
        Y[0] = 1;
        Y[1] = 0;
    };
    while(1)
    {
        q=r[0]/r[1];
        z=r[1];
        r[1]=r[0]%r[1];
        r[0]=z;
        if(r[1]==0)
        {
            break;
        };

        X[2]=X[0]-X[1]*q;
        Y[2]=Y[0]-Y[1]*q;

        for(i=0; i<2; i++)
        {
            X[i]=X[i+1];
            Y[i]=Y[i+1];
        };
    };

    *d=r[0];
    if(c%(*d)!=0)
    {
        return 1;
    };
    *x_private=X[2];
    *y_private=Y[2];

    if(psign_x[0]=='-')
    {
        psign_x[0]='+';
        (*x_private)=-(*x_private);
    };
    if(psign_x[1]=='-'&&((*b)/(*d))<0)
    {
        psign_x[1]='+';
        (*b)=-(*b);
    };
    if(psign_x[1]=='-'&&((*b)/(*d))>0)
    {
        psign_x[1]=0;
        (*b)=-(*b);
    };
    if(psign_y[0]=='-')
    {
        psign_y[0]='+';
        (*y_private)=-(*y_private);
    };
    if(psign_y[1]=='-'&&((*a)/(*d))<0)
    {
        psign_y[1]='+';
        (*a)=-(*a);
    };
    if(psign_y[1]=='-'&&((*a)/(*d))<0)
    {
        psign_y[1]=0;
        (*a)=-(*a);
    };
    return 0;
};

int main()
{
    int a,b,c,d,x_private,y_private,k,result;
    char sign_x[2],sign_y[2];
    char* psign_x=sign_x,* psign_y=sign_y;

    scanf("%d",&a);
    scanf("%d",&b);
    scanf("%d",&c);
    result=DiophantEquation(&a,&b,c,&d,&x_private,&y_private,psign_x,psign_y);
    if(result!=0)
    {
        printf("Error\n");
        return 1;
    }
    printf("x=%d%c%dk\n",x_private*(c/d),sign_x[1],b/d);
    printf("y=%d%c%dk\n",y_private*(c/d),sign_y[1],a/d);
    scanf("%d",&k);
    printf("x=%d\n",x_private*(c/d)+(b/d)*k);
    printf("y=%d\n",y_private*(c/d)-(a/d)*k);
    return 0;
};
