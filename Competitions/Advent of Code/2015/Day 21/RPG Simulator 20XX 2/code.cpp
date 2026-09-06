#include <bits/stdc++.h>

int ReadInt(std::istringstream& sin) {
  int num;
  sin >> num;
  return num;
}
std::string ReadString(std::istringstream& sin) {
  std::string str;
  sin >> str;
  sin.ignore(1);
  if (sin.peek() != ' ') {
    std::string to_add;
    sin >> to_add;
    str += " " + to_add;
  }
  return str;
}

const std::vector<std::string> kItemTypeName = {
    "Weapon",
    "Armor",
    "Ring",
};
struct Item {
  enum Type { kWeapon = 0, kArmor = 1, kRing = 2 };
  const Type type;
  const std::string name;
  const int cost, damage, armor;
  Item(const Type& t, std::istringstream&& sin)
      : type(t),
        name(ReadString(sin)),
        cost(ReadInt(sin)),
        damage(ReadInt(sin)),
        armor(ReadInt(sin)) {}
  Item(const Type& t, const std::string& str)
      : Item(t, std::istringstream(str)) {}
};
template <>
struct std::formatter<Item> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Item& i, FormatContext& ctx) const {
    return std::format_to(ctx.out(), "{:6} | {:10} | c: {:3}, d: {:1}, a: {:1}",
                          kItemTypeName[(int)i.type], i.name, i.cost, i.damage,
                          i.armor);
  }
};

struct Game {
  struct Being {
    int hp, damage, armor;
    void Hit(Being& other) const {
      other.hp -= std::max(1, damage - other.armor);
    }
  };
  const std::vector<Item> items;
  const Being initial_player, initial_boss;
  Game(std::istringstream&& sin)
      : items([&]() {
          std::vector<Item> is;
          Item::Type type;
          int types_done = 0;
          for (std::string line; std::getline(sin, line);) {
            if (line.empty()) {
              if (types_done == 3) break;
              continue;
            }
            if (auto it =
                    std::ranges::find_if(kItemTypeName,
                                         [&](const std::string& type_name) {
                                           return line.starts_with(type_name);
                                         });
                it != kItemTypeName.end()) {
              ++types_done;
              type = Item::Type((int)std::distance(kItemTypeName.begin(), it));
              continue;
            }
            is.emplace_back(type, line);
          }
          return is;
        }()),
        initial_player(Being{.hp = 100, .damage = 0, .armor = 0}),
        initial_boss([&]() {
          int hp, damage, armor;
          sin.ignore(std::numeric_limits<std::streamsize>::max(), ':');
          sin >> hp;
          sin.ignore(std::numeric_limits<std::streamsize>::max(), ':');
          sin >> damage;
          sin.ignore(std::numeric_limits<std::streamsize>::max(), ':');
          sin >> armor;
          return Being{hp, damage, armor};
        }()) {}
  Game(const std::string& str) : Game(std::istringstream(str)) {}

  bool Can(Being player) const {
    Being boss = initial_boss;
    bool player_turn = true;
    while (player.hp > 0 && boss.hp > 0) {
      if (player_turn) {
        player.Hit(boss);
      } else {
        boss.Hit(player);
      }
      player_turn = !player_turn;
    }
    return player.hp > 0;
  }
  void MaxGoldRec(int& best, std::vector<int>& best_picks, Being player,
                  int i = 0, std::array<int, 3> item_budget = {1, 1, 2},
                  int gold = 0, std::vector<int> picks = {}) const {
    if (i == (int)items.size()) {
      // Must buy at least one weapon.
      if (item_budget[0] == 0 && gold > best && !Can(player)) {
        best = gold, best_picks = picks;
      }
      return;
    }

    MaxGoldRec(best, best_picks, player, i + 1, item_budget, gold, picks);
    const Item& item = items[i];
    int& budget = item_budget[(int)item.type];
    if (budget) {
      --budget;
      player.damage += item.damage, player.armor += item.armor;
      picks.push_back(i);
      MaxGoldRec(best, best_picks, player, i + 1, item_budget, gold + item.cost,
                 picks);
    }
  }
  int MaxGold() const {
    std::println("MaxGold:");
    int best = std::numeric_limits<int>::min();
    std::vector<int> best_picks;
    MaxGoldRec(best, best_picks, initial_player);
    std::println("\tbest_picks: {}",
                 best_picks | std::views::transform(
                                  [&](const int i) { return items[i].name; }));
    return best;
  }
};
template <>
struct std::formatter<Game> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Game& g, FormatContext& ctx) const {
    return std::format_to(
        ctx.out(), "items:\n{}\ninitial_player | {}\ninitial_boss   | {}",
        g.items | std::views::transform([](const Item& i) {
          return std::format("\t{}", i);
        }) | std::views::join_with('\n') |
            std::ranges::to<std::string>(),
        g.initial_player, g.initial_boss);
  }
};
template <>
struct std::formatter<Game::Being> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Game::Being& s, FormatContext& ctx) const {
    return std::format_to(ctx.out(), "hp: {:3}, d: {:2}, a: {:2}", s.hp,
                          s.damage, s.armor);
  }
};

int main() {
  const std::string input(std::istreambuf_iterator<char>(std::cin), {});
  const Game game(input);

  std::println("game:\n{}", game);

  const int ans = game.MaxGold();
  std::println("ans: {}", ans);

  return 0;
}
