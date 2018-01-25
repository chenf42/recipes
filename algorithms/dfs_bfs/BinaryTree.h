#ifndef BINARYTREE_H_
#define BINARYTREE_H_

#include <vector>
#include <queue>

template <typename T>
struct TreeNode {
  T val;
  TreeNode *left;
  TreeNode *right;
};

template <typename T>
TreeNode<T> *NewTree(std::vector<T> v) {
  if (v.empty())
    return nullptr;

  auto root = new TreeNode<T>{v[0], nullptr, nullptr};
  std::queue<TreeNode<T> *> queue;
  queue.push(root);
  size_t i = 1;

  while (i < v.size()) {
    auto left = new TreeNode<T>{v[i], nullptr, nullptr};
    i++;
    TreeNode<T> *right = nullptr;
    if (i < v.size()) {
      right = new TreeNode<T>{v[i], nullptr, nullptr};
      i++;
    }
    queue.front()->left = left;
    queue.front()->right = right;
    queue.pop();
    queue.push(left);
    if (right)
      queue.push(right);
  }

  return root;
}

#endif
