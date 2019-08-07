#include <bits/stdc++.h>
using namespace std;

void read(int a[])
{
  for (int i = 0; i < 3; i ++) scanf("%d", &a[i]);
}

int main()
{
  int a[3], b[3]; read(a); read(b);
  printf("%d\n", max(b[2] - a[2], 0) + max(b[1] - a[1], 0) + max(b[0] - a[0], 0));
  return(0);
}
