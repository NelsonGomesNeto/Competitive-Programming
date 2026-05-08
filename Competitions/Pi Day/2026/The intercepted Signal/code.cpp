#include <bits/stdc++.h>

const std::map<std::string, char> kMorseToLetterMap{
    {".-", 'a'},    {"-...", 'b'},  {"-.-.", 'c'},  {"-..", 'd'},
    {".", 'e'},     {"..-.", 'f'},  {"--.", 'g'},   {"....", 'h'},
    {"..", 'i'},    {".---", 'j'},  {"-.-", 'k'},   {".-..", 'l'},
    {"--", 'm'},    {"-.", 'n'},    {"---", 'o'},   {".--.", 'p'},
    {"--.-", 'q'},  {".-.", 'r'},   {"...", 's'},   {"-", 't'},
    {"..-", 'u'},   {"...-", 'v'},  {".--", 'w'},   {"-..-", 'x'},
    {"-.--", 'y'},  {"--..", 'z'},  {"-----", '0'}, {".----", '1'},
    {"..---", '2'}, {"...--", '3'}, {"....-", '4'}, {".....", '5'},
    {"-....", '6'}, {"--...", '7'}, {"---..", '8'}, {"----.", '9'},
};

bool GetLetter(std::istream& sin, std::string& letter) {
  letter.clear();
  while (!sin.eof() && sin.peek() != ' ') {
    if (sin.peek() == '\n') {
      if (letter.empty()) {
        letter = "\n";
        sin.get();
      }
      return true;
    }
    letter.push_back(sin.get());
  }
  return !letter.empty();
}

struct MorseCode {
  int letter_pause;
  std::array<int, 2> word_pause;
  std::string signal;
  std::vector<std::vector<std::string>> words;
  std::string decoded_signal;

  friend std::istream& operator>>(std::istream& sin, MorseCode& m) {
    sin >> m.letter_pause >> m.word_pause[0] >> m.word_pause[1];
    sin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (std::string line; std::getline(sin, line, '\n');) {
      // if (line.empty()) line = "\n";
      // if (!m.signal.empty()) m.signal.push_back('\n');
      line.push_back('\n');
      m.signal += line;
    }
    return sin;
  }

  void Parse() {
    std::istringstream sin(signal);
    int pause_parity = 0;
    std::vector<std::string> word;
    for (std::string letter; GetLetter(sin, letter);) {
      const int sep_count = [&]() {
        int sep_count = 0;
        while (sin.peek() == ' ') ++sep_count, sin.ignore(1);
        return sep_count;
      }();
      word.push_back(letter);

      if (sin.eof()) {
        // EOF
        words.push_back(word);
        word.clear();
        break;
      } else if (sep_count == 0) {
        words.push_back(word);
        word.clear();
        continue;
      } else if (sep_count == letter_pause) {
        continue;
      } else {
        // word_pause
        assert(sep_count == word_pause[pause_parity]);
        pause_parity = 1 - pause_parity;
        words.push_back(word);
        word.clear();
      }
    }

    for (const auto& word : words) {
      if (!decoded_signal.empty()) decoded_signal.push_back(' ');
      for (const auto& letter : word) {
        const auto it = kMorseToLetterMap.find(letter);
        const char decoded_letter = [&]() {
          if (it == kMorseToLetterMap.end()) {
            // assert(letter.size() == 1);
            return letter[0];
          } else {
            return it->second;
          }
        }();
        decoded_signal.push_back(decoded_letter);
      }
    }
  }
};
template <>
struct std::formatter<MorseCode> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const MorseCode& m, FormatContext& ctx) const {
    std::format_to(ctx.out(), "letter_pause: {}\n", m.letter_pause);
    std::format_to(ctx.out(), "word_pause[0]: {}\n", m.word_pause[0]);
    std::format_to(ctx.out(), "word_pause[1]: {}\n", m.word_pause[1]);
    std::format_to(ctx.out(), "signal:\n|{}|\n", m.signal);
    std::format_to(
        ctx.out(), "words:\n|{}|\n",
        m.words |
            std::views::transform([](const std::vector<std::string>& word) {
              return std::format("{}", word | std::views::join_with(' ') |
                                           std::ranges::to<std::string>());
            }) |
            std::views::join_with('|') | std::ranges::to<std::string>());
    std::format_to(ctx.out(), "decoded_signal:\n|{}|\n", m.decoded_signal);
    return ctx.out();
  }
};

int main() {
  MorseCode morse_code;
  std::cin >> morse_code;

  morse_code.Parse();

  std::println("\tmorse_code:\n{}", morse_code);

  return 0;
}
