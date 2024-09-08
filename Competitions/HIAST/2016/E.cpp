#include <bits/stdc++.h>
using namespace std;
char s[(int) 1e5 + 1];

void printNumber(stack<char> a)
{
  vector<char> ans;
  while (!a.empty())
  {
    ans.push_back(a.top()); a.pop();
  }
  reverse(ans.begin(), ans.end());
  for (auto c: ans) printf("%c", c);
  printf("\n");
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    int toRemove; scanf("\n%s %d", s, &toRemove);
    stack<char> small, big;

    int k = toRemove, kk = toRemove;
    for (int i = 0; s[i]; i ++)
    {
      while (k && !small.empty() && small.top() > s[i]) k --, small.pop();
      while (kk && !big.empty() && big.top() < s[i]) kk --, big.pop();
      small.push(s[i]), big.push(s[i]);
    }
    while (k) k --, small.pop();
    while (kk) kk --, big.pop();

    printNumber(small); printNumber(big);
  }
  return(0);
}
