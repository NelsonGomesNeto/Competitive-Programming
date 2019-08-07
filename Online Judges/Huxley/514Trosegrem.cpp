#include <bits/stdc++.h>
#define lli long long int
using namespace std;

struct Slices { int start, end; };

void printArray(int size, lli array[], int parts)
{
  // for (int i = 0; i < size; i ++)
}

int main()
{
  lli n, x0, a, c, m;
  while (scanf("%lld %lld %lld %lld %lld", &n, &x0, &a, &c, &m) != EOF)
  {
    lli array[n]; array[0] = x0;
    for (int i = 1; i < n; i ++) array[i] = (a * array[i - 1] + c) % m;

    for (int parts = ceil((double) n / 2); parts > 0; parts --)
    {
      printArray(n, array, parts);
    }
  }
  return(0);
}