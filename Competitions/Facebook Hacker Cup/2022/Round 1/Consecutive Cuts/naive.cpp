#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e5; int n; lli k;
vector<int> a, b;
deque<int> aa;

bool valid(deque<int>& curr)
{
  int i = 0;
  for (int ai : curr)
    if (ai != b[i++])
      return false;
  return true;
}

bool possible(deque<int> curr = aa, int moves = k)
{
  if (moves == 0) return valid(curr);

  
  for (int i = 0; i < n - 1; ++i)
  {
    curr.push_back(curr[0]);
    curr.pop_front();
    if (possible(curr, moves - 1))
      return true;
  }
  return false;
}

int main()
{
  int testCases; scanf("%d", &testCases);
  for (int testCase = 1; testCase <= testCases; ++testCase)
  {
    scanf("%d %lld", &n, &k);
    a.clear(), b.clear();
    a.resize(n), b.resize(n);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    for (int i = 0; i < n; ++i) scanf("%d", &b[i]);
    aa.clear();
    for (int aaa : a) aa.push_back(aaa);

    bool can = possible();
    printf("Case #%d: %s\n", testCase, can ? "YES" : "NO");
  }
  return 0;
}
