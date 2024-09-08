#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5;
int n, m;
int a[maxN];

int cnt[maxN];
bool has[maxN];

bool add(int i)
{
  return ++cnt[a[i]] == 1;
}
bool isRequired(int i)
{
  return cnt[a[i]] == 1;
}
void remove(int i)
{
  --cnt[a[i]];
}

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    for (int i = 0; i < n; ++i)
    {
      scanf("%d", &a[i]);
      --a[i];
    }

    memset(has, false, sizeof(has));
    memset(cnt, 0, sizeof(cnt));
    vector<int> ans;
    int current = 0;
    int start;
    for (int i = n - 1; i >= 0; --i)
    {
      current += add(i);
      if (current == m)
      {
        ans.push_back(a[0]), start = 0;
        for (int j = 0; j <= i; ++j)
          if (a[j] < ans.back())
            ans.back() = a[j], start = j;
        has[ans.back()] = true;
        remove(start);
        for (int j = start; j < i; ++j)
          add(j);
        break;
      }
    }

    while (ans.size() < m)
    {
      DEBUG {
        printf("%d %d - ", (int)ans.size(), start);
        for (int i = 0; i < ans.size(); ++i)
          printf("%d%c", ans[i] + 1, i + 1 < ans.size() ? ' ' : ' ');
        printf(" |");
        for (int i = 0; i < m; ++i) printf(" %d", cnt[i]);
        printf("\n");
      }
      int nxt = -1;
      for (int i = start + 1; i < n; ++i)
      {
        if (!has[a[i]] && isRequired(i))
        {
          DEBUG printf("\ttrying to add %d\n", a[i] + 1);
          ans.push_back(-2), nxt = start + 1;
          for (int j = start + 1; j <= i; ++j)
            if (!has[a[j]] && (ans.back() == -2 || a[j] < ans.back()))
              ans.back() = a[j], nxt = j;
          assert(ans.back() != -2);
          has[ans.back()] = true;
          if (nxt == i) remove(i);
          for (int j = nxt + 1; j < i; ++j)
            add(j);
          start = nxt;
          break;
        }
        remove(i);
      }
      assert(nxt != -1);
    }

    for (int i = 0; i < m; ++i)
      printf("%d%c", ans[i] + 1, i + 1 < m ? ' ' : '\n');
  }
  return 0;
}
