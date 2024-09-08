#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5;
int a[maxN + 2];
int n;
int ans = -1;
int queries = 0;
int query(int idx)
{
  if (a[idx] != -1)
    return a[idx];
  queries++;
  assert(queries <= 100);

  printf("? %d\n", idx); fflush(stdout);
  scanf("%d", &a[idx]);
  return a[idx];
}
void find()
{
  int idx = 1 + rand() % n;
  for (int i = 0; i < 50; i++)
  {
    int a = query(idx), b = query(idx - 1), c = query(idx + 1);
    if (a < min(b, c))
    {
      ans = idx;
      break;
    }
    if (b < a && b < c)
      idx--;
    else
      idx++;
  }
}

int main()
{
  srand(time(NULL));

  while (~scanf("%d", &n))
  {
    queries = 0;
    memset(a, -1, sizeof(a));
    a[0] = a[n + 1] = 1e9;

    int lo = 1, hi = n;
    while (lo < hi)
    {
      int mid = (lo + hi) >> 1;
      int idx = mid;
      int a = query(idx), b = query(idx - 1), c = query(idx + 1);
      if (a < min(b, c))
      { 
        lo = mid;
        break;
      }
      if (a > b) hi = mid - 1;
      else lo = mid + 1;
    }
    printf("! %d\n", lo); fflush(stdout);

    break;
  }

  return 0;
}
