#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
1 query to discover the biggest
binary search to find it's position
*/

int query(int lo, int hi)
{
  printf("? %d", hi - lo + 1);
  for (int i = lo; i <= hi; i++) printf(" %d", i);
  printf("\n"); fflush(stdout);

  int value; scanf("%d", &value);
  return value;
}

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    int n, k; scanf("%d %d", &n, &k);
    set<int> s[k];
    for (int i = 0; i < k; i++)
    {
      int c; scanf("%d", &c);
      for (int j = 0; j < c; j++)
      {
        int ss; scanf("%d", &ss);
        s[i].insert(ss);
      }
    }

    int biggest = query(1, n);

    int lo = 1, hi = n;
    while (lo < hi)
    {
      int mid = (lo + hi) >> 1;
      int emid = query(lo, mid);
      if (emid == biggest) hi = mid;
      else lo = mid + 1;
    }
    int biggestPos = lo;

    int password[k]; list<int> missings;
    for (int i = 0; i < k; i++)
    {
      if (!s[i].count(biggestPos)) password[i] = biggest;
      else missings.push_back(i);
    }

    for (int missing: missings)
    {
      int kk = 0;
      for (int i = 1; i <= n; i++) if (!s[missing].count(i)) kk++;
      printf("? %d", kk);
      for (int i = 1; i <= n; i++) if (!s[missing].count(i)) printf(" %d", i);
      printf("\n"); fflush(stdout);
      int value; scanf("%d", &value);
      password[missing] = value;
    }

    printf("!");
    for (int i = 0; i < k; i++) printf(" %d", password[i]);
    printf("\n"); fflush(stdout);

    char verdict[15]; scanf(" %s", verdict);
  }
  return 0;
}
