#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

std::string ToString(const std::vector<int>& a) {
  std::ostringstream sout;
  for (int aa : a) {
    sout << aa << " ";
  }
  return sout.str();
}

std::vector<int> arr;
std::vector<int> tmp;
std::pair<int, int> GetMinMax(const std::vector<int>& a, const int lo,
                              const int hi) {
  const auto [minit, maxit] =
      std::minmax_element(a.begin() + lo, a.begin() + hi + 1);
  return std::make_pair(*minit, *maxit);
}
std::pair<int, int> Update(const int curr_min, const int curr_max, const int lo,
                           const int hi) {
  int p = lo;
  int pivot = arr[p];
  while (p < hi && (pivot == curr_min || pivot == curr_max)) {
    pivot = arr[++p];
  }

  int loi = lo, hii = hi;
  for (int i = lo; i <= hi; ++i) {
    if (arr[i] < pivot) {
      tmp[loi++] = arr[i];
    } else if (arr[i] > pivot) {
      tmp[hii--] = arr[i];
    }
  }
  p = loi;
  do {
    tmp[loi++] = pivot;
  } while (loi <= hii);

  DEBUG std::cout << "pivot: " << pivot << "\n";
  DEBUG std::cout << "lol: " << ToString(tmp) << "\n";

  for (int i = lo; i <= hi; ++i) {
    arr[i] = tmp[i];
  }

  if (pivot == curr_min || pivot == curr_max) {
    return std::make_pair(-1, -1);
  }

  return std::make_pair(pivot, p);
}
int Solve(const int lo = 0, const int hi = arr.size() - 1,
          const int border = -1) {
  const auto [curr_min, curr_max] = GetMinMax(arr, lo, hi);
  DEBUG std::cout << "sol: " << curr_min << " " << curr_max << " " << border
                  << " | " << lo << " " << hi << "\n";
  const int border_ans =
      border == -1
          ? 0
          : (border <= curr_min ? curr_min - border : border - curr_max);
  if (lo >= hi) {
    return border_ans;
  }
  if (curr_min == curr_max) {
    return border_ans;
  }

  const auto [pivot, p] = Update(curr_min, curr_max, lo, hi);
  if (pivot == -1) {
    return std::max(border_ans, curr_max - curr_min);
  }

  const int left_gap = pivot - curr_min, right_gap = curr_max - pivot;
  if (left_gap > right_gap) {
    int ans = std::max(border_ans, Solve(lo, p - 1, pivot));
    if (ans >= right_gap) return ans;

    return std::max(ans, Solve(p + 1, hi, pivot));
  } else {
    int ans = std::max(border_ans, Solve(p + 1, hi, pivot));
    if (ans >= left_gap) return ans;

    return std::max(ans, Solve(lo, p - 1, pivot));
  }
}

struct State {
  int lo, hi, border, gap;
  bool operator<(const State& other) const {
    return gap < other.gap ||
           (gap == other.gap && hi - lo < other.hi - other.lo);
  }
};
int Solve2() {
  std::priority_queue<State> pq;
  pq.emplace(0, arr.size() - 1, -1, 0);
  int best_ans = 0;
  while (!pq.empty()) {
    State s = pq.top();
    pq.pop();
    // if (s.gap < best_ans) {
    //   continue;
    // }
    const int lo = s.lo, hi = s.hi, border = s.border;

    const auto [curr_min, curr_max] = GetMinMax(arr, lo, hi);
    DEBUG std::cout << "sol: " << curr_min << " " << curr_max << " " << border
                    << " | " << lo << " " << hi << "\n";
    const int border_ans =
        border == -1
            ? 0
            : (border <= curr_min ? curr_min - border : border - curr_max);
    if (lo >= hi || curr_min == curr_max) {
      best_ans = std::max(best_ans, border_ans);
      continue;
    }

    const auto [pivot, p] = Update(curr_min, curr_max, lo, hi);
    if (pivot == -1) {
      best_ans = std::max({best_ans, border_ans, curr_max - curr_min});
      continue;
    }

    const int left_gap = pivot - curr_min, right_gap = curr_max - pivot;
    if (left_gap > best_ans) pq.emplace(lo, p - 1, pivot, left_gap);
    if (right_gap > best_ans) pq.emplace(p + 1, hi, pivot, right_gap);
  }
  return best_ans;
}

struct Bucket {
  void Add(const int x) {
    minimum = std::min(minimum, x);
    maximum = std::max(maximum, x);
  }
  bool Empty() const {
    return minimum == std::numeric_limits<int>::max();
  }
  int minimum = std::numeric_limits<int>::max(),
      maximum = std::numeric_limits<int>::min();
};
int Solve3(const std::vector<int>& arr) {
  if (arr.size() == 1) return 0;

  const auto [minit, maxit] = std::minmax_element(arr.begin(), arr.end());
  const int minimum = *minit, maximum = *maxit;
  const int minimum_gap =
      std::ceil((double)(maximum - minimum) / (arr.size() - 1));
  if (minimum_gap == 0) return 0;

  std::vector<Bucket> buckets(arr.size() + 1);
  /*
  d = (max - min) / (n - 1)  (minimum_gap)
  buckets = {
    [min : min + d - 1],
    [min + d : min + 2*d - 1],
    ...,
    [min + (n-2)*d : min + (n-1)*d - 1],
    [min + (n-1)*d : min + n*d - 1]  (just max)
  }
  */
  for (const int a : arr) {
    const int curr = a - minimum;
    const int gap = curr / minimum_gap;
    buckets[gap].Add(a);
  }

  int ans = 0;
  for (int i = 0; i + 1 < buckets.size(); ++i) {
    while (i < buckets.size() && buckets[i].Empty()) ++i;
    int j = i + 1;
    while (j < buckets.size() && buckets[j].Empty()) ++j;

    if (j >= buckets.size()) continue;

    const int l_max = buckets[i].maximum;
    const int r_min = buckets[j].minimum;
    const int gap = r_min - l_max;

    ans = std::max(ans, gap);
  }

  return ans;
}

class Solution {
 public:
  int maximumGap(std::vector<int>& nums) {
    // arr = nums;
    // tmp = arr;
    // std::fill(tmp.begin(), tmp.end(), -1);
    return Solve3(nums);
  }
};

int Naive(std::vector<int> nums) {
  int prv_size = nums.size();
  std::sort(nums.begin(), nums.end());
  nums.resize(
      std::distance(nums.begin(), std::unique(nums.begin(), nums.end())));
  int res = 0;
  for (int i = 1; i < nums.size(); ++i) {
    res = std::max(res, nums[i] - nums[i - 1]);
  }
  return res;
}

int main() {
  for (std::string line; std::getline(std::cin, line);) {
    DEBUG std::cout << line << "\n";
    std::stringstream sin(line);
    arr.clear();
    for (int a; sin >> a;) {
      arr.push_back(a);
    }
    DEBUG std::cout << "size: " << arr.size() << "\n";

    int ans = Solution().maximumGap(arr);
    int nai = Naive(arr);
    std::cout << "nai: " << nai << "\n";
    DEBUG std::cout << "ans: " << ans << "\n";
    DEBUG std::cout << "arr: " << ToString(arr) << "\n";
    std::cout << ans << "\n";

    DEBUG std::cout << "----------------------------\n";
  }
  return 0;
}