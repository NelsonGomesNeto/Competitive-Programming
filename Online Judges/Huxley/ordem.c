#include <stdio.h>
//Decrescente
int main()
{
	int n1, n2, n3;
	scanf("%d\n%d\n%d", &n1, &n2, &n3);
	if (n1 >= n2 && n1 >= n3)
	{
		if (n2 >= n3)
			printf("%d\n%d\n%d\n", n1, n2, n3);
		else
			printf("%d\n%d\n%d\n", n1, n3, n2);
	}
	else if (n2 >= n1 && n2 >= n3)
		if (n1 >= n3)
			printf("%d\n%d\n%d\n", n2, n1, n3);
		else
			printf("%d\n%d\n%d\n", n2, n3, n1);
	else
		if (n1 >= n2)
			printf("%d\n%d\n%d\n", n3, n1, n2);
		else
			printf("%d\n%d\n%d\n", n3, n2, n1);
	return(0);
}
/*Crescente
if (n1 >= n2 && n1 >= n3)
{
	if (n2 >= n3)
		printf("%d\n%d\n%d\n", n3, n2, n1);
	else
		printf("%d\n%d\n%d\n", n2, n3, n1);
}
else if (n2 >= n1 && n2 >= n3)
	if (n1 >= n3)
		printf("%d\n%d\n%d\n", n3, n1, n2);
	else
		printf("%d\n%d\n%d\n", n1, n3, n2);
else
	if (n1 >= n2)
		printf("%d\n%d\n%d\n", n2, n1, n3);
	else
		printf("%d\n%d\n%d\n", n1, n2, n3);
return(0);
}
*/
