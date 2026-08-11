#include <bits/stdc++.h>

const std::string kTarget = "000000";

std::string Strip(const std::string& s) {
  auto is_space = [](char ch) { return std::isspace(ch); };
  auto view = std::views::all(s) | std::views::drop_while(is_space) |
              std::views::reverse | std::views::drop_while(is_space) |
              std::views::reverse;
  return {view.begin(), view.end()};
}

// Md5 hash implementation based on https://en.wikipedia.org/wiki/MD5
// All variables are unsigned 32 bit and wrap modulo 2^32 when calculating
namespace Md5 {
// s specifies the per-round shift amounts.
const std::array<uint32_t, 64> s = {
    7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
    5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20,
    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};
// Use binary integer part of the sines of integers (Radians) as constants:
// for i from 0 to 63 do
//  K[i] := floor(232 × abs(sin(i + 1)))
// end for
// Precalc table:
const std::array<uint32_t, 64> K = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a,
    0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340,
    0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8,
    0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa,
    0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92,
    0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

// Returns an Md5 hash from a `message`.
std::string Hash(std::string message, const bool verbose = false) {
  const uint64_t original_length_in_bits = message.size() * 8;
  // Pre-process message
  // Append 0x80 and pad with 0x00 bytes so that the message length in
  // bytes ≡ 56 (mod 64).
  message.push_back(0x80);
  while (message.size() % 64 != 56) {
    message.push_back(0x00);
  }
  // append original length in bits mod 2^64 to message
  std::array<uint8_t, 8> bytes;
  std::memcpy(bytes.data(), &original_length_in_bits, /*byte_count=*/8);
  for (const auto byte : bytes) message.push_back(byte);

  if (verbose) {
    std::println("pre-processed message: {}",
                 message | std::views::transform([](const char c) {
                   return std::format("{:02x}", c);
                 }) | std::views::join_with(' ') |
                     std::ranges::to<std::string>());
  }

  // Process message
  // Initialize variables:
  uint32_t a0 = 0x67452301, b0 = 0xefcdab89, c0 = 0x98badcfe, d0 = 0x10325476;
  if (verbose) {
    std::println("it - | {}A | {}B  | {}C  | {}D  |", std::string(6, ' '),
                 std::string(6, ' '), std::string(6, ' '), std::string(6, ' '));
    std::println("in - 0x{:08x} 0x{:08x} 0x{:08x} 0x{:08x}", a0, b0, c0, d0);
  }
  // Process the message in successive 512-bit (64 bytes) chunks:
  for (const auto& chunk : message | std::views::chunk(64)) {
    // break chunk into sixteen 32-bit words M[j], 0 ≤ j ≤ 15
    std::array<uint32_t, 16> M;
    std::ranges::fill(M, 0);
    for (auto [j, mj] : M | std::views::enumerate) {
      // This must also be little-endian and the chunks must lose the sign :^)
      for (int i = 3; i >= 0; --i) {
        mj = (mj << 8) | (uint8_t)chunk[j * 4 + i];
      }
    }
    // Initialize hash value for this chunk:
    uint32_t A = a0, B = b0, C = c0, D = d0;
    // Main loop:
    for (int i = 0; i < 64; ++i) {
      uint32_t F, g;
      if (i >= 0 && i <= 15) {
        F = (B & C) | ((~B) & D);
        g = i;
      } else if (i >= 16 && i <= 31) {
        F = (D & B) | ((~D) & C);
        g = (5 * i + 1) % 16;
      } else if (i >= 32 && i <= 47) {
        F = B ^ C ^ D;
        g = (3 * i + 5) % 16;
      } else if (i >= 48 && i <= 63) {
        F = C ^ (B | (~D));
        g = (7 * i) % 16;
      }
      F += A + K[i] + M[g];  // M[g] must be a 32-bit block
      A = D;
      D = C;
      C = B;
      B += std::rotl(F, s[i]);
      if (verbose) {
        std::println("{:02d} - 0x{:08x} 0x{:08x} 0x{:08x} 0x{:08x}", i, A, B, C,
                     D);
      }
    }
    // Add this chunk's hash to result so far:
    a0 += A;
    b0 += B;
    c0 += C;
    d0 += D;
  }

  std::array<uint32_t, 4> raw_digest = {a0, b0, c0, d0};
  // std::array<uint32_t, 4> raw_digest = {d0, c0, b0, a0};
  std::array<uint8_t, 16> digest_bytes;
  std::memcpy(digest_bytes.data(), raw_digest.data(), 16);
  std::string digest;
  for (const auto byte : digest_bytes) digest.push_back(byte);
  return digest | std::views::transform([](const uint8_t c) {
           return std::format("{:02x}", c);
         }) |
         std::views::join | std::ranges::to<std::string>();
}
}  // namespace Md5

int FindSmallest(const std::string& message) {
  for (int i = 1;; ++i) {
    const std::string hash = Md5::Hash(std::format("{}{}", message, i));
    if (hash.starts_with(kTarget)) return i;
  }
  return -1;
}

int main() {
  std::string s;
  std::cin >> s;
  s = Strip(s);

  std::println("message: {}", s);
  const std::string hash = Md5::Hash(s, /*verbose=*/true);
  std::println("hash: {}", hash);
  std::println("{}", std::string(80, '-'));

  const int ans = FindSmallest(s);
  std::println("ans: {}", ans);
  std::println("{} + {} -> {}", s, ans, Md5::Hash(std::format("{}{}", s, ans)));

  return 0;
}
