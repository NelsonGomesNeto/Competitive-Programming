This was the first day where I stopped to optimize it.
It was also the first time I optimized the range intersection to O(n*lg).
It's pretty interesting.

Initial algorithm was O(n^2) and ran in 18.5s over 10^5 ranges with no overlap.

Then, O(n*lg) ran in ~70ms over 10^5 ranges with no overlap.
The idea is to:
1. Start with an empty set of ranges;
1. Sort the ranges to add by `start` and then `end`;
1. Since they're sorted, we'll always add a new range or extend the last one.