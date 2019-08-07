#include <stdio.h>
#include <string.h>

int main()
{
  int array[100][10000], i[100], j = 0;
  char oper[5];
  while (scanf("%s", oper) != EOF)
  {
    getchar();
    if (strcmp(oper,"PUSH") == 0)
    {
      char s;
      while (scanf("%d%c", &array[j][i[j]], &s) && s == ' ')
      {
        i[j] ++;
      }
      j ++;
    }
    else
    {
      j --;
      if (j < 0)
      {
        j = 0;
        printf("EMPTY STACK\n");
        continue;
      }
      int x;
      for (x = 0; x < i[j]; x ++)
      {
        printf("%d ", array[j][x]);
      } printf("%d\n", array[j][x]);
      i[j] = 0;
    }
  }
  return(0);
}
