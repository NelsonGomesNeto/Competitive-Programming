#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Tutorial:
  When p and q disagree, you've got to find the size of this disagreement
  To do that, you will iterate through p and q and maintain a set for each one:
    if pSet is holding q[i]: remove q[i] from pSet
    else: qSet will hold q[i] (so when p[i] == q[i] happens, it will remove from qSet)
    if qSet is holding p[i]: remove p[i] from qSet
    else: pSet will hold p[i] (so when q[i] == p[i] happens, it will remove from pSet)

    if pSet and qSet are empty: there's no current disagreement
*/

const int maxN = 2e5; int n, k, letter;
int p[maxN], q[maxN], charCnt[256];
char s[maxN + 1];
vector<int> blockEnds;
set<int> pSet, qSet;

int main()
{
  scanf("%d %d", &n, &k);
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &p[i]);
    p[i] --;
  }
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &q[i]);
    q[i] --;
  }

  for (int i = 0; i < n; i ++)
  {
    if (pSet.count(q[i])) pSet.erase(q[i]);
    else qSet.insert(q[i]);
    if (qSet.count(p[i])) qSet.erase(p[i]);
    else pSet.insert(p[i]);

    if (pSet.empty() && qSet.empty())
      blockEnds.push_back(i);
  }

  if (blockEnds.size() < k) printf("NO\n");
  else
  {
    int lo = 0; char letter = 'a';
    for (int hi: blockEnds)
    {
      for (; lo <= hi; lo ++)
        s[p[lo]] = letter;
      letter = letter < 'z' ? letter + 1 : letter;
    }
    printf("YES\n%s\n", s);
  }

  return(0);
}