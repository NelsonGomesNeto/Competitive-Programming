#include <stdio.h>
#include <string.h>

int main()
{
  int printa; char stringA[999], stringB[999];
  scanf("%[^\n]", stringA);
  getchar(); scanf("%[^\n]", stringB);
  for (printa = strlen(stringB) - 1; printa >= 0; printa --)
  {
    printf("%c", stringB[printa]);
  }
  printf(" ");
  for (printa = strlen(stringA) - 1; printa >= 0; printa --)
  {
    printf("%c", stringA[printa]);
  }
  printf("\n");
  return(0);
}
