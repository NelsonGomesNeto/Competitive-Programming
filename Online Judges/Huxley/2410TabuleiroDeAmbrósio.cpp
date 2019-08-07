#include <stdio.h>

int main()
{
	int n, pos = 1, plays; scanf("%d", &n);
	for (plays = 0; pos != n; plays ++)
	{
		pos += (plays % 6 + 1);
		if (pos > n) pos = pos % n;
	}
	printf("%d\n", plays);
	return(0);
}