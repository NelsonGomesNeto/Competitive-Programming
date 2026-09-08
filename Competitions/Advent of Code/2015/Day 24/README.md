OH YES, balancing the sleigh was AWESOME \o/.

Perhaps A* would be better here, but I was able to get a DFS with pruning solve
part 2 in 150ms with O2 \o/.

It even finds other solutions along the way.

I also played around with `std::countr_zero` and `std::countl_zero`. They make
iterating on a mask a lot faster \o/.
But again, the biggest optimization was to prune by the current best solution.
Another nice optimization was to solve the first group first hahaha.