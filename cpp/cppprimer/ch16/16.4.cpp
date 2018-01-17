#include <iostream>
#include <list>
#include <string>
#include <vector>

template <typename I, typename T>
I find(I begin, I end, const T &val) {
  for (auto i = begin; i != end; i++) {
    if (*i == val) return i;
  }
  return end;
}

int main(int argc, char **argv) {
  std::vector<int> v { 1, 2, 3, 4, 5 };
  auto i1 = ::find(v.begin(), v.end(), 3);
  // 这样输出结果不是期望的 3,4。因为参数核算的顺序是不确定的。
  //std::cout << *i1 << ',' << *(++i1) << '\n';
  std::cout << *i1 << ',' << *(i1+1) << '\n';

  std::list<std::string> l { "hello", "world", "bye" };
  auto i2 = ::find(l.begin(), l.end(), "world");
  // 无法编译，因为 std::list<T>::iterator 未定义 operator +
  // std::cout << *i2 << ',' << *(i2+1) << '\n';
  std::cout << *i2 << ',';
  std::cout << *(++i2) << '\n';

  return 0;
}
