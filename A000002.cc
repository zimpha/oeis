// produce 3 * 10^9 terms
#include <cstdio>

const int N = 100000000, B = 20;

using ll = long long;

ll extand[1 << B];
ll bits[1 << B];
unsigned int mask[30];
unsigned int s[N];
unsigned int m;

int get(unsigned int p) {
  return s[p >> 5] >> (p & 31) & 1;
}

void set(unsigned int p, int o) {
  int x = p >> 5, y = p & 31;
  unsigned int v = (s[x] >> y & 1) << y;
  s[x] ^= v;
  s[x] |= o << y;
}

unsigned int get_from(unsigned int p) {
  int x = p >> 5, y = p & 31;
  unsigned int r = s[x] >> y;
  if (32 - y >= B) return r & mask[B];
  else return (r | ((s[x + 1] & mask[y + B - 32]) << (32 - y))) & mask[B];
}

void set_from(unsigned int p, int l, ll v) {
  int x = p >> 5, y = p & 31;
  if (l <= 32 - y) {
    s[x] |= v << y;
  } else {
    ll u = v >> (32 - y) << (32 - y);
    s[x] |= (v ^ u) << y;
    l -= 32 - y;
    u >>= 32 - y;
    while (l >= 32) {
      s[++x] = u;
      u >>= 32;
      l -= 32;
    }
    s[x + 1] = u;
  }
}

void prepare() {
  for (int i = 0; i < 30; ++i) mask[i] = (1 << i) - 1;
  for (int mask = 0; mask < (1 << B); ++mask) {
    ll v = 0, s = 0;
    for (int i = 0; i < B; ++i) {
      int e = 1 + (mask >> i & 1);
      while (e--) v |= ll(i & 1) << (s++);
    }
    extand[mask] = v;
    bits[mask] = s;
  }
  m = 0;
  set(0, 0); set(1, 1);
  for (int i = 0; i < 60; ++i) {
    int e = 1 + get(i);
    while (e--) set(m++, i & 1);
  }
  m = 0;
  for (unsigned int i = 0; m < 3000000000; i += 20) {
    int v = get_from(i);
    set_from(m, bits[v], extand[v]);
    m += bits[v];
  }
}

int main() {
  prepare();
  for (int i = 0; i < 100; ++i) printf("%d ", get(i) + 1);
  puts("");
  return 0;
}
