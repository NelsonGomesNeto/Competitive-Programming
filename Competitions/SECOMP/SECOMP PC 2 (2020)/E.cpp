int ans = 0;
for (int sz = 1; sz <= n; sz++)
{
  (i + sz - 2) - (i) + 1 = (sz - 1);
  (j + sz - 2) - (j) + 1 = (sz - 1);
  ans += (sz - 1) * (sz - 1);
  // for (int i = 0; i + sz - 1 < n; i++)
  //   for (int j = 0; j + sz - 1 < n; j++)
  //     ans++;
}