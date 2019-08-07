#include <bits/stdc++.h>

int main()
{
  int d; char n[101];
  while (scanf("%d %s", &d, n) && !(d == 0 && !strcmp(n, "0")))
  {
    getchar();

    int firstDigit = 1;
    for (int i = 0; n[i]; i ++)
    {
      if (n[i] == '0' && !firstDigit)
        printf("0");
      else if (n[i] - '0' != d && n[i] != '0')
      {
        printf("%c", n[i]);
        firstDigit = 0;
      }
    }
    printf("%s\n", firstDigit ? "0" : "\0");
  }

  return(0);
}