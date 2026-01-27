#include <bits/stdc++.h>

struct Device {
  std::string name;
  int id;
  std::vector<std::string> output_names;
  Device(std::istream&& sin) {
    std::getline(sin, name, ':');
    sin.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    for (std::string s; std::getline(sin, s, ' ') && !s.empty();) {
      output_names.push_back(s);
    }
  }
  Device(const std::string& device_str)
      : Device(std::istringstream(device_str)) {}

  auto operator<=>(const Device& o) const { return id <=> o.id; }
  bool operator==(const Device& o) const { return id == o.id; }
};
template <>
struct std::formatter<Device> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Device& d, FormatContext& ctx) const {
    return std::format_to(ctx.out(), "{} -> {}", d.name,
                          d.output_names | std::views::join_with(' ') |
                              std::ranges::to<std::string>());
  }
};

struct Reactor {
  std::vector<Device> devices;
  std::vector<std::vector<int>> graph;
  std::vector<std::string> all_devices;
  int GetId(const std::string& name) const {
    return std::ranges::lower_bound(all_devices, name) - all_devices.begin();
  }
  int GetId(const Device& d) const { return GetId(d.name); }

  friend std::istream& operator>>(std::istream& sin, Reactor& r) {
    for (std::string line; std::getline(sin, line) && !line.empty();) {
      r.devices.emplace_back(line);
    }
    r.BuildGraph();
    return sin;
  }
  void BuildGraph() {
    for (const auto& d : devices) {
      all_devices.push_back(d.name);
      all_devices.insert(all_devices.end(), d.output_names.begin(),
                         d.output_names.end());
    }
    std::ranges::sort(all_devices);
    all_devices.resize(
        std::distance(all_devices.begin(),
                      std::unique(all_devices.begin(), all_devices.end())));

    graph.resize(all_devices.size(), {});
    for (auto& u : devices) {
      u.id = GetId(u);
    }
    std::ranges::sort(devices);
    // TODO: Make this prettier using references inside the Device struct!
    for (auto& u : devices) {
      for (auto& v : u.output_names) {
        graph[u.id].push_back(GetId(v));
      }
    }
  }

  int Dfs(const int u, const int target) {
    if (u == target) {
      return 1;
    }

    int ans = 0;
    for (const int v : graph[u]) {
      ans += Dfs(v, target);
    }
    return ans;
  }
  int CountPaths() { return Dfs(GetId("you"), GetId("out")); }
};
template <>
struct std::formatter<Reactor> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Reactor& r, FormatContext& ctx) const {
    std::format_to(ctx.out(), "devices:\n{}",
                   r.devices | std::views::transform([](const Device& d) {
                     return std::format("\t{}", d);
                   }) | std::views::join_with('\n') |
                       std::ranges::to<std::string>());
    std::format_to(ctx.out(), "\ngraph:\n");
    for (const auto& [i, outs] : r.graph | std::views::enumerate) {
      std::format_to(ctx.out(), "\t{} -> {}\n", i, outs);
    }
    return ctx.out();
  }
};

int main() {
  Reactor reactor;
  std::cin >> reactor;

  std::println("reactor:\n{}", reactor);

  const int ans = reactor.CountPaths();
  std::println("Ans: {}", ans);

  return 0;
}
