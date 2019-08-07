#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void converttoall(int num, int base, char fim[], int i)
{
  if (num == 0)
  {
    return;
  }
  fim[i] = (num % base) + 48;
  if (fim[i] > '9')
  {
    fim[i] += 7;
  }
  converttoall(num / base, base, fim, i + 1);
}

int main()
{
  int testes; scanf("%d", &testes);
  while (testes > 0)
  {
    int num, base;
    scanf("%d %d", &num, &base);
    char fim[999999];
    strcpy(fim, "\0");
    converttoall(num, base, fim, 0);
    int i;
    for (i = strlen(fim) - 1; i >= 0; i --)
    {
      printf("%c", fim[i]);
      fim[i] = '\0';
    } printf("\n");
    testes --;
  }
  return(0);
}
