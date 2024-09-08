#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6; int n, k;
char ss[maxN + 1];
string a, b;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &k);
    scanf(" %s", ss); a = string(ss);
    scanf(" %s", ss); b = string(ss);

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    priority_queue<char, vector<char>, greater<char>> pq;
    for (int i = 0; i < n; i++)
      pq.push(a[i]);

    bool can = true;
    for (int i = 0; !pq.empty() && can; i++)
    {
      DEBUG printf("\t%d - %s - %s\n", i, a.c_str(), b.c_str());
      while (i < n && pq.top() == b[i]) i++, pq.pop();

      if (i == n) break;

      if (i + k - 1 >= n) can = false;
      else
      {
        int delta = b[i] - pq.top();
        vector<char> lol;
        for (int j = 0; j < k; j++)
        {
          lol.push_back(pq.top());
          pq.pop();
        }

        if (lol[0] == lol[k - 1] && delta >= 0)
        {
          for (int j = 0; j < k; j++)
            if (lol[j] + delta > b[i + j])
              can = false;

          if (can)
          {
            for (int j = 0; j < k; j++)
            {
              lol[j] += delta;
              pq.push(lol[j]);
            }
            i--;
          }
        }
        else
          can = false;
      }
    }
    printf("%s\n", can ? "YES" : "NO");
  }
  return 0;
}
