#include "compare.h"

class Sales_data {
  // 未实现 operator == 和 operator <
};

int main(int argc, char **argv) {
  Sales_data d1, d2;

  // 编译报错：
  // 未定义运算符或到预定义运算符可接受的类型的转换
  compare(d1, d2);
  return 0;
}
