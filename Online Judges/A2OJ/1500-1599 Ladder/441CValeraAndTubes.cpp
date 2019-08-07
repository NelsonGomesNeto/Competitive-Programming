#include <bits/stdc++.h>
using namespace std;

const int maxN = 3e2, maxM = 3e2, maxK = 9e4 / 2; int n, m, k;
vector<pair<int, int>> positionsPerColor[maxK];

int main()
{
  scanf("%d %d %d", &n, &m, &k);
  int pieces = n*m / k;
  int ii = 0, jj = 0;
  for (int i = 0; i < k; i ++)
    for (int j = 0; j < pieces || (i == k - 1 && ii < n); j ++)
    {
      positionsPerColor[i].push_back({ii, jj}); 
      jj += (ii & 1) ? -1 : 1;
      if (jj == m) ii ++, jj = m - 1;
      if (jj == -1) ii ++, jj = 0;
    }
  for (int i = 0; i < k; i ++)
  {
    printf("%d", (int) positionsPerColor[i].size());
    for (auto p: positionsPerColor[i]) printf(" %d %d", p.first + 1, p.second + 1);
    printf("\n");
  }

  return(0);
}