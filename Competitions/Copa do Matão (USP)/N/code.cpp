#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100, maxW = 1e4; int n, k, L;
struct Person
{
  int c, w, v;
  void read() { scanf("%d %d", &c, &w); }
};
Person people[maxN];
struct Item
{
  int w, v;
  void read() { scanf("%d %d", &w, &v); }
};
Item items[maxN];

int memop[maxN][maxW + 1];
int solvep(int c, int i = 0)
{
  if (i == k) return 0;
  int &ans = memop[i][c];
  if (ans != -1) return ans;
  ans = solvep(c, i + 1);
  if (items[i].w <= c) ans = max(ans, solvep(c - items[i].w, i + 1) + items[i].v);
  return ans;
}

int memoe[maxN][maxW + 1];
int solvee(int c, int i = 0)
{
  if (i == k) return 0;
  int &ans = memoe[i][c];
  if (ans != -1) return ans;
  ans = solvee(c, i + 1);
  if (people[i].w <= c) ans = max(ans, solvee(c - people[i].w, i + 1) + people[i].v);
  return ans;
}

int main()
{
  while (~scanf("%d %d %d", &n, &k, &L))
  {
    for (int i = 0; i < n; i++) people[i].read();
    for (int i = 0; i < k; i++) items[i].read();

    for (int i = 0; i < n; i++)
    {
      memset(memop, -1, sizeof(memop));
      people[i].v = solvep(people[i].c);
    }

    memset(memoe, -1, sizeof(memoe));
    lli ans = solvee(L);
    printf("%lld\n", ans);
  }
  return 0;
}