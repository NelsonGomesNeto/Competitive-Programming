while True:
  try:
    a, b, c, d = map(int, input().split())
  except EOFError:
    break

  lo, hi = 0, int(1e20)
  while lo < hi:
    mid = (lo + hi) >> 1
    cyan = a + b * mid
    red = c * mid
    if cyan <= red * d: hi = mid
    else: lo = mid + 1

  cyan = a + b * lo
  red = c * lo
  if cyan > red * d: print("-1")
  else: print(lo)