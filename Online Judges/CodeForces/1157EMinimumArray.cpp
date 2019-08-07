#include <bits/stdc++.h>
using namespace std;

const int maxN = 2e5; int n;
int a[maxN], b[maxN], c[maxN];
int bAmount[maxN];
set<int> bHas;

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++) scanf("%d", &a[i]);
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &b[i]);
    bAmount[b[i]] ++;
  }
  for (int i = 0; i < n; i ++)
    if (bAmount[i])
      bHas.insert(i);

  for (int i = 0; i < n; i ++)
  {
    auto it = bHas.lower_bound((n - a[i]) % n);
    if (it == bHas.end()) it --;
    vector<set<int>::iterator> toTry;
    toTry.push_back(bHas.begin());
    toTry.push_back(--bHas.end());
    if (it != --bHas.end()) toTry.push_back(it);
    if (it != bHas.begin()) toTry.push_back(--it);
    if (it != --(--bHas.end())) toTry.push_back(++(++it));
    set<int>::iterator best;
    c[i] = n;
    for (auto t: toTry)
    {
      if ((a[i] + *t) % n < c[i])
        c[i] = (a[i] + *t) % n, best = t;
    }
    bAmount[*best] --;
    if (!bAmount[*best]) bHas.erase(best);
  }
  for (int i = 0; i < n; i ++)
    printf("%d ", c[i]);
  printf("\n");

  return(0);
}