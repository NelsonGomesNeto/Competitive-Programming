I honestly expected the image to be something surpring but AFAICT it seems like
a thermal picture of something unknown on low res hahaha.

I didn't optimize anything and did `O(|instructions|*n*m)`.
I do wonder though, if it is even possible to optimize it because of the
negative rule of capping at 0. Without that, it's possible to do
`O(|instructions|*n + n*m)`. With that, it seems like
`O(|negatives|*n*m + |positives|*n)` where `negatives` and `positives` are
ranges with negatives and positives instructions.