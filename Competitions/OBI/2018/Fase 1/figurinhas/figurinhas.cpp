#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n, c, m; scanf("%d %d %d", &n, &c, &m);
  set<int> rare; int k;
  for (int i = 0; i < c; i ++)
  {
    scanf("%d", &k);
    rare.insert(k);
  }
  set<int> bought;
  for (int i = 0; i < m; i ++)
  {
    scanf("%d", &k);
    bought.insert(k);
  }
  int missing = 0;
  for (auto f: rare)
    missing += (bought.count(f) == 0);
  printf("%d\n", missing);
  return(0);
}
