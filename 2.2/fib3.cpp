#include <cassert>
#include <iostream>

template <class Int>
Int gcd(Int a, Int b) {
  
if (a%b == 0)
  	return b;
if (b%a == 0)
	return a;
if (a>=b)
	return gcd(a%b,b);

return gcd(b%a,a);
  
}

int main(void) {
  int a, b;
  std::cin >> a >> b;
  std::cout << gcd(a, b) << std::endl;
  return 0;
}
