#include <bits/stdc++.h>
using namespace std;

const int maxN = 18;
map<string, int> nameMap;
string revMap[maxN];
int infects[maxN];

int countOnes(int number)
{
  int s = 0;
  while (number)
  {
    s += number & 1;
    number >>= 1;
  }
  return(s);
}

int main()
{
  int n, m; scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i ++)
  {
    string a; cin >> a;
    nameMap[a] = nameMap.size();
    revMap[i] = a, infects[i] |= 1 << i;
  }

  for (int i = 0; i < m; i ++)
  {
    string a, b; cin >> a >> b;
    int u = nameMap[a], v = nameMap[b];
    infects[u] |= 1 << v, infects[v] |= 1 << u;
  }

  int ans = n, chosen = (1 << n) - 1;
  for (int i = 1, end = 1 << n; i < end; i ++)
  {
    int total = 0;
    for (int j = 0; j < n; j ++)
      if (i & (1 << j))
        total |= infects[j];
    int ones = countOnes(i);
    if (total == (1 << n) - 1 && ones < ans)
      ans = ones, chosen = i;
  }
  printf("%d\n", ans);
  for (int i = 0, done = 0; i < n; i ++)
    if (chosen & (1 << i))
    {
      if (done) printf(" ");
      cout << revMap[i], done = 1;
    }
  printf("\n");

  return(0);
}