#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5;
int n;

void ask(char prefix, int i)
{
  printf("%c %d\n", prefix, i + 1);
  fflush(stdout);
}

bool isZero(int i)
{
  ask('?', i);
  int res;
  scanf("%d", &res);
  return res == 0;
}

int main()
{
  scanf("%d", &n);

  int lo = 0, hi = n - 1;
  while (lo < hi)
  {
    int mid = (lo + hi + 1) >> 1;
    if (isZero(mid)) lo = mid;
    else hi = mid - 1;
  }
  ask('!', lo);

  return 0;
}
