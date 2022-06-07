
#ifndef SOLUTION_H
#define SOLUTION_H

#include "node.h"
#include <vector>
#include <queue>
#include <unordered_map>
#include <map>
#include <string>
#include <stack>

using namespace std;
namespace sol105
{

  class Solution
  {
  private:
    Node *_buildTree(
        int preS, int preE, int inS, int inE, vector<int> &preorder,
        vector<int> &inorder, unordered_map<int, int> &map);

  public:
    Node *buildTree(vector<int> &preorder, vector<int> &inorder);
  };

}
#endif