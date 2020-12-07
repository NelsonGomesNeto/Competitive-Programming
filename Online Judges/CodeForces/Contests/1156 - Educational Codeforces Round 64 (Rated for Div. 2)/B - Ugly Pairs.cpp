#include <bits/stdc++.h>
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    char s[101], seven[101], sodd[101];
    memset(s, '\0', sizeof(s)), memset(seven, '\0', sizeof(seven)), memset(sodd, '\0', sizeof(sodd));
    scanf(" %s", s);
    int sevenSize = 0, soddSize = 0;
    for (int i = 0; s[i]; i ++)
      if (s[i] & 1) seven[sevenSize ++] = s[i];
      else sodd[soddSize ++] = s[i];
    sort(seven, seven + sevenSize), sort(sodd, sodd + soddSize);

    if (abs(seven[sevenSize - 1] - sodd[0]) > 1)
      printf("%s%s\n", seven, sodd);
    else if (abs(sodd[soddSize - 1] - seven[0]) > 1)
      printf("%s%s\n", sodd, seven);
    else
      printf("No answer\n");
  }
  return(0);
}