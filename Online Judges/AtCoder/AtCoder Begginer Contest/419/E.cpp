#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

/*
every sum(A[i : i + L - 1]) === 0 (mod m)

{
sum(A[0 : (L - 1)]) === 0 (mod m)
sum(A[1 : (L - 1) + 1]) === 0 (mod m)
...
sum(A[(n - 1) - (L - 1) : n - 1]) === 0 (mod m)

A[0] - A[L] === 0 (mod m)
A[0] === A[L] (mod m)
A[1] - A[L + 1] === 0 (mod m)
...
A[L] - A[2*L] === 0 (mod m)
A[n - 1 - L] - A[n - 1] === 0 (mod m)
eq1: A[i] - A[i + L] === 0 (mod m)

We only need to define A[0 : (L - 1)]
Then, from (eq1) we can replicate the state of
A[0 : (L - 1)] all other positions >= L.

So that A[1 : L] is guaranteed to be safe since
A[L] is "modular" equivalent to A[0] :).
}

*/

void PrintArray(const std::vector<int>& arr) {
  std::cout << "\t";
  for (int i = 0; i < (int)arr.size(); ++i) {
    if (i) std::cout << " ";
    std::cout << arr[i];
  }
  std::cout << "\n";
}

const int kInf = 1e7;

struct TestCase {
  int n, m, l;
  std::vector<int> a;

  int Cost(const int pos, const int add) {
    int cost = add, prv = a[pos] + add;
    for (int i = pos + l; i < n; i += l) {
      // A[i] - A[i + L] === 0 (mod m)
      const int delta = (prv - a[i]) % m;
      const int required = delta < 0 ? m + delta : delta;
      cost += required;
      assert((prv - (a[i] + required)) % m == 0);
      prv = a[i] + required;
    }
    return cost;
  }

  std::vector<std::vector<int>> memo;
  int Solve(const int i = 0, int sum = 0) {
    sum %= m;
    if (i == l) {
      return sum == 0 ? 0 : kInf;
    }
    int& ans = memo[i][sum];
    if (ans != -1) return ans;

    ans = kInf;
    for (int add = 0; add < m; ++add) {
      const int res = Solve(i + 1, sum + (a[i] + add)) + Cost(i, add);
      ans = std::min(ans, res);
    }
    return ans;
  }

  bool Run() {
    if (!(std::cin >> n >> m >> l)) return false;
    a.resize(n);
    for (auto& ai : a) std::cin >> ai;

    memo.resize(n, std::vector<int>(m, -1));
    const int ans = Solve();
    std::cout << ans << "\n";

    return true;
  }
};

int main() {
  while (true) {
    TestCase test_case{};
    if (!test_case.Run()) break;
  }
  return 0;
}