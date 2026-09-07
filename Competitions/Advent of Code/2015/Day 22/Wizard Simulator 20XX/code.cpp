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

struct Magic {
  struct Effect {
    int turns, damage = 0, armor = 0, mana = 0;
    bool operator==(const Effect& other) const {
      return damage == other.damage && armor == other.armor &&
             mana == other.mana;
    }
  };
  const std::string name;
  const int cost, damage = 0, heal = 0;
  const std::optional<Effect> effect = std::nullopt;
};
template <>
struct std::formatter<Magic::Effect> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Magic::Effect& me, FormatContext& ctx) const {
    return std::format_to(ctx.out(), "t: {:1}, d: {:1}, a: {:1}, m: {:3}",
                          me.turns, me.damage, me.armor, me.mana);
  }
};
template <>
struct std::formatter<Magic> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Magic& m, FormatContext& ctx) const {
    std::format_to(ctx.out(), "{:13} | c: {:3}, d: {:1}, h: {:1}", m.name,
                   m.cost, m.damage, m.heal);
    if (m.effect.has_value()) {
      std::format_to(ctx.out(), " | {}", *m.effect);
    }
    return ctx.out();
  }
};

struct Being {
  int hp, damage = 0, armor = 0, mana = 0;
  void Hit(Being& other) const {
    other.hp -= std::max(1, damage - other.armor);
  }
};
template <>
struct std::formatter<Being> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Being& s, FormatContext& ctx) const {
    if (s.mana > 0) {
      return std::format_to(ctx.out(), "hp: {:3}, a: {:2}, m: {:3}", s.hp,
                            s.armor, s.mana);
    } else {
      return std::format_to(ctx.out(), "hp: {:3}, a: {:2}, d: {:2}", s.hp,
                            s.armor, s.damage);
    }
  }
};

struct Game {
  const std::vector<Magic> magics = {
      Magic{.name = "Magic Missile", .cost = 53, .damage = 4},
      Magic{.name = "Drain", .cost = 73, .damage = 2, .heal = 2},
      Magic{.name = "Shield",
            .cost = 113,
            .effect = Magic::Effect{.turns = 6, .armor = 7}},
      Magic{.name = "Poison",
            .cost = 173,
            .effect = Magic::Effect{.turns = 6, .damage = 3}},
      Magic{.name = "Recharge",
            .cost = 229,
            .effect = Magic::Effect{.turns = 5, .mana = 101}},
  };
  const Being initial_player, initial_boss;
  Game(std::istringstream&& sin)
      : initial_player([&]() {
          Being being;
          sin.ignore(std::numeric_limits<std::streamsize>::max(), ':');
          sin >> being.hp;
          sin.ignore(std::numeric_limits<std::streamsize>::max(), ':');
          sin >> being.mana;
          return being;
        }()),
        initial_boss([&]() {
          Being being;
          sin.ignore(std::numeric_limits<std::streamsize>::max(), ':');
          sin >> being.hp;
          sin.ignore(std::numeric_limits<std::streamsize>::max(), ':');
          sin >> being.damage;
          return being;
        }()) {}
  Game(const std::string& str) : Game(std::istringstream(str)) {}

  void ApplyEffects(std::list<Magic::Effect>& effects, Being& player,
                    Being& boss) const {
    for (auto it = effects.begin(); it != effects.end();) {
      auto& effect = *it;
      if (effect.damage > 0) boss.hp -= effect.damage;
      if (effect.armor > 0) player.armor = effect.armor;
      if (effect.mana > 0) player.mana += effect.mana;
      --effect.turns;
      if (effect.turns == 0) {
        if (effect.armor > 0) player.armor = 0;
        it = effects.erase(it);
      } else {
        ++it;
      }
    }
  }
  void CastMagic(const Magic& magic, Being& player, Being& boss,
                 std::list<Magic::Effect>& effects) const {
    assert(player.mana >= magic.cost);
    player.mana -= magic.cost;
    if (magic.effect.has_value()) {
      assert(!std::ranges::contains(effects, *magic.effect));
      effects.push_back(*magic.effect);
    } else {
      if (magic.damage > 0) {
        boss.hp -= magic.damage;
      }
      if (magic.heal > 0) {
        player.hp += magic.heal;
      }
    }
  }
  void MinManaRec(int& best, std::vector<int>& best_picks, Being player,
                  Being boss, const bool player_turn = true, const int mana = 0,
                  std::list<Magic::Effect> effects = {},
                  std::vector<int> picks = {}) const {
    if (mana > best) return;
    if (player.hp <= 0) return;

    ApplyEffects(effects, player, boss);

    if (boss.hp <= 0) {
      if (mana < best) {
        best = mana, best_picks = picks;
      }
      return;
    }

    if (player_turn) {
      picks.push_back(-1);
      const Being before_player = player, before_boss = boss;
      std::list<Magic::Effect> before_effects = effects;
      for (const auto& [i, magic] : magics | std::views::enumerate) {
        if (player.mana < magic.cost ||
            (magic.effect.has_value() &&
             std::ranges::contains(effects, *magic.effect)))
          continue;
        picks.back() = i;
        CastMagic(magic, player, boss, effects);
        MinManaRec(best, best_picks, player, boss, !player_turn,
                   mana + magic.cost, effects, picks);
        player = before_player, boss = before_boss, effects = before_effects;
      }
    } else {
      player.hp -= std::max(1, boss.damage - player.armor);
      MinManaRec(best, best_picks, player, boss, !player_turn, mana, effects,
                 picks);
    }
  }
  int MinMana() const {
    std::println("MinMana:");
    int best = std::numeric_limits<int>::max();
    std::vector<int> best_picks;
    MinManaRec(best, best_picks, initial_player, initial_boss);
    std::println("\tbest_picks: {} | best_picks: {}", best_picks,
                 best_picks | std::views::transform(
                                  [&](const int i) { return magics[i].name; }));

    std::list<Magic::Effect> effects;
    Being player = initial_player, boss = initial_boss;
    for (int player_turn = 1, pick = 0; player.hp > 0 && boss.hp > 0;
         player_turn = 1 - player_turn) {
      ApplyEffects(effects, player, boss);
      if (boss.hp <= 0) break;
      std::println(
          "{} | p: {} | b: {} | {}", player_turn, player, boss,
          effects | std::views::transform([&](const Magic::Effect& effect) {
            return std::format("{}", effect);
          }) | std::views::join_with(std::string_view(", ")) |
              std::ranges::to<std::string>());

      if (player_turn) {
        if (pick >= (int)best_picks.size()) break;
        const Magic& magic = magics[best_picks[pick]];
        std::println("\t{}", magic);
        CastMagic(magic, player, boss, effects);
        ++pick;
      } else {
        player.hp -= std::max(1, boss.damage - player.armor);
      }
    }
    std::println("p: {} | b: {} |", player, boss);
    assert(player.hp > 0 && boss.hp <= 0);

    return best;
  }
};
template <>
struct std::formatter<Game> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Game& g, FormatContext& ctx) const {
    return std::format_to(
        ctx.out(), "magics:\n{}\ninitial_player | {}\ninitial_boss   | {}",
        g.magics | std::views::transform([&](const Magic& m) {
          return std::format("\t{}", m);
        }) | std::views::join_with('\n') |
            std::ranges::to<std::string>(),
        g.initial_player, g.initial_boss);
  }
};

int main() {
  const std::string input(std::istreambuf_iterator<char>(std::cin), {});
  const Game game(input);

  std::println("game:\n{}", game);
  std::println("{}", std::string(80, '-'));

  const int ans = game.MinMana();
  std::println("ans: {}", ans);

  return 0;
}
