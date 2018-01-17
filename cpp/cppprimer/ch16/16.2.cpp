#include <assert.h>
#include <string>
#include "compare.h"

int main(int argc, char **argv) {
  std::string s1("aaaaaaaaaaab");
  std::string s2("b");
  std::string s3(s2);

  assert(compare(s1, s2) == -1);
  assert(compare(s2, s3) == 0);
  assert(compare(s3, s1) == 1);

  return 0;
}
