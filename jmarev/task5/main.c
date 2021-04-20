#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct node
{
    int digit;
    struct node* next;
} node;

int DecimalToFactorial(int decimal)
{
    int i = 2, f = 1, factorial;
    char sign = 0;

    if(decimal < 0)
    {
        sign = 1;
        decimal *= -1;
    };

    while(f<=decimal)
    {
        f *= i;
        i ++;
    };
    i --;
    f /= i;
    factorial=decimal / f;

    while(i > 2)
    {
        decimal %= f;
        i --;
        f /= i;
        factorial *= 10;
        factorial += decimal / f;
    };

    if(sign == 1)
    {
        factorial *= -1;
    };

    return factorial;
};

int FactorialToDecimal(int factorial)
{
    int f = 1,decimal = 0;
    size_t i;

    for (i = 1; factorial != 0; i ++)
    {

        f *= i;
        decimal += (factorial%10)*f;
        factorial /= 10;
    };

    return decimal;
};

int GetIndexFromTransposition(int transposition,int n)
{
    node* head,* back,* p;
    int current_digit, index,counter = 0;
    size_t i, k;

    if(n < 1)
    {
        return -1;
    };

    head=(node*)malloc(sizeof(node));
    if(head == NULL)
    {
        return -2;
    }

    back = head;
    head->digit = 1;
    head->next = NULL;

    for(i = 0; i < n - 1; i ++)
    {
        back->next = (node*)malloc(sizeof(node));
        if(back->next == NULL)
        {
            return -2;
        };
        back->next->digit = i + 2;
        back = back->next;
    };
    back->next = NULL;
    back = head;
    for(k = 1; transposition > pow(10,k); k++);
    k -= 1;

    for(i = 0; head != NULL; i++)
    {
        current_digit = transposition / pow(10,k);
        transposition -= current_digit * pow(10,k);
        k -= 1;

        index *= 10;

        if(head->digit == current_digit)
        {
            p = head;
            head = head->next;
            free(p);
        }
        else
        {
            counter = 0;
            for(back = head;back->next->digit != current_digit;back = back->next)
            {
                counter ++;
            }
            counter += 1;
            index += counter;
            p = back->next;
            back->next = back->next->next;
        };
        free(p);
    };
    return (FactorialToDecimal(index / 10) + 1);
};

int GetTranspositionFromIndex (int index, int n)
{
    int factorial, transposition = 0, current_digit;
    node* head,* back,* p;
    size_t i, k;

    if(n < 1)
    {
        return -1;
    };

    head = (node*)malloc(sizeof(node));
    if(head == NULL)
    {
        return -2;
    }

    back = head;
    head->digit = 1;
    head->next = NULL;

    for(i = 0; i < n-1; i ++)
    {
        back->next = (node*)malloc(sizeof(node));
        if(back->next == NULL)
        {
            return -2;
        };
        back->next->digit = i + 2;
        back = back->next;
    };
    back->next = NULL;

    factorial = (DecimalToFactorial(index - 1)) * 10;
    for(k = 1; factorial > pow(10,k); k ++);
    k -= 1;
    if(k + 2 < n)
    {
        current_digit = 0;
        for(i = 0; i<(n - (k + 2)); i ++)
        {
            transposition *= 10;
            transposition += head->digit;
            p = head;
            head = head->next;
            free(p);
        };

    };
    for(i = 0; head != NULL; i++)
    {
        current_digit = factorial / pow(10,k);
        factorial-=current_digit*pow(10,k);
        k -= 1;
        back = head;
        transposition *= 10;
        if(current_digit == 0)
        {
            transposition += back->digit;
            p = back;
            head = back->next;
            free(p);
        }
        else
        {
            for(i = 0; i < current_digit-1; i++)
            {
                back = back->next;
            };

            transposition += back->next->digit;
            p = back->next;
            back->next = back->next->next;
            free(p);
        };
    };
    back = head;

    return transposition;
};

int GetNextTransposition(int current_transposition)
{
    int current_index,next_transposition;
    size_t k;

    for(k = 1; current_transposition > pow(10,k); k ++);

    current_index = GetIndexFromTransposition(current_transposition, k);
    if(current_index == -1)
    {
        return -1;
    };
    if(current_index == -2)
    {
        return -2;
    }
    next_transposition = GetTranspositionFromIndex(current_index + 1, k);
    if(next_transposition == -1)
    {
        return -3;
    };
    if(next_transposition == -2)
    {
        return -4;
    }
    return next_transposition;
};

int main()
{
    int mode, input_data1, input_data2,output;
    scanf("%d", &mode);
    while(mode <= 0)
    {
        printf("Invalid mode index, input it again\n");
        scanf("%d", &mode);
    };
    scanf("%d", &input_data1);
    switch(mode)
    {
        case 1:
        {
            printf("%d\n", DecimalToFactorial(input_data1));
        };
        case 2:
        {
            printf("%d\n", FactorialToDecimal(input_data1));
        };
        case 3:
        {
            output=GetNextTransposition(input_data1);
            if(output<0)
            {
                printf("Error\n");
                return output;
            };
            printf("%d\n", output);
        };
        case 4:
        {
            scanf("%d", &input_data2);
            output=GetIndexFromTransposition(input_data1, input_data2);
            if(output<0)
            {
                printf("Error\n");
                return output;
            };
            printf("%d\n", output);
        };
        case 5:
        {
            scanf("%d", &input_data2);
            output=GetTranspositionFromIndex(input_data1, input_data2);
            if(output<0)
            {
                printf("Error\n");
                return output;
            };
            printf("%d\n", output);
        };
    };

    return 0;
};
