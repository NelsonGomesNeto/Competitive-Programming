#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  int pos = 2, iterations = 1;
  while (pos != 1)
  {
    if (pos <= (n >> 1)) pos += pos;
    else if (pos > (n >> 1)) pos -= n - pos + 1;
    iterations ++;
  }
  printf("%d\n", iterations);
  return(0);
}