#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <tuple>
#include <unordered_map>
#include "solution.h"
#include "util.h"

using namespace std;
using namespace sol105;

/*
preorder = [3,9,20,15,7]
inorder = [9,3,15,20,7]

   3
   / \
  9  20
    /  \
   15   7

*/

tuple<vector<int>, vector<int>, Node *>
testFixture1()
{
  auto pre = vector<int>{3, 9, 20, 15, 7};
  auto in = vector<int>{9, 3, 15, 20, 7};

  auto root = new Node(3);
  root->left = new Node(9);
  root->right = new Node(20);
  root->right->left = new Node(15);
  root->right->right = new Node(7);

  return make_tuple(pre, in, root);
}

void test1()
{
  auto f = testFixture1();
  Solution sol;
  auto root = sol.buildTree(get<0>(f), get<1>(f));

  cout << "Expect to see : 7" << endl;
  cout << root->right->right->val << endl;
}

main()
{
  test1();
}