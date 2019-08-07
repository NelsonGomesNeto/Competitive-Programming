#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 2e5; int n;
struct Box
{
  lli a[3];
  bool operator<(const Box &b) const { return(a[0] < b.a[0] || (a[0] == b.a[0] && a[1] < b.a[1]) || (a[0] == b.a[0] && a[1] == b.a[1] && a[2] < b.a[2])); }
};
Box boxes[maxN + 1];
int permutations[6][3] = {{0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 1, 0}, {2, 0, 1}};
bool invalid(int i, int p)
{
  for (int k = 0; k < 3; k ++)
    if (boxes[i].a[k] >= boxes[i - 1].a[permutations[p][k]])
      return(true);
  return(false);
}

int memo[maxN][6];
bool solve(int i, int p)
{
  if (i == n) return(true);
  if (invalid(i, p)) return(false);
  if (memo[i][p] == -1)
  {
    bool ans = false;
    for (int k = 0; k < 6 && !ans; k ++)
      ans = solve(i + 1, p);
    memo[i][p] = ans;
  }
  return(memo[i][p]);
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++) scanf("%lld %lld %lld", &boxes[i].a[0], &boxes[i].a[1], &boxes[i].a[2]);
  sort(boxes, boxes+n); reverse(boxes, boxes+n);

  memset(memo, -1, sizeof(memo));
  bool can = false;
  for (int i = 0; i < 6 && !can; i ++)
    can = solve(1, i);
  printf("%c\n", can ? 'S' : 'N');

  return(0);
}