#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5; int n; lli k;
struct Costumer
{
  int id; lli entrance, d, finalized; char chef;
  bool operator<(const Costumer &c) const { return(entrance < c.entrance || (entrance == c.entrance && id < c.id)); }
  void print()
  {
    printf("%d %lld %lld %lld %c\n", id, entrance, d, finalized, chef);
  }
};
Costumer costumers[maxN], ans[maxN];

queue<pair<lli, int>> A, B;
lli Atime, Btime;
void solve()
{
  Atime = Btime = 0;
  for (int i = 0; i < n; i ++)
  {
    while (!A.empty() && max(Atime, costumers[A.front().second].entrance) + A.front().first <= costumers[i].entrance)
    {
      Atime = costumers[A.front().second].finalized = max(Atime, costumers[A.front().second].entrance) + A.front().first, costumers[A.front().second].chef = 'A';
      A.pop();
    }
    while (!B.empty() && max(Btime, costumers[B.front().second].entrance) + B.front().first <= costumers[i].entrance)
    {
      Btime = costumers[B.front().second].finalized = max(Btime, costumers[B.front().second].entrance) + B.front().first, costumers[B.front().second].chef = 'B';
      B.pop();
    }
    // printf("%lld %lld %d %d\n", Atime, Btime, (int) A.size(), (int) B.size());
    if (A.size() <= B.size()) A.push({costumers[i].d, i});
    else B.push({k*costumers[i].d, i});
  }
  while (!A.empty())
  {
    Atime = costumers[A.front().second].finalized = max(Atime, costumers[A.front().second].entrance) + A.front().first, costumers[A.front().second].chef = 'A';
    A.pop();
  }
  while (!B.empty())
  {
    Btime = costumers[B.front().second].finalized = max(Btime, costumers[B.front().second].entrance) + B.front().first, costumers[B.front().second].chef = 'B';
    B.pop();
  }
}

int main()
{
  scanf("%d %lld", &n, &k);
  for (int i = 0; i < n; i ++)
  {
    costumers[i].id = i;
    scanf("%lld %lld", &costumers[i].entrance, &costumers[i].d);
  }
  sort(costumers, costumers+n);

  solve();

  for (int i = 0; i < n; i ++) ans[costumers[i].id] = costumers[i];
  for (int i = 0; i < n; i ++) printf("%c %lld\n", ans[i].chef, ans[i].finalized);

  return(0);
}