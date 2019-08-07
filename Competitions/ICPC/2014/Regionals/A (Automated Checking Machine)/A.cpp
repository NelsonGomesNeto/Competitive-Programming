#include <bits/stdc++.h>
#define lli long long int
using namespace std;

void read(int a[])
{
  for (int i = 0; i < 5; i ++)
    scanf("%d", &a[i]);
}

int main()
{
  int x[5], y[5];
  read(x); read(y);
  bool can = true;
  for (int i = 0; i < 5; i ++)
    if (x[i] != !y[i])
      can = false;
  printf("%c\n", can ? 'Y' : 'N');
  return(0);
}