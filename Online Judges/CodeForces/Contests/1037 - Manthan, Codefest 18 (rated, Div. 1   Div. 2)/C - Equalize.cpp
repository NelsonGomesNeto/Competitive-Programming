#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  char a[n + 1], b[n + 1]; scanf("\n%s\n%s", a, b);
  int cost = 0;
  for (int i = 0; i < n; i ++) cost += a[i] != b[i];
  for (int i = 0; i < n - 1; i ++)
    if (a[i] == b[i + 1] && a[i + 1] == b[i] && a[i] != b[i] && a[i + 1] != b[i + 1]) cost --, i ++;
  printf("%d\n", cost); 
  return(0);
}