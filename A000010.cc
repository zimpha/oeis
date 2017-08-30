#include <cstdio>
#include <cassert>
#include <vector>

using int64 = long long;

// produce first n terms
std::vector<int64> run_linear(int64 n) {
  std::vector<int64> p, phi(n + 1);
  std::vector<bool> mark(n + 1);
  phi[1] = 1;
  for (int64 i = 2; i <= n; ++i) {
    if (!mark[i]) {
      p.push_back(i);
      phi[i] = i - 1;
    }
    for (size_t j = 0, u = n / i; j < p.size() && p[j] <= u; ++j) {
      mark[i * p[j]] = true;
      if (i % p[j]) {
        phi[i * p[j]] = phi[i] * (p[j] - 1);
      } else {
        phi[i * p[j]] = phi[i] * p[j];
        break;
      }
    }
  }
  return phi;
}

// produce the n-th term
int64 run_sqrt(int64 n) {
  int64 ret = n;
  for (int64 i = 2; i * i <= n; ++i) {
    if (n % i) continue;
    while (n % i == 0) n /= i;
    ret = ret / i * (i - 1);
  }
  if (n > 1) ret = ret / n * (n - 1);
  return ret;
}

int main() {
  const int n = 1000000;
  auto phi = run_linear(n);
  for (int i = 1; i <= n; ++i) {
    assert(phi[i] == run_sqrt(i));
  }
  return 0;
}
