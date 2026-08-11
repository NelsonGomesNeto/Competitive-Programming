#include <bits/stdc++.h>

void PrintPpm(const int n, const int m) {
  std::ofstream ofs("image.ppm", std::ios_base::out | std::ios_base::binary);
  ofs << "P6\n" << m << " " << n << "\n255\n";

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      const uint8_t r = (uint8_t)(i * 10 % 256), g = (uint8_t)(j * 10 % 256),
                    b = (uint8_t)(i * 10 * j % 256);
      ofs << r << g << b;
    }
  }
}

int main() {
  PrintPpm(/*n=*/10, /*m=*/20);
  return 0;
}
