
#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("2\n3\n5\n7\n");
	for (int i = 2; i < 101; i++)
	{
		if (i % 2 != 0 && i % 3 != 0 && i % 4 != 0 && i % 5 != 0 && i % 6 != 0 && i % 7 != 0 && i % 8 != 0 && i % 9 != 0 && i % 10 != 0)
		{
			printf("%d\n", i);
		}
	}
}

