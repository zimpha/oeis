#include <cstdio>
#include <cassert>
#include <vector>

using int64 = long long;

// produce first n terms
std::vector<int64> run_linear(int64 n) {
  std::vector<int64> e(n + 1), p, d(n + 1);
  std::vector<bool> mark(n + 1);
  d[1] = 1;
  for (int64 i = 2; i <= n; ++i) {
    if (!mark[i]) {
      p.push_back(i);
      e[i] = d[i] = 2;
    }
    for (size_t j = 0, u = n / i; j < p.size() && p[j] <= u; ++j) {
      mark[i * p[j]] = true;
      if (i % p[j]) {
        e[i * p[j]] = 2;
        d[i * p[j]] = d[i] * 2;
      } else {
        e[i * p[j]] = e[i] + 1;
        d[i * p[j]] = d[i] / e[i] * (e[i] + 1);
        break;
      }
    }
  }
  return d;
}

// produce the n-th term
int64 run_sqrt(int64 n) {
  int64 ret = 1;
  for (int64 i = 2; i * i <= n; ++i) {
    if (n % i) continue;
    int64 cnt = 0;
    while (n % i == 0) n /= i, ++cnt;
    ret *= (cnt + 1);
  }
  if (n > 1) ret *= 2;
  return ret;
}

int main() {
  auto d = run_linear(1000000);
  for (int i = 1; i <= 1000000; ++i) {
    assert(d[i] == run_sqrt(i));
  }
  return 0;
}
