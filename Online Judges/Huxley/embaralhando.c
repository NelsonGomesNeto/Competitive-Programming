#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define lli long long int

lli fat(lli pd[], int n)
{
  if (n <= 1) return(1);
  if (pd[n] == 0)
    pd[n] = n * fat(pd, n - 1);
  return(pd[n]);
}

int main()
{
  char work[16]; lli *DP = calloc(16, sizeof(lli));
  while (scanf("%s", work) != EOF && !(work[0] == '0' && strlen(work) == 1))
  {
    lli anagramas = fat(DP, strlen(work));
    printf("%Ld\n", anagramas);
    getchar();
  }
  return(0);
}
