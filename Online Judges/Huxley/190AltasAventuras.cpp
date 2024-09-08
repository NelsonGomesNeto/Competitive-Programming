#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
n == 1: 1
k == 1: n

k == 2:
max(d - 1, n / d + n % d)

The worst case is always:
pop until k == 1 and then test all remaining

*/

lli apSum(lli a1, lli n, lli d)
{
  lli an = a1 + (n - 1) * d;
  return n * (a1 + an) >> 1LL;
}

const int maxK = 30;
const int neg_inf = numeric_limits<int>().min();

struct TestCase {
  int N, K;

  map<int, int> memo[maxK + 1];
  map<pair<int, int>, int> mult_memo;
  int get_mult(int n, int d) {
    // auto key = make_pair(n, d);
    // if (mult_memo.count(key)) return mult_memo[key];
    // int& res = mult_memo[key];
    int lo = 1, hi = d;
    while (lo < hi) {
      int mid = (lo + hi + 1) >> 1;
      if (apSum(d, mid, -1) <= n) lo = mid;
      else hi = mid - 1;
    }
    return lo;
  }
  int eval(int n, int k, int d) {
    // if (d == 1) return 1 + solve(n - 1, k);
    // if (d == n) return 1 + solve2(d - 1, k - 1);
    // int pop = 1 + solve2(d - 1, k - 1);
    // int not_pop = n / d + max(solve2(d - 1, k - 1), solve2(n % d, k));
    // return not_pop;
    // return max(pop, not_pop);
    int lo = get_mult(n, d);
    int rem = n - apSum(d, lo, -1);
    // if (rem == 0) return 1 + solve2(d - 1, k - 1);
    // if (lo > d) return 1 + lo + solve2(rem, k);
    // if (lo < d) return 1 + solve2(d - 1, k - 1);
    return 1 + max(solve2(d - 1, k - 1), lo + solve2(rem, k));
  }
  int solve2(int n, int k, int depth = 0) {
    if (k == 1) return n;
    if (n == 0) return neg_inf;
    if (n == 1) return 1;
    if (memo[k].count(n)) return memo[k][n];

    // ans = n;
    // for (int j = 1, end = n; j <= end; ++j) {
    //   ans = min(ans, eval(n, k, j));
    // }
    int lo = 1, hi = n;
    // while (hi - lo > 2) {
    //   int midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi) / 3;
    //   assert(midlo > 0 && midhi > 0);
    //   int elo = eval(n, k, midlo);
    //   int ehi = eval(n, k, midhi);
    //   if (elo < ehi) hi = midhi;
    //   else lo = midlo;
    // }
    int& ans = memo[k][n];
    ans = n;
    for (int j = lo; j <= hi; ++j)
      ans = min(ans, eval(n, k, j));

    return ans;
  }

  map<int, string> path[maxK + 1];
  int solve(int n, int k, int depth = 0) {
    if (k == 1) return n;
    if (n == 1) return 1;
    if (memo[k].count(n)) return memo[k][n];

    int& ans = memo[k][n];
    string& p = path[k][n];
    ans = n;
    for (int i = 1, end = max((n + 1) / 2, min(n, 5)); i <= end; ++i) {
      int pop = i > 1 ? solve(i - 1, k - 1, depth + 1) : neg_inf;
      int not_pop = i < n ? solve(n - i, k, depth + 1) : neg_inf;
      DEBUG {
        for (int j = 0; j <= depth; ++j) printf("\t");
        printf("%d %d | %d %d\n", n, k, pop, not_pop);
      }
      pair<int, string> best = pop >= not_pop ? make_pair(pop, "P(" + to_string(i) + ")|" + path[k - 1][i - 1]) : make_pair(not_pop, to_string(n - i) + "|" + path[k][n - i]);
      if (1 + best.first <= ans)
        p = best.second;
      ans = min(ans, 1 + max(pop, not_pop));
    }

    return ans;
  }

  pair<int, string> solve3(int n, int k) {
    if (k == 1) return make_pair(n, "K");
    if (n == 1) return make_pair(1, "N");

    int ans = n; string ans_str = "F";
    for (int i = 1; i <= n; ++i) {
      auto [pop, pop_str] = i > 1 ? solve3(i - 1, k - 1) : make_pair(neg_inf, "");
      auto [not_pop, not_pop_str] = i < n ? solve3(n - i, k) : make_pair(neg_inf, "");
      int best; string best_str;
      if (pop > not_pop) {
        best = pop, best_str = pop_str + "P";
      } else {
        best = not_pop, best_str = not_pop_str + "X";
      }
      ++best;
      if (best < ans)
        ans = best, ans_str = best_str;
    }

    return make_pair(ans, ans_str);
  }

  int solve4(int n, int k) {
    int pops = 0;
    while (n > 1 && k > 0) {
      n >>= 1, --k, ++pops;
    }
    int ans = pops;
    if (k == 0 && n > 1) return ans += n - 1;
    else ans += 1;
    return ans;
  }

  bool can(int n, int k, int x) {
    return false;
  }
  int solve5(int n, int k) {
    int lo = 1, hi = n;
    while (lo < hi) {
      int mid = (lo + hi) >> 1;
      if (can(n, k, mid)) hi = mid;
      else lo = mid + 1;
    }
    return lo;
  }

  bool run() {
    if (scanf("%d %d", &N, &K) == EOF) return false;
    if (N > 1e5) return false;
    K = min(K, 30);

    // int ans = solve(N, K);
    // int ans2 = solve2(N, K);
    // printf("%d %d\n", ans, ans2);
    // printf("%d\n", ans2);
    // auto [ans, ans_str] = solve3(N, K);
    // printf("%d %s\n", ans, ans_str.c_str());
    int ans1 = solve(N, K);
    for (int j = 0; j <= K; ++j) memo[j].clear();
    // int ans2 = solve2(N, K);
    // printf("(%d, %d) | %d | %d | %s\n", N, K, ans1, ans2, path[K][N].c_str());
    printf("\t%d\n", ans1);
    printf("%d\n", solve2(N, K));

    return true;
  }
};
TestCase test_case;

int main() {
  while (true) {
    test_case = TestCase{};
    if (!test_case.run()) break;
  }
  return 0;
}
