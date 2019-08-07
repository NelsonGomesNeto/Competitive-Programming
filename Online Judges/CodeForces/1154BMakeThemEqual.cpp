#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  set<int> diffValues;
  int a[n];
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &a[i]);
    diffValues.insert(a[i]);
  }

  if (diffValues.size() == 1) printf("0\n");
  else if (diffValues.size() > 3) printf("-1\n");
  else if (diffValues.size() == 2) printf("%d\n", !(((*(++diffValues.begin())) - (*diffValues.begin())) & 1) ? ((*(++diffValues.begin())) - (*diffValues.begin())) >> 1 : ((*(++diffValues.begin())) - (*diffValues.begin())));
  else
  {
    if ((*(++diffValues.begin())) - (*diffValues.begin()) == (*(--diffValues.end())) - (*(++diffValues.begin())) ) printf("%d\n", (*(++diffValues.begin())) - (*diffValues.begin()));
    else printf("-1\n");
  }
  return(0);
}