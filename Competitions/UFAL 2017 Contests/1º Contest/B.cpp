#include <bits/stdc++.h>
#define DEBUG if(1)
int n, k, array[(int) 1e5], groups[(int) 1e5], q = -1e9 - 1;

void createGroup()
{
  groups[0] = array[0];
  for (int j = 1, i = !(k - 1) ? 1 : (k - 1); i < n; j ++, i ++)
    groups[j] = array[i];
}

int strToInt(char num[])
{
  int i, n = 0, pot = 1;
  for (i = 0; num[i]; i ++); i --;
  while (i >= 0)
  {
    if (i == 0 && num[i] == '-')
      n *= -1;
    else
      n += (num[i] - '0') * pot;
    pot *=  10;
    i --;
  }
  return(n);
}

int main()
{
  scanf("%d %d", &n, &k);
  char num[100];
  for (int i = 0; i < n; i ++)
  {
    getchar();
    scanf("%s", num);
    if (num[0] == '?') array[i] = q;
    else array[i] = strToInt(num);
  }
  createGroup();

  DEBUG for (int i = 0; i < n; i ++)
  {
    if (groups[i] == q) printf("? ");
    else printf("%d ", groups[i]);
  } DEBUG printf("\n");

  for (int i = -10; i < 11; i ++)
  ;//  printf("(%d, %d)\n", i, evaluate(i));

  return(0);
}