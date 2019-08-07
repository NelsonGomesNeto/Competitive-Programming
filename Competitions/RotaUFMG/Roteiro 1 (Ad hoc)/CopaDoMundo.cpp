#include <bits/stdc++.h>
#define DEBUG if(0)

int main()
{
  int answer[16], a, b;
  for (int i = 15; i >= 1; i --)
  {
    scanf("%d %d", &a, &b);
    answer[i] = a > b;
  }

  int at = 1;
  for (int i = 0; i < 3; i ++)
  {
    DEBUG printf("%d %d %d\n", at, 16 - at, answer[at]);
    if (answer[at])
      at = 2*at + 1;
    else
      at = 2*at;
  }

  at = 15 - at;
  printf("%c\n", 'A' + (2 * at) + !answer[15 - at]);

  return(0);
}