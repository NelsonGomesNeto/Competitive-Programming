#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

enum Type { FIVE, FOUR, FULL_HOUSE, THREE, TWO, ONE, HIGH };
const std::string cards_order = "AKQJT98765432";
std::vector<int> card_rank(256);

struct Hand {
  std::string cards;
  int bid;

  std::vector<int> cards_rank;
  Type type;

  bool operator<(const Hand& other) const {
    return type < other.type || (type == other.type && cards_rank < other.cards_rank);
  }

  void Build() {
    std::map<char, int> cnt;
    cards_rank.clear();
    for (char c : cards) {
      ++cnt[c];
      cards_rank.push_back(card_rank[c]);
    }

    if (cnt.size() == 1) {
      type = Type::FIVE;
    } else if (cnt.size() == 2) {
      type = cnt.begin()->second == 1 || cnt.begin()->second == 4
                 ? Type::FOUR
                 : Type::FULL_HOUSE;
    } else if (cnt.size() == 3) {
      type = Type::TWO;
      for (auto [_, f] : cnt) {
        if (f == 3) type = Type::THREE;
      }
    } else if (cnt.size() == 4) {
      type = Type::ONE;
    } else {
      type = Type::HIGH;
    }
  }

  friend std::istream& operator>>(std::istream& stream, Hand& h) {
    stream >> h.cards >> h.bid;
    h.Build();
    return stream;
  }

  friend std::ostream& operator<<(std::ostream& stream, const Hand& h) {
    stream << h.cards << " " << h.bid << " " << h.type << " |";
    for (const int rank : h.cards_rank) stream << " " << rank;
    return stream;
  }
};
std::vector<Hand> hands;

int main() {
  for (int i = 0; i < cards_order.size(); ++i) {
    card_rank[cards_order[i]] = i;
  }

  Hand h;
  while (std::cin >> h) {
    hands.push_back(h);
  }

  DEBUG {
    for (const auto& hand : hands) {
      std::cout << hand << std::endl;
    }
  }

  sort(hands.begin(), hands.end());
  reverse(hands.begin(), hands.end());

  lli ans = 0;
  for (int i = 0; i < hands.size(); ++i) {
    DEBUG std::cout << (i + 1) << " " << hands[i] << std::endl;
    ans += (i + 1) * hands[i].bid;
  }
  std::cout << ans << std::endl;

  return 0;
}
