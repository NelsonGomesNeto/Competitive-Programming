#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e5;
char s[maxN + 1];
int n, q;

struct Query {
  int t, x; char c;
  void read() {
    scanf("%d %d %c", &t, &x, &c);
    --x;
  }
};
Query queries[maxN];

int main()
{
  while (~scanf("%d", &n)) {
    scanf(" %s", s);

    scanf("%d", &q);
    int last_flip = -1;
    for (int i = 0; i < q; ++i) {
      queries[i].read();

      if (queries[i].t == 1) {
        s[queries[i].x] = queries[i].c;
      } else {
        last_flip = i;
      }
    }


    string ans = string(s);
    if (last_flip != -1) {
      Query query = queries[last_flip];
      if (query.t == 2) {
        for (int i = 0; i < n; ++i)
          ans[i] = tolower(ans[i]);
      }
      else {  // t = 3
        for (int i = 0; i < n; ++i)
          ans[i] = toupper(ans[i]);
      }

      for (int i = last_flip + 1; i < q; ++i)
        if (queries[i].t == 1)
          ans[queries[i].x] = queries[i].c;
    }
    printf("%s\n", ans.c_str());
  }
  return 0;
}
