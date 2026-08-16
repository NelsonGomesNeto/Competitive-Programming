#include <bits/stdc++.h>

void PrintGraphviz() {
  std::ofstream ofs("graph.dot", std::ios_base::out);
  std::println(ofs, "digraph {{");
  std::println(ofs, "bgcolor=\"#000000\"");
  std::println(ofs,
               "node [fontcolor=\"#ffffff\", color=\"#ffffff\", "
               "fillcolor=\"#333333\", style=filled]");
  std::println(ofs, "edge [color=\"#ffffff\", fontcolor=\"#ffffff\"]");
  auto AddEdge = [&](const std::string& u, const std::string& v) {
    std::println(ofs, "\"{}\" -> \"{}\"", u, v);
  };

  AddEdge("a", "c");
  AddEdge("b", "c");

  std::println(ofs, "}}");
}

int main() {
  PrintGraphviz();
  return 0;
}
