#include <stdio.h>
#include <stdlib.h>

int ans[110], strin[110];

int check(char str[][110], int fim)
{
  int i;
  for (i = 0; i < fim; i ++)
  {
    int posi = ans[i], j;
    for (j = 0; strin[j] != '\0'; j ++)
    {
      if (str[posi][j] != strin[j])
      {
        return(0);
      }
    }
  }
  return(1);
}

void BT(char c[], char str[][110], int i, int fim)
{
  if (check(str, i) == 1)
  {

  }
  int j;
  for (j = 0; j < fim; j ++)
  {
    ans[i] = j;
    BT(c, str, i + 1, codes);
  }
}

int main()
{
  int codes;
  while (scanf("%d", &codes) != EOF)
  {
    char c[codes], str[codes][110];
    int i;
    for (i = 0; i < codes; i ++)
    {
      scanf("%c %[^\n]", &c[i], str[i]);
      getchar();
    }
    scanf("%[^\n]", string);
    BT(c, str, 0, codes);
  }
  return(0);
}
