#include "./BinaryTree.h"
#include <iostream>
#include <stack>

using tree_node = TreeNode<int>;

// 深度优先 & 递归
void Walk(tree_node *t) {
  if (t == nullptr) return;
  Walk(t->left);
  std::cout << t->val << '\n';
  Walk(t->right);
}

// 深度优先 & 非递归
void Walk2(tree_node *t) {
  std::stack<tree_node *> stack;

  stack.push(t);
  while (!stack.empty()) {
    auto l = stack.top()->left;
    if (!l) {
      auto r = stack.top()->right;
      std::cout << stack.top()->val << '\n';
      stack.pop();
      if (r)
        stack.push(r);
    } else {
      stack.top()->left = nullptr;
      stack.push(l);
    }
  }
}

int main(int argc, char **argv) {
  auto t = NewTree(std::vector<int>{1,2,3,4,5,6});
  Walk(t);
  std::cout << "--------\n";
  Walk2(t);
  return 0;
}
