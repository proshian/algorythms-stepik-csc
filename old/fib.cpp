#include <cassert>
#include <iostream>

class Fibonacci final {
 public:
  static int get(int n) {
    assert(n >= 0);
    if (n<2)
    	return n;
    unsigned int arr[2];
    arr[0] = 0; arr[1] = 1;
    
    int i;
    for(i = 2; i <= n; i++)
    	arr[i%2] = arr[0] + arr[1];
    return arr[(i-1)%2];
  }
};

int main(void) {
  int n;
  std::cin >> n;
  std::cout << Fibonacci::get(n) << std::endl;
  return 0;
}
