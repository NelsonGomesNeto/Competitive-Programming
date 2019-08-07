#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isVogal(char a)
{
  a = tolower(a);
  return(a == 'a' || a == 'e' || a == 'i' || a == 'o' || a == 'u');
}

int main()
{
  char A[1000], B[1000];
  scanf("%s %s", A, B);
  int i, tamA = strlen(A), tamB = strlen(B);

  for (i = 0; i < tamA; i ++)
    if (A[i] >= 'A' && A[i] <= 'Z')
      tamB = -1;

  for (i = 0; i < tamB; i ++)
    if (B[i] >= 'A' && B[i] <= 'Z')
      tamA = -1;
      
  if (tamA != tamB)
    printf("ERRO\n");
  else
  {
    for (i = 0; i < tamA; i ++)
    {
      if (A[i] == B[i] && !isVogal(A[i]))
        printf("%d", i);
      else if (!(i & 1)) // not odd
        printf("%c", toupper(A[i]));
      else
        printf("!!");
    }
    printf("\n");
  }
  return(0);
}
