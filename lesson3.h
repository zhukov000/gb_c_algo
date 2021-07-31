
int isPrime(unsigned x) {
  unsigned d = 2;
  while ((d * d <= x) && (x % d != 0)) ++d;
  return (x > 1) && (d * d > x);
}
