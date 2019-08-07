#include <bits/stdc++.h>

int main()
{
  int k; scanf("%d", &k); getchar();
  int letter[256]; char s; memset(letter, 0, sizeof(letter));
  while (scanf("%c", &s) && s != '\n') letter[s] ++;

  char kString[1001]; int can = 1, j = 0;
  for (int i = 0; i < 256; i ++)
  {
    if (letter[i] % k != 0) can = 0;
    int amount = letter[i] / k;
    while (amount --) kString[j ++] = i;
  } kString[j] = '\0';

  if (!can) printf("-1");
  else while (k --) printf("%s", kString);
  printf("\n");

  return(0);
}