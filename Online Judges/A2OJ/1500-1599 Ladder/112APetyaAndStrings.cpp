#include <bits/stdc++.h>
using namespace std;

void lowerCase(char a[])
{
  for (int i = 0; a[i]; i ++) a[i] = tolower(a[i]);
}

int main()
{
  char a[101], b[101];
  scanf("%s\n%s", a, b);
  lowerCase(a); lowerCase(b);

  int res = strcmp(a, b);
  if (res < 0) printf("-1\n");
  else if (res == 0) printf("0\n");
  else printf("1\n");

  return(0);
}