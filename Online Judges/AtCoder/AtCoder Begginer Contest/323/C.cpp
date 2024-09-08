#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int kMaxN = 100;
int n, m;
int a[kMaxN];
pair<int, int> score_problem[kMaxN];
char ss[kMaxN + 1];
string s[kMaxN];
int scores[kMaxN];
int biggest_score;

string ReadString() {
  scanf(" %s", ss);
  return string(ss);
}

int ans[kMaxN];
int Solve(int i) {
  int curr = scores[i];
  int res = 0;
  for (int j = m - 1; j >= 0 && curr < biggest_score; --j) {
    int p = score_problem[j].second;
    if (s[i][p] == 'o') continue;
    curr += a[p], ++res;
  }
  return res;
}

int main() {
  int tt = 0;
  while (~scanf("%d %d", &n, &m)) {
    if (tt++) printf("-----------------\n");

    for (int i = 0; i < m; ++i) {
      scanf("%d", &a[i]);
      score_problem[i] = make_pair(a[i], i);
    }
    sort(score_problem, score_problem+m);

    for (int i = 0; i < n; ++i) {
      s[i] = ReadString();
      scores[i] = i;
      for (int j = 0; j < m; ++j)
        scores[i] += (s[i][j] == 'o') * a[j];
    }
    biggest_score = *max_element(scores, scores+n);

    for (int i = 0; i < n; ++i)
      ans[i] = Solve(i);
    for (int i = 0; i < n; ++i)
      printf("%d\n", ans[i]);
  }
  return 0;
}
