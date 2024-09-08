#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 10; int n, m, s, f;
char ss[maxN + 1];
string in, out;

struct Node
{
  string curr; int d, h;
  Node(string &s, int d) : curr(s), d(d)
  {
    h = 0;
    for (int i = 0; i < s.size(); i++)
      h += s[i] != out[i];
  }
  bool operator<(const Node &other) const
  {
    return d + h < other.d + other.h;
  }
};

int astar()
{
  priority_queue<Node> pq;
  pq.push(Node(in, 0));

  while (!pq.empty())
  {
    Node u = pq.top(); pq.pop();

    // flips
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
      {
        char aux = u.curr[i*m + j];
        u.curr[i*m + j] = aux == 'G' ? 'M' : 'G';
        pq.push(Node(u.curr, u.d + f));
      }
  }
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d %d %d", &n, &m, &s, &f);
    in = "";
    for (int i = 0; i < n; i++)
    {
      scanf(" %s", ss);
      in += string(ss);
    }
    out = "";
    for (int i = 0; i < n; i++)
    {
      scanf(" %s", ss);
      out += string(ss);
    }

    int ans = astar();

    printf("Case #%d: %d\n", tt, ans);
  }
  return 0;
}