#include <array>
#include <cassert>
#include <cstdint>
#include <deque>
#include <iostream>
#include <sstream>

int constexpr N = 218;

static std::array<uint64_t, N + 1> cache;
static std::array<std::deque<int>, N + 1> terms;

// Write n as a sum of different terms, all less than or equal `max_term',
// whose product is maximal, and return that product.
uint64_t f(int n, int max_term)
{
  // Use caching to speed things up.
  if (cache[n] != 0)
    return (terms[n][0] <= max_term) ? cache[n] : 0;

  // If n is less than 5 then the maximum product is n itself.
  if (n < 5)
  {
    terms[n] = { n };
    return cache[n] = n;
  }

  // Starting with the largest term that makes sense, try smaller and smaller terms,
  // until the largest product has been found.
  uint64_t largest_product = 0;
  for (int term = std::min(n - 2, max_term); term > 1; --term)
  {
    // Find the largest product, calling f recursively for the remaining part of the sum.
    uint64_t product = term * f(n - term, term - 1);
    if (product > largest_product)
    {
      largest_product = product;
      terms[n] = terms[n - term];
      terms[n].push_front(term);
    }
  }

  return cache[n] = largest_product;
}

int main()
{
  uint64_t max_product = f(N, N - 2);
  uint64_t product = 1;
  int sum = 0;
  char const* separator = "";
  for (int t : terms[N])
  {
    product *= t;
    sum += t;
    std::cout << separator << t;
    separator = " * ";
  }
  std::cout << " = " << product << std::endl;
  assert(product == max_product);
  assert(sum == N);
}
