#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 20, maxB = 15;
struct Tower
{
  lli value; int size, idx;
  bool operator<(const Tower &other) const { return size > other.size; }
};
Tower towers[maxN];
lli pot[maxB + 1];

int readDigit()
{
  int d; scanf("%d", &d);
  // assert(d >= 0 && d <= 9);
  return d;
}
void putOnTower(int i, int d)
{
  towers[i].value += pot[towers[i].size] * d;
  towers[i].size++;
  printf("%d\n", towers[i].idx); fflush(stdout);
}

int main()
{
  random_device rd;
  mt19937 e2(rd());
  uniform_real_distribution<> dist(0, 1);

  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine e(seed);

  pot[0] = 1;
  for (int i = 1; i <= maxB; i++)
    pot[i] = pot[i - 1] * 10;

  int t, n, b; lli p; scanf("%d %d %d %lld", &t, &n, &b, &p);
  for (int tt = 1; tt <= t; tt++)
  {
    for (int i = 0; i < n; i++)
      towers[i] = Tower{0, 0, i + 1};

    for (int i = n*b - 1; i >= 0; i--)
    {
      int d = readDigit();

      bool done = false;
      if (d >= 8)
      {
        for (int j = 0; j < n; j++)
          if (towers[j].size < b && towers[j].size == b - (9 - d + 1))
          {
            putOnTower(j, d);
            done = true;
            break;
          }

        if (!done)
        {
          int chosen = -1;
          for (int j = 0; j < n; j++)
            if (towers[j].size < b && towers[j].size <= b - (9 - d + 1) && (chosen == -1 || towers[j].size > towers[chosen].size))
              chosen = j;
          if (chosen != -1)
          {
            putOnTower(chosen, d);
            done = true;
          }
        }

        if (!done)
        {
          int chosen = -1;
          for (int j = 0; j < n; j++)
            if (towers[j].size < b && (chosen == -1 || towers[j].size > towers[chosen].size))
              chosen = j;
          if (chosen != -1)
          {
            putOnTower(chosen, d);
            done = true;
          }
        }
      }
      else
      {
        for (int db = 2; db >= 1 && !done; db--)
        {
          int chosen = -1;
          // for (int j = 0; j < n; j++)
          for (int j = n - 1; j >= 0; j--)
            if (towers[j].size < b && towers[j].size < b - db)
              chosen = j;
          if (chosen != -1)
          {
            putOnTower(chosen, d);
            done = true;
          }
        }

        if (!done)
        {
          int chosen = -1;
          // for (int j = 0; j < n; j++)
          for (int j = n - 1; j >= 0; j--)
            if (towers[j].size < b)
              chosen = j;
          if (chosen != -1)
          {
            putOnTower(chosen, d);
            done = true;
          }
        }
      }
    }

    for (int i = 0; i < n; i++)
      assert(towers[i].size == b);
  }
  int res; scanf("%d", &res);

  return 0;
}