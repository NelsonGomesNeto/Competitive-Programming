#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e3; int n;
const int mid = 2*maxN;
char ss[maxN + 1];
string a, b, c;

/* Tutorial:
  O(n^3) easy:
    relative to a;
    try all positions for b O(n):
      try all positions for c O(n):
        check if it's valid O(n)

  What if we could check in O(1) :3? SOLVED
  We're going to precalculate something (in O(n^2)) to be able to check in O(1)

  I will show for a and b, but you'll need to do for ac and bc.
  Suppose b is shifted k from a[0]:
    Example for k = 0, 2 and -1 respectively
      aaaaaaa aaaaaaa   -aaaaaaa
      bbbbbb  ---bbbbbb bbbbbb  
  That shift is valid iff all aligned positions have a match.
  So we just need to fill something that will tell us that
  a given shift is valid. Make all valid, then for each shift:
  iterate through b, verifying if there's a aligned position
  that doesn't match, if so, mark that shift as invalid.
*/

bool ab[2*mid+1], ac[2*mid+1], bc[2*mid+1];
bool match(char ca, char cb)
{
  return ca == cb || ca == '?' || cb == '?';
}
void fillShitfs(string &s, string &t, bool shifts[])
{
  memset(shifts, true, sizeof(bool)*(2*mid+1));
  for (int i = 0; i < s.size(); i++)
    for (int j = 0; j < t.size(); j++)
      shifts[mid + (i - j)] &= match(s[i], t[j]);
  // This is a BEAUTIFUL way to implement the fill shifts
  // But you can simply do:
  // for (int i = -mid; i <= mid; i++)
  //   for (int j = 0; j < t.size(); j++)
  //     if (i + j >= 0 && i + j < s.size())
  //       shifts[mid + i] &= match(s[i + j], t[j])
}

int main()
{
  while (scanf(" %s", ss) != EOF)
  {
    a = string(ss);
    scanf(" %s", ss); b = string(ss);
    scanf(" %s", ss); c = string(ss);
    DEBUG printf("%s - %s - %s\n", a.c_str(), b.c_str(), c.c_str());

    fillShitfs(a, b, ab);
    fillShitfs(a, c, ac);
    fillShitfs(b, c, bc);

    int ans = 3*maxN;
    int aSize = a.size(), bSize = b.size(), cSize = c.size();
    for (int i = -mid; i <= mid; i++)
      for (int j = -mid; j <= mid; j++)
        if (ab[mid + i] && ac[mid + j] && bc[mid + (j - i)])
        {
          int left = max({-i, -j, 0});
          int right = max({(i + bSize) - aSize, (j + cSize) - aSize, 0});
          ans = min(ans, left + aSize + right);
        }
    printf("%d\n", ans);
  }
  return 0;
}