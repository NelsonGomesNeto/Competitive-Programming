#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int kMaxN = 2e5;
int n, m;
int a[kMaxN];
int cnt[kMaxN];

struct Candidate {
  int i, votes;

  bool operator<(const Candidate& other) const {
    return votes < other.votes || (votes == other.votes && i > other.i);
  }
};

int main() {
  while (~scanf("%d %d", &n, &m)) {
    for (int i = 0; i < m; ++i) {
      scanf("%d", &a[i]);
      --a[i];
    }

    fill(cnt, cnt+n, 0);
    set<Candidate> candidates;
    for (int i = 0; i < n; ++i)
      candidates.insert(Candidate{i, 0});

    for (int i = 0; i < m; ++i) {
      candidates.erase(Candidate{a[i], cnt[a[i]]});
      ++cnt[a[i]];
      candidates.insert(Candidate{a[i], cnt[a[i]]});
      printf("%d\n", candidates.rbegin()->i + 1);
    }
  }
  return 0;
}
