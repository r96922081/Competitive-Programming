#include "stdio.h"
#include "stdlib.h"

int main()
{
	int tc = 0;
	int a, b;
	scanf("%d", &tc);
	
	while (tc--)
	{
		scanf("%d %d", &a, &b);
		if (a > b)
			printf(">\n");
		else if (a < b)
			printf("<\n");
		else
			printf("=\n");
	}
}