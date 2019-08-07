#include <stdio.h>
#include <string.h>

int main()
{
  long long int A, B; char string[1000000];
  scanf("%Ld %Ld", &A, &B); getchar();
  scanf("%s", string);
  long long int pots = 0; int i;
  for (i = 0; string[i] != '\0'; i ++)
  {
    if (string[i] == '1')
    {
      pots += A;
      pots %= B;
    }
    A = ((A % B) * (A % B)) % B;
  }
  printf("%Ld\n", pots);
  return(0);
}
