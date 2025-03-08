#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const int kDi[4] = {0, 0, 1, -1};
const int kDj[4] = {1, -1, 0, 0};

struct TestCase {
  int n, m;
  std::vector<std::string> mat;

  void PrintYesNo(const bool ans) { std::cout << (ans ? "Yes" : "No") << "\n"; }

  bool FindRectangle(const int hashtag_cnt) {
    int loi = n, loj = m, hii = 0, hij = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (mat[i][j] != '#') continue;
        loi = std::min(loi, i), loj = std::min(loj, j);
        hii = std::max(hii, i), hij = std::max(hij, j);
      }
    }

    for (int i = loi; i <= hii; ++i) {
      for (int j = loj; j <= hij; ++j) {
        if (mat[i][j] != '.') continue;
        return false;
      }
    }
    return true;
  }

  bool Run() {
    if (!(std::cin >> n >> m)) return false;
    mat.resize(n);
    for (auto& row : mat) std::cin >> row;

    const auto [hashtag_cnt, question_cnt] = [&]() {
      int hashtag_cnt = 0, question_cnt = 0;
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
          hashtag_cnt += mat[i][j] == '#';
          question_cnt += mat[i][j] == '?';
        }
      }
      return std::make_pair(hashtag_cnt, question_cnt);
    }();
    if (hashtag_cnt == 0) {
      PrintYesNo(question_cnt > 0);
      return true;
    }

    const bool ans = FindRectangle(hashtag_cnt);
    PrintYesNo(ans);

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  do {
    test_case = TestCase{};
  } while (test_case.Run());

  return 0;
}
