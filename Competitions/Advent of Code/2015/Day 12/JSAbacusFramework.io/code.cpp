#include <bits/stdc++.h>
#define DEBUG if (0)

// Grammar:
// object = [ + object + ]
// object = { + kv_list + }
// kv_list =
// kv_list = kv
// kv_list = kv + , + kv_list
// kv = " + string + " + : + object
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
  int AddNumbers() const {
    int ans = 0;
    const auto visitor = overloads{[&](const ObjectList& list) {
                                     for (const auto& o : list) {
                                       ans += o.AddNumbers();
                                     }
                                   },
                                   [&](const ObjectMap& map) {
                                     for (const auto& [k, o] : map) {
                                       ans += o.AddNumbers();
                                     }
                                   },
                                   [&](const int& num) { ans += num; },
                                   [&](const std::string& str) {}};
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
          std::format_to(ctx.out(), "{{");
          bool first = true;
          for (const auto& [k, v] : map) {
            if (!first) std::format_to(ctx.out(), ",");
            std::format_to(ctx.out(), "\"{}\":{}", k, v);
            first = false;
          }
          std::format_to(ctx.out(), "}}");
        },
        [&](const int& num) { std::format_to(ctx.out(), "{}", num); },
        [&](const std::string& str) {
          std::format_to(ctx.out(), "\"{}\"", str);
        }};
    std::visit(visitor, o.data);
    return ctx.out();
  }
};

enum ParsingState { kObject = 0, kMap = 1, kList = 2 };
struct State {
  ParsingState parsing_state;
  Object& object;
};
const std::vector<std::string> kParsingStateName = {"Object", "Map", "List"};
struct Json {
  const Object object;
  Json(const std::string& s)
      : object([&]() {
          Object root_object;
          std::stack<State> states;
          states.emplace(ParsingState::kObject, root_object);
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
            const auto& [parsing_state, curr_object] = states.top();
            DEBUG std::println("\t{} | {} | {}", s[i],
                               kParsingStateName[parsing_state], curr_object);
            switch (parsing_state) {
              case ParsingState::kObject: {
                if (s[i] == ']' || s[i] == ',' || s[i] == '}') {
                  // Should be handled upstream.
                  --i;
                  states.pop();
                } else if (s[i] == '{') {
                  curr_object.data = ObjectMap{};
                  states.emplace(ParsingState::kMap, curr_object);
                } else if (s[i] == '[') {
                  curr_object.data = ObjectList{};
                  states.emplace(ParsingState::kList, curr_object);
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
              case ParsingState::kMap: {
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
                  states.emplace(ParsingState::kObject, new_object);
                }
                break;
              }
              case ParsingState::kList: {
                if (s[i] == ']') {
                  states.pop();
                } else {
                  assert(std::holds_alternative<ObjectList>(curr_object.data));
                  ObjectList& list =
                      *std::get_if<ObjectList>(&curr_object.data);
                  list.emplace_back();
                  Object& new_object = list.back();
                  if (s[i] != ',') --i;  // first element to be processed
                  states.emplace(ParsingState::kObject, new_object);
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

    const int ans = json.AddNumbers();
    std::println("ans: {}", ans);
  }
  return 0;
}
