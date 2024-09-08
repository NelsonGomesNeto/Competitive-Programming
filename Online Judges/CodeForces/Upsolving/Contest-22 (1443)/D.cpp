#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e4; int n;
int a[maxN], aux[maxN];

void brute()
{
  int j = 0;
  while (j + 1 < n - 1 && a[j + 1] <= a[j]) j++;
  if (j + 1 < n - 1)
  {
    int prv = a[j + 1];
    for (int k = j + 1; k < n - 1 && a[k] == prv; k++)
      a[k] -= a[j];
  }
  for (int k = 0; k <= j; k++)
    a[k] = 0;
}

bool doit()
{
  bool can = true;
  brute();
  reverse(a, a+n);
  brute();
  for (int i = 0; i < n; i++)
    if (a[i] > 0)
      can = false;
  return can;
}

void wtf()
{
  int j = 0;
  while (j + 1 < n - 1 && a[j + 1] <= a[j]) j++;
  j++;
  while (j + 1 < n - 1 && a[j + 1] == a[j]) j++;
  DEBUG printf("\t%d %d\n", j, a[j]);

  if (j + 1 < n - 1)
  {
    int diff = a[j] - a[j + 1];
    for (int k = 0; k <= j; k++)
      diff = min(diff, a[k]);
    diff = max(diff, 0);
    for (int k = 0; k <= j; k++)
      a[k] -= diff;
  }
}
bool doit2()
{
  // return false;
  wtf();
  DEBUG
    for (int i = 0; i < n; i++)
      printf("%d%c", a[i], i < n - 1 ? ' ' : '\n');
  reverse(a, a+n);
  wtf();

  return doit();
}

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
    for (int tt = 0; tt < t; tt++)
    {
      scanf("%d", &n);
      for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
      DEBUG
      {
        printf("%d\n", tt + 1);
        for (int i = 0; i < n; i++)
          printf("%d%c", a[i], i < n - 1 ? ' ' : '\n');
      }

      if (n <= 2) printf("YES\n");
      else
      {
        bool lol1, lol2, lol3, can;

        for (int i = 0; i < n; i++)
          aux[i] = a[i];
        lol1 = doit();

        for (int i = 0; i < n; i++)
          a[i] = aux[i];
        lol2 = doit();

        for (int i = 0; i < n; i++)
          a[i] = aux[i];
        lol3 = doit2();

        can = lol1 || lol2 || lol3;
        DEBUG printf("\tcans: %d %d %d\n", lol1, lol2, lol3);

        printf("%s\n", can ? "YES" : "NO");
      }
    }
  return 0;
}