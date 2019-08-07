#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
  int n; cin >> n;
  vector< pair<int, int> > a;
  int i, j, k;
  for (i = 0; i < n; i ++)
  {
    scanf("%d %d", &j, &k);
    a.push_back(make_pair(k, j));
  }

  sort(a.begin(), a.end());

  k = 1;
  for (i = 1, j = 0; i < n; i ++)
  {
    if (a[i].second >= a[j].first)
    {
      j = i;
      k ++;
    }
    //printf("%d %d\n", a[i].first, a[i].second);
  }

  printf("%d\n", k);

  return(0);
}
