#include <stdio.h>
#include <string.h>

int main()
{
  char frase1[99], frase2[99];
  scanf("%[^\n]", frase1);
  getchar();
  scanf("%[^\n]", frase2);
  strcat(frase1,frase2);
  printf("%s\n", frase1);
  return(0);
}
