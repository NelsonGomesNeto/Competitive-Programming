#include <bits/stdc++.h>

int main()
{
  int k, n, s, p; scanf("%d %d %d %d", &k, &n, &s, &p);
  double sheetPerPerson = ceil((double) n / s);
  int totalSheet = ceil(k * sheetPerPerson);
  printf("%d\n", (int) ceil((double) totalSheet / p));
  return(0);
}