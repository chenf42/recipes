#include "./BinaryTree.h"
#include <iostream>
#include <queue>

using tree_node = TreeNode<int>;

// 广度优先
void Walk(tree_node *t) {
  if (t == nullptr) return;
  std::queue<tree_node *> unvisited;
  unvisited.push(t);

  while (!unvisited.empty()) {
    auto curr = unvisited.front();
    unvisited.pop();
    if (curr->left)
      unvisited.push(curr->left);
    if (curr->right)
      unvisited.push(curr->right);
    std::cout << curr->val << '\n';
  }
}

int main(int argc, char **argv) {
  auto t = NewTree(std::vector<int>{1,2,3,4,5,6});
  Walk(t);
  return 0;
}
