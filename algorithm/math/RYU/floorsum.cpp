ll floorsum(ll a, ll b,ll c,ll n){ //[(ax+b)/c] x=0~n sum.
  if(!a) return (b / c) * (n + 1);
  if(a >= c or b >= c) return ( ( n * (n + 1) ) / 2) * (a / c) + (n + 1) * (b / c) + floorsum(a % c, b % c, c, n);
  long long m = (a * n + b) / c;
  return m * n - floorsum(c, c - b - 1, a, m - 1);
}