#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n, k, m, num;
  scanf("%d %d %d", &n, &k, &m);
  vector<int> mods[m];
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &num);
    mods[num % m].push_back(num);
  }

  int done = 0;
  for (int i = 0; i < m; i ++)
    if (mods[i].size() >= k)
    {
      printf("Yes\n");
      for (int j = 0; j < k; j ++)
        printf("%d%c", mods[i][j], j < k - 1 ? ' ' : '\n');
      done = 1;
      break;
    }
  if (!done) printf("No\n");

  return(0);
}