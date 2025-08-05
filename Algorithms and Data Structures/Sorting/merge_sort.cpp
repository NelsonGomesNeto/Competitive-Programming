#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

using time_precision = std::chrono::milliseconds;

void Print(const std::string& prefix, const std::vector<int>& arr, const int lo,
           const int hi) {
  std::cout << prefix;
  for (int i = lo; i <= hi; ++i) {
    std::cout << arr[i] << " ";
  }
  std::cout << "\n";
}

namespace no_temp {
// The worst case is O(n^2) and it is pretty often!!
void Merge(const int alo, const int ahi, const int blo, const int bhi,
           std::vector<int>& arr) {
  for (int i = alo; i <= ahi; ++i) {
    if (arr[i] <= arr[blo]) continue;

    std::swap(arr[i], arr[blo]);
    for (int j = blo; j + 1 <= bhi && arr[j] > arr[j + 1]; ++j) {
      std::swap(arr[j], arr[j + 1]);
    }
  }
}

void MergeSortInternal(const int lo, const int hi, std::vector<int>& arr) {
  const int sz = hi - lo + 1;
  if (sz <= 1) return;

  const int mid = (lo + hi) >> 1;
  MergeSortInternal(lo, mid, arr);
  MergeSortInternal(mid + 1, hi, arr);

  Merge(lo, mid, mid + 1, hi, arr);
}

void MergeSort(std::vector<int>& arr) {
  MergeSortInternal(0, (int)arr.size() - 1, arr);
}
}  // namespace no_temp

namespace with_temp {
void Merge(const int alo, const int ahi, const int blo, const int bhi,
           std::vector<int>& arr, std::vector<int>& temp) {
  for (int i = alo, j = blo, k = alo; i <= ahi || j <= bhi;) {
    if (i <= ahi && j <= bhi) {
      if (arr[i] <= arr[j])
        temp[k++] = arr[i++];
      else
        temp[k++] = arr[j++];
    } else if (i <= ahi) {
      while (i <= ahi) temp[k++] = arr[i++];
    } else {
      while (j <= bhi) temp[k++] = arr[j++];
    }
  }
  for (int i = alo; i <= bhi; ++i) arr[i] = temp[i];
}

void MergeSortInternal(const int lo, const int hi, std::vector<int>& arr,
                       std::vector<int>& temp) {
  const int sz = hi - lo + 1;
  if (sz <= 1) return;

  const int mid = (lo + hi) >> 1;
  MergeSortInternal(lo, mid, arr, temp);
  MergeSortInternal(mid + 1, hi, arr, temp);

  Merge(lo, mid, mid + 1, hi, arr, temp);
}

void MergeSort(std::vector<int>& arr) {
  std::vector<int> temp(arr.size());
  MergeSortInternal(0, (int)arr.size() - 1, arr, temp);
}
}  // namespace with_temp

namespace with_temp_async {
const int kThreadLimit = 12;
std::vector<int> temp;
std::atomic_int thread_cnt = 0;

void Merge(const int alo, const int ahi, const int blo, const int bhi,
           std::vector<int>& arr) {
  for (int i = alo, j = blo, k = alo; i <= ahi || j <= bhi;) {
    if (i <= ahi && j <= bhi) {
      if (arr[i] <= arr[j])
        temp[k++] = arr[i++];
      else
        temp[k++] = arr[j++];
    } else if (i <= ahi) {
      while (i <= ahi) temp[k++] = arr[i++];
    } else {
      while (j <= bhi) temp[k++] = arr[j++];
    }
  }
  for (int i = alo; i <= bhi; ++i) arr[i] = temp[i];
}

std::pair<bool, std::future<void>> RunAsyncOrSync(
    const std::function<void()>& f) {
  if (thread_cnt >= kThreadLimit) {
    f();
    return std::make_pair(false, std::future<void>{});
  } else {
    ++thread_cnt;
    return std::make_pair(true, std::async(f));
  }
}

const int kAsyncThreshold = 1e4;
void MergeSortInternal(const int lo, const int hi, std::vector<int>& arr) {
  const int sz = hi - lo + 1;
  if (sz <= 1) return;

  const int mid = (lo + hi) >> 1;
  if (sz < kAsyncThreshold) {
    MergeSortInternal(lo, mid, arr);
    MergeSortInternal(mid + 1, hi, arr);
  } else {
    const auto [right_is_async, right] =
        RunAsyncOrSync([&]() { MergeSortInternal(mid + 1, hi, arr); });
    MergeSortInternal(lo, mid, arr);
    if (right_is_async) {
      right.wait();
      --thread_cnt;
    }
  }

  Merge(lo, mid, mid + 1, hi, arr);
}

void MergeSort(std::vector<int>& arr) {
  temp.resize(arr.size()), thread_cnt = 0;
  MergeSortInternal(0, (int)arr.size() - 1, arr);
}
}  // namespace with_temp_async

