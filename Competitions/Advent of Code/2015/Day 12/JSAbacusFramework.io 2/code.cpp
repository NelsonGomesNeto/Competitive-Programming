#include <bits/stdc++.h>
#define DEBUG if (0)

std::string Spacing(const int depth) { return std::string(depth * 2, ' '); }

// Grammar:
// object = '[' object ']'
// object = '{' kv_list '}'
// kv_list = kv | kv , kv_list | e
// kv = '"' string '"' ':' object
// object = int
// object = string
template <class... Ts>
struct overloads : Ts... {
  using Ts::operator()...;
};
struct Object;
using ObjectMap = std::map<std::string, Object>;
using ObjectList = std::vector<Object>;
struct Object {
  std::variant<ObjectList, ObjectMap, int, std::string> data;

  std::string FormattedString(const int depth = 0,
                              const bool start_with_tab = true) const {
    std::string res = start_with_tab ? Spacing(depth) : "";
    auto resins = std::back_inserter(res);
    const auto visitor = overloads{
        [&](const ObjectList& list) {
          std::format_to(resins, "[\n{}\n{}]",
                         list | std::views::transform([&](const Object& io) {
                           return io.FormattedString(depth + 1);
                         }) | std::views::join_with(std::string_view(",\n")) |
                             std::ranges::to<std::string>(),
                         Spacing(depth));
        },
        [&](const ObjectMap& map) {
          std::format_to(
              resins, "{{\n{}\n{}}}",
              map |
                  std::views::transform(
                      [&](const std::pair<std::string, Object>& kv) {
                        const auto& [k, v] = kv;
                        return std::format(
                            "{}\"{}\": {}", Spacing(depth + 1), k,
                            v.FormattedString(depth + 1,
                                              /*start_with_tab=*/false));
                      }) |
                  std::views::join_with(std::string_view(",\n")) |
                  std::ranges::to<std::string>(),
              Spacing(depth));
        },
        [&](const int& num) { std::format_to(resins, "{}", num); },
        [&](const std::string& str) { std::format_to(resins, "\"{}\"", str); }};
    std::visit(visitor, data);
    return res;
  }

  int AddNumbers() const {
    int ans = 0;
    const auto visitor = overloads{
        [&](const ObjectList& list) {
          for (const auto& o : list) {
            ans += o.AddNumbers();
          }
        },
        [&](const ObjectMap& map) {
          const bool has_red = std::ranges::any_of(
              map | std::views::values, [](const Object& o) {
                const std::string* str = std::get_if<std::string>(&o.data);
                return str != nullptr && *str == "red";
              });
          if (has_red) return;
          for (const auto& [k, o] : map) {
            ans += o.AddNumbers();
          }
        },
        [&](const int& num) { ans += num; }, [&](const std::string& str) {}};
    std::visit(visitor, data);
    return ans;
  }
};
template <>
struct std::formatter<Object> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Object& o, FormatContext& ctx) const {
    const auto visitor = overloads{
        [&](const ObjectList& list) {
          std::format_to(ctx.out(), "[{}]",
                         list | std::views::transform([](const Object& io) {
                           return std::format("{}", io);
                         }) | std::views::join_with(std::string_view(",")) |
                             std::ranges::to<std::string>());
        },
        [&](const ObjectMap& map) {
          std::format_to(ctx.out(), "{{{}}}",
                         map |
                             std::views::transform(
                                 [](const std::pair<std::string, Object>& kv) {
                                   const auto& [k, v] = kv;
                                   return std::format("\"{}\":{}", k, v);
                                 }) |
                             std::views::join_with(std::string_view(",")) |
                             std::ranges::to<std::string>());
        },
        [&](const int& num) { std::format_to(ctx.out(), "{}", num); },
        [&](const std::string& str) {
          std::format_to(ctx.out(), "\"{}\"", str);
        }};
    std::visit(visitor, o.data);
    return ctx.out();
  }
};

struct State {
  enum Step { kObject = 0, kMap = 1, kList = 2 };
  Step step;
  Object& object;
};
const std::vector<std::string> kParsingStateName = {"Object", "Map", "List"};
struct Json {
  const Object object;
  Json(const std::string& s)
      : object([&]() {
          Object root_object;
          std::stack<State> states;
          states.emplace(State::Step::kObject, root_object);
          for (int i = 0; i < (int)s.size(); ++i) {
            auto ParseString = [&]() {
              assert(s[i] == '"');
              ++i;
              int j = i;
              while (j + 1 < (int)s.size() && s[j + 1] != '"') ++j;
              const std::string str = s.substr(i, j - i + 1);
              i = j + 1;
              assert(s[i] == '"');
              return str;
            };
            const auto& [step, curr_object] = states.top();
            DEBUG std::println("\t{} | {} | {}", s[i], kParsingStateName[step],
                               curr_object);
            switch (step) {
              case State::Step::kObject: {
                if (s[i] == ']' || s[i] == ',' || s[i] == '}') {
                  // Should be handled upstream.
                  --i;
                  states.pop();
                } else if (s[i] == '{') {
                  curr_object.data = ObjectMap{};
                  states.emplace(State::Step::kMap, curr_object);
                } else if (s[i] == '[') {
                  curr_object.data = ObjectList{};
                  states.emplace(State::Step::kList, curr_object);
                } else if (s[i] == '"') {
                  const std::string str = ParseString();
                  curr_object.data = str;
                  states.pop();
                } else {  // int case
                  const bool negative = s[i] == '-';
                  if (negative) ++i;
                  int j = i;
                  while (j + 1 < (int)s.size() && std::isdigit(s[j + 1])) ++j;
                  const int num =
                      std::stoi(s.substr(i, j - i + 1)) * (negative ? -1 : 1);
                  curr_object.data = num;
                  i = j;
                  states.pop();
                }
                break;
              }
              case State::Step::kMap: {
                if (s[i] == '}') {
                  states.pop();
                } else if (s[i] == ',') {
                  // just skip this one and look for the kv in the same state.
                } else {  // kv
                  assert(std::holds_alternative<ObjectMap>(curr_object.data));
                  const std::string str = ParseString();
                  ObjectMap& map = *std::get_if<ObjectMap>(&curr_object.data);
                  Object& new_object = map[str];
                  ++i;
                  assert(s[i] == ':');
                  states.emplace(State::Step::kObject, new_object);
                }
                break;
              }
              case State::Step::kList: {
                if (s[i] == ']') {
                  states.pop();
                } else {
                  assert(std::holds_alternative<ObjectList>(curr_object.data));
                  ObjectList& list =
                      *std::get_if<ObjectList>(&curr_object.data);
                  list.emplace_back();
                  Object& new_object = list.back();
                  if (s[i] != ',') --i;  // first element to be processed
                  states.emplace(State::Step::kObject, new_object);
                }
                break;
              }
              default:
                assert(false);
                break;
            }
          }
          return root_object;
        }()) {}

  std::string FormattedString() const { return object.FormattedString(); }

  int AddNumbers() const { return object.AddNumbers(); }
};
template <>
struct std::formatter<Json> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Json& j, FormatContext& ctx) const {
    return std::format_to(ctx.out(), "{}", j.object);
  }
};

int main() {
  while (true) {
    std::string json_str;
    if (!(std::cin >> json_str)) break;
    Json json(json_str);

    std::println("json: {}", json);
    std::println("formatted json:\n{}", json.FormattedString());

    const int ans = json.AddNumbers();
    std::println("ans: {}", ans);
  }
  return 0;
}
