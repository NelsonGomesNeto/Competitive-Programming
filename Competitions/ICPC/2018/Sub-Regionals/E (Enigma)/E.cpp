#include <bits/stdc++.h>

int main()
{
  char encrypted[(int) 1e4 + 1], crib[(int) 1e4 + 1];
  scanf("%s\n%s", encrypted, crib);
  int encSize = strlen(encrypted), cribSize = strlen(crib);
  int possible = encSize - cribSize + 1;
  for (int i = 0; i < encSize - cribSize + 1; i ++)
    for (int j = 0; crib[j]; j ++)
      if (encrypted[i + j] == crib[j])
      {
        possible --;
        break;
      }
  printf("%d\n", possible);
  return(0);
}
