#ifndef COMPARE_H_
#define COMPARE_H_

template <typename T>
int compare(const T &x, const T &y) {
  if (x < y) return -1;
  if (y < x) return 1;
  return 0;
}

#endif
