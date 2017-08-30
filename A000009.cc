#include <cmath>
#include <vector>
#include <cstdio>
#include <algorithm>

using int64 = long long;

// produce first n terms in O(n \sqrt n)
std::vector<int64> run(int64 n, int64 mod) {
  std::vector<int64> f(n + 1), g(n + 1);
  std::vector<int64> res(n + 1);
  int m = (int)sqrt(2 * n);
  f[0] = 1;
  for (int i = 1; i <= m; ++i) {
    std::fill(g.begin(), g.end(), 0);
    for (int j = i; j <= n; ++j) {
      g[j] = (f[j - i] + g[j - i]) % mod;
    }
    f.swap(g);
    for (int j = 1; j <= n; ++j) {
      res[j] = (res[j] + f[j]) % mod;
    }
  }
  return res;
}

int main() {
  auto res = run(100, 100000000);
  for (int i = 1; i < 100; ++i) {
    printf("%d %lld\n", i, res[i]);
  }
  return 0;
}