namespace no_temp_async {
const int kThreadLimit = 12;
std::atomic_int thread_cnt = 0;

// The worst case is O(n^2)!
void Merge(const int alo, const int ahi, const int blo, const int bhi,
           std::vector<int>& arr) {
  for (int i = alo; i <= ahi; ++i) {
    if (arr[i] <= arr[blo]) continue;

    std::swap(arr[i], arr[blo]);
    for (int j = blo; j + 1 <= bhi && arr[j] > arr[j + 1]; ++j) {
      std::swap(arr[j], arr[j + 1]);
    }
  }
}

std::pair<bool, std::future<void>> RunAsyncOrSync(
    const std::function<void()>& f) {
  if (thread_cnt >= kThreadLimit) {
    f();
    return std::make_pair(false, std::future<void>{});
  } else {
    ++thread_cnt;
    return std::make_pair(true, std::async(f));
  }
}

const int kAsyncThreshold = 1e4;
void MergeSortInternal(const int lo, const int hi, std::vector<int>& arr) {
  const int sz = hi - lo + 1;
  if (sz <= 1) return;

  const int mid = (lo + hi) >> 1;
  if (sz < kAsyncThreshold) {
    MergeSortInternal(lo, mid, arr);
    MergeSortInternal(mid + 1, hi, arr);
  } else {
    const auto [right_is_async, right] =
        RunAsyncOrSync([&]() { MergeSortInternal(mid + 1, hi, arr); });
    MergeSortInternal(lo, mid, arr);
    if (right_is_async) {
      right.wait();
      --thread_cnt;
    }
  }

  Merge(lo, mid, mid + 1, hi, arr);
}

void MergeSort(std::vector<int>& arr) {
  MergeSortInternal(0, (int)arr.size() - 1, arr);
}
}  // namespace no_temp_async

namespace multiple_temp {
void Merge(const int alo, const int ahi, const int blo, const int bhi,
           std::vector<int>& arr) {
  std::vector<int> temp;
  for (int i = alo, j = blo; i <= ahi || j <= bhi;) {
    if (i <= ahi && j <= bhi) {
      if (arr[i] <= arr[j])
        temp.push_back(arr[i++]);
      else
        temp.push_back(arr[j++]);
    } else if (i <= ahi) {
      while (i <= ahi) temp.push_back(arr[i++]);
    } else {
      while (j <= bhi) temp.push_back(arr[j++]);
    }
  }
  for (int i = alo, k = 0; i <= bhi; ++i, ++k) arr[i] = temp[k];
}

void MergeSortInternal(const int lo, const int hi, std::vector<int>& arr) {
  const int sz = hi - lo + 1;
  if (sz <= 1) return;

  const int mid = (lo + hi) >> 1;
  MergeSortInternal(lo, mid, arr);
  MergeSortInternal(mid + 1, hi, arr);

  Merge(lo, mid, mid + 1, hi, arr);
}

void MergeSort(std::vector<int>& arr) {
  MergeSortInternal(0, (int)arr.size() - 1, arr);
}
}  // namespace multiple_temp

const int kExecutions = 30;
time_precision GetAverageExecutionTime(
    std::vector<int> arr,
    const std::function<void(std::vector<int>&)>& sort_fn) {
  time_precision average{0};
  std::vector<int> cpy = arr;
  for (int i = 0; i < kExecutions; ++i) {
    arr = cpy;
    const auto start = std::chrono::high_resolution_clock::now();
    sort_fn(arr);
    const auto end = std::chrono::high_resolution_clock::now();
    const auto duration =
        std::chrono::duration_cast<time_precision>(end - start);
    average += duration;
  }
  assert(std::ranges::is_sorted(arr));
  return average / kExecutions;
}

void BruteForce() {
  const int size = 8;
  std::vector<int> arr;
  arr.reserve(size);
  for (int i = 0; i < size; ++i) arr.push_back(i);

  do {
    std::vector<int> cpy = arr;
    no_temp_async::MergeSort(cpy);
    if (!std::ranges::is_sorted(cpy)) {
      std::cout << "input :";
      for (const int v : arr) std::cout << v << " ";
      std::cout << "\n";
      std::cout << "broken:";
      for (const int v : cpy) std::cout << v << " ";
      std::cout << "\n";
      std::fflush(stdout);
      assert(false);
    }
  } while (std::next_permutation(arr.begin(), arr.end()));
}

int main() {
  // std::ios::sync_with_stdio(false);
  // std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  std::cin.ignore(1);

  std::string input;
  std::getline(std::cin, input);
  std::istringstream sin(input);
  std::vector<int> arr(n);
  for (int& ai : arr) sin >> ai;
  // for (int& ai : arr) std::cin >> ai;

  std::print("array: {{");
  for (const int ai : arr | std::views::take(5)) std::print(" {}", ai);
  std::println(" }}");

  const std::vector<
      std::pair<std::string, std::function<void(std::vector<int>&)>>>
      hehe = {
          {"with_temp", &with_temp::MergeSort},
          // {"no_temp", &no_temp::MergeSort},
          {"with_temp_async", &with_temp_async::MergeSort},
          // {"no_temp_async", &no_temp_async::MergeSort},
      };
  for (const auto& [name, fn] : hehe) {
    const auto average = GetAverageExecutionTime(arr, fn);
    std::cout << name << ": " << average << "\n";
  }

  DEBUG {
    for (const int ai : arr) std::cout << ai << " ";
    std::cout << "\n";
    std::fflush(stdout);
  }

  // BruteForce();

  return 0;
}
