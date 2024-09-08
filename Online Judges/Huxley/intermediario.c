#include <stdio.h>

int main()
{
  int n1, n2, n3;
  scanf("%i\n%i\n%i", &n1, &n2, &n3);
  if (n1 >= n2 && n1 >= n3)
  {
  	if (n2 >= n3)
  		printf("%i\n", n2);
  	else
  		printf("%i\n", n3);
  }
  else if (n2 >= n1 && n2 >= n3)
  	if (n1 >= n3)
  		printf("%i\n", n1);
  	else
  		printf("%i\n", n3);
  else
  	if (n1 >= n2)
  		printf("%i\n", n1);
  	else
  		printf("%i\n", n2);
  return(0);
}
