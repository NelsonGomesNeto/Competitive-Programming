#include <bits/stdc++.h>
using namespace std;

int binSearch(vector<int>& a, int lo, int hi, int target)
{
  if (lo >= hi) return(lo == a.size() ? -1 : a[lo]);
  int mid = (lo + hi) >> 1;
  if (a[mid] >= target) return(binSearch(a, lo, mid, target));
  return(binSearch(a, mid + 1, hi, target));
}

int main()
{
  vector<int> letter[256];
  char s[(int) 2e5 + 1]; scanf("%s", s);
  for (int i = 0; s[i]; i ++) letter[s[i]].push_back(i);

  int q; scanf("%d", &q);
  char op[5];
  stack<pair<int, int> > now;
  while (q --)
  {
    scanf("\n%s", op);
    if (!strcmp(op, "push"))
    {
      char toAdd; scanf(" %c", &toAdd);
      int at;
      if (now.empty()) at = 0;
      else at = now.top().second + 1;

      int pos = binSearch(letter[toAdd], 0, letter[toAdd].size(), at);
      int before = now.empty() ? 1 : now.top().first;
      if (pos == -1) now.push({0, pos});
      else now.push({before, pos});
      printf("%s\n", (pos == -1 || !before) ? "NO" : "YES");
    }
    else
    {
      now.pop();
      printf("%s\n", (now.empty() || now.top().first) ? "YES" : "NO");
    }
  }
  return(0);
}