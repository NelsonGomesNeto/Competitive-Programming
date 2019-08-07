#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n, t = 0; scanf("%d", &n);
  while (t < n)
  {
    if (t) printf("\n");

    map<string, int> tree; string bug;
    int trees = 0;
    while (getline(cin, bug) && bug.size())
    {
      trees ++;
      if (!tree.count(bug))
        tree[bug] = 1;
      else
        tree[bug] ++;
    }

    for (auto i: tree)
    {
      string s = i.first; double percent = 100 * (double) i.second / trees;
      cout << s; printf(" %.4lf\n", percent);
    }

    if (trees) t ++;
  }
  return(0);
}