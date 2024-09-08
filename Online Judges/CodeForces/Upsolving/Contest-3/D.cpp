#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int n; lli u, v;
const int maxB = 60;
lli cnt[maxB];

bool has()
{
  for (int i = 0; i < maxB; i ++)
    if (cnt[i])
      return true;
  return false;
}

int main()
{
  while (scanf("%lld %lld", &u, &v) != EOF)
  {
    memset(cnt, 0, sizeof(cnt));
    bool cant = false;
    lli curr = v, maxCnt = 0;
    for (int i = maxB - 1; i >= 0; i --)
    {
      lli now = (1LL << i);
      lli k = curr / now;
      if (((u & now) >> i) != (k & 1LL))
        k = max(0LL, k - 1);
      for (int mm = 0; mm < maxB; mm ++)
        if (((u & now) >> i) != (k & 1LL))
        {
          if (i < maxB - 1)
          {
            for (int j = i + 1; j < maxB; j ++)
              if (cnt[j] >= 2)
              {
                cnt[j] -= 2;
                curr += (1LL << j)*2LL;
                break;
              }
            k = curr / now;
            if (((u & now) >> i) != (k & 1LL))
              k = max(0LL, k - 1);
          }
        }
      cnt[i] = k;
      maxCnt = max(maxCnt, cnt[i]);

      curr -= k * now;
      if (curr < 0) { cant = true; break; }
      DEBUG printf("\t%d %lld\n", i, k);
    }
    if (maxCnt > 1e7) cant = true;

    vector<lli> ans;
    lli x = 0, s = 0;
    while (has() && !cant)
    {
      lli num = 0;
      for (int i = 0; i < maxB; i ++)
        if (cnt[i])
          num |= 1LL << i, cnt[i] --;
      x ^= num, s += num;
      ans.push_back(num);
      if (s > v) { cant = true; break; }
    }
    if (x != u || s != v || cant)
      printf("-1\n");
    else
    {
      printf("%d\n", (int)ans.size());
      for (int i = 0; i < ans.size(); i ++)
        printf("%lld%c", ans[i], i < ans.size() - 1 ? ' ' : '\n');
    }
  }
  return 0;
}
