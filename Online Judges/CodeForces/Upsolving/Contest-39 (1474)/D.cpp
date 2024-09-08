#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
lli a[maxN];
lli aux[maxN];

void reset()
{
  for (int i = 0; i < n; i++)
    a[i] = aux[i];
}
bool check()
{
  bool can = true;
  for (int i = 0; i < n; i++)
    can &= a[i] == 0;
  return can;
}

bool try1()
{
  reset();

  bool can = true, done = false;
  for (int i = 0, j = 0; i < n; i++)
  {
    if (!done && a[i] > a[i + 1])
      swap(a[i], a[i + 1]), done = true;

    if (a[i] > a[i + 1])
      can = false;
    int delta = min(a[i], a[i + 1]);
    a[i + 1] -= delta;
    a[i] -= delta;
  }
  return can & check();
}
bool try2()
{
  reset();

  bool can = true, done = false;
  for (int i = 0, j = 0; i < n; i++)
  {
    if (!done && a[i] > a[i + 1])
      swap(a[i], a[i + 1]), done = true;

    if (a[i] > a[i + 1])
      can = false;
    int delta = min(a[i], a[i + 1]);
    a[i + 1] -= delta;
    a[i] -= delta;
  }
  return can & check();
}
bool try3()
{
  reset();

  bool can = true, done = false;
  for (int i = 0, j = 0; i < n; i++)
  {
    if (!done && a[i] > a[i + 1] && i + 2 < n)
      swap(a[i + 1], a[i + 2]), done = true;

    if (a[i] > a[i + 1])
      can = false;
    int delta = min(a[i], a[i + 1]);
    a[i + 1] -= delta;
    a[i] -= delta;
  }
  return can & check();
}
bool try4()
{
  reset();

  bool can = true, done = false;
  for (int i = 0, j = 0; i < n; i++)
  {
    if (!done && a[i] > a[i + 1] && i + 2 < n)
      swap(a[i + 1], a[i + 2]), done = true;

    if (a[i] > a[i + 1])
      can = false;
    int delta = min(a[i], a[i + 1]);
    a[i + 1] -= delta;
    a[i] -= delta;
  }
  return can & check();
}
bool try5()
{
  reset();

  bool can = true, done = false;

  int i = 0;
  while (i + 1 < n && a[i + 1] <= a[i]) i++;
  if (i + 1 < n && a[i + 1] > a[i])
    swap(a[i + 1], a[i]), done = true;

  for (int i = 0, j = 0; i < n; i++)
  {
    if (!done && a[i] > a[i + 1])
      swap(a[i], a[i + 1]), done = true;

    if (a[i] > a[i + 1])
      can = false;
    int delta = min(a[i], a[i + 1]);
    a[i + 1] -= delta;
    a[i] -= delta;
  }
  return can & check();
}
bool try6()
{
  reset();

  bool can = true, done = false;

  int j = n - 1;
  while (j - 1 >= 0 && a[j - 1] <= a[j]) j--;
  if (j - 1 >= 0 && a[j - 1] > a[j])
    swap(a[j - 1], a[j]), done = true;

  for (int i = 0, j = 0; i < n; i++)
  {9999999999999999999999999999
    if (!done && a[i] > a[i + 1])
      swap(a[i], a[i + 1]), done = true;

    if (a[i] > a[i + 1])
      can = false;
    int delta = min(a[i], a[i + 1]);
    a[i + 1] -= delta;
    a[i] -= delta;
  }
  return can & check();
}
bool try7()
{
  reset();

  bool can = true, done = false;

  int bi = 0;
  for (int i = 0; i + 1 < n; i++)
    if (a[i] > a[bi])
      bi = i;
  swap(a[bi], a[bi + 1]), done = true;

  for (int i = 0, j = 0; i + 1 < n; i++)
  {
    if (a[i] > a[i + 1])
      can = false;
    int delta = min(a[i], a[i + 1]);
    a[i + 1] -= delta;
    a[i] -= delta;
  }
  return can & check();
}
bool try8()
{
  reset();

  bool can = true, done = false;

  int bi = 1;
  for (int i = 1; i < n; i++)
    if (a[i] > a[bi])
      bi = i;
  swap(a[bi], a[bi - 1]), done = true;

  for (int i = 0, j = 0; i + 1 < n; i++)
  {
    if (a[i] > a[i + 1])
      can = false;
    int delta = min(a[i], a[i + 1]);
    a[i + 1] -= delta;
    a[i] -= delta;
  }
  return can & check();
}
bool try9()
{
  reset();

  bool can = true, done = false;

  int bi = n - 2;
  for (int i = n - 2; i >= 0; i--)
    if (a[i] > a[bi])
      bi = i;
  swap(a[bi], a[bi + 1]), done = true;

  for (int i = 0, j = 0; i + 1 < n; i++)
  {
    if (a[i] > a[i + 1])
      can = false;
    int delta = min(a[i], a[i + 1]);
    a[i + 1] -= delta;
    a[i] -= delta;
  }
  return can & check();
}
bool try10()
{
  reset();

  bool can = true, done = false;

  int bi = n - 1;
  for (int i = n - 1; i > 0; i--)
    if (a[i] > a[bi])
      bi = i;
  swap(a[bi], a[bi - 1]), done = true;

  for (int i = 0, j = 0; i + 1 < n; i++)
  {
    if (a[i] > a[i + 1])
      can = false;
    int delta = min(a[i], a[i + 1]);
    a[i + 1] -= delta;
    a[i] -= delta;
  }
  return can & check();
}
bool hardTry()
{
  bool can = false;
  can |= try1();
  can |= try2();
  can |= try3();
  can |= try4();
  can |= try5();
  can |= try6();
  can |= try7();
  can |= try8();
  can |= try9();
  can |= try10();
  return can;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);
    for (int i = 0; i < n; i++)
      aux[i] = a[i];

    bool can = false;
    can |= hardTry();
    reverse(aux, aux+n);
    can |= hardTry();

    printf("%s\n", can ? "YES" : "NO");
  }
  return 0;
}