#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  pair<int, int> laptop[n];
  for (int i = 0; i < n; i ++)
    scanf("%d %d", &laptop[i].first, &laptop[i].second);
  sort(laptop, laptop+n);

  int happy = 0;
  for (int i = 0; i < n - 1; i ++)
    if (laptop[i].first < laptop[i + 1].first && laptop[i].second > laptop[i + 1].second)
      happy = 1;

  printf("%s\n", happy ? "Happy Alex" : "Poor Alex");

  return(0);
}