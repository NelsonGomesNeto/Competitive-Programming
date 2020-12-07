#include <bits/stdc++.h>
using namespace std;

int letters[256];

int main()
{
  int n; scanf("%d", &n);
  for (int i = 0; i < n; i ++)
  {
    char name[21]; scanf(" %s", name);
    letters[name[0]] ++;
  }

  int x = 0;
  for (int i = 0; i < 256; i ++)
  {
    int a = (letters[i] >> 1), b = (letters[i] >> 1) + (letters[i] & 1);
    x += a * (a - 1) / 2;
    x += b * (b - 1) / 2;
  }

  printf("%d\n", x);

  return(0);
}
