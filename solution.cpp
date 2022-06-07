#include "solution.h"
#include "util.h"
#include <unordered_set>
#include <numeric>
#include <iterator>
#include <unordered_map>
#include <deque>
#include <string>
#include <sstream>
#include <algorithm>
#include <stack>
#include <iostream>
using namespace sol105;
using namespace std;

/*takeaways
  - preorder=[3,9,20,15,7] inorder=[9,3,15,20,7]
  - so the basic idea is locate the root from the preorder
    in the inorder and break both into smaller pieces
  - for example from preorder, we know 3 is the root.
  - you then look at inorder and know [9] is its left
    child, which only has one number: (indx of 3) - 0 = 1
  - we now go back to preorder and know that the next
    number will be its left tree as well
  - the rest should be all for the right child
  - pre [3,9,20,15,7] -> [9] & [20,15,7]
  - in [9,3,15,20,7] -> [9] & [15,20,7]
  - so we can continue building left child with [9] and [9]
    and right child with [20,15,7] and [15,20,7]

*/

Node *Solution::buildTree(vector<int> &preorder, vector<int> &inorder)
{
  /* for easy lookup from preorder back to inorder */
  auto m = unordered_map<int, int>();
  for (auto i = 0; i < inorder.size(); i++)
    m[inorder[i]] = i;

  return _buildTree(0, preorder.size() - 1, 0, inorder.size() - 1, preorder, inorder, m);
}

Node *Solution::_buildTree(int preS, int preE, int inS, int inE,
                           vector<int> &preorder, vector<int> &inorder,
                           unordered_map<int, int> &map)
{
  if (preS > preE)
    return nullptr;

  /* map back to the inorder */
  auto rootIdx = map[preorder[preS]];

  /* there is 'num' numbers before rootIdx */
  auto num = rootIdx - inS;

  auto root = new Node(preorder[preS]);
  /* break preorder and inorder into two groups
 for left and right child */

  /* for the left child
     - the preorder starts from the next position where the
       root is in the preorder: preS + 1
     - the next "num" numbers should be for the left child
       so the preorder ends in pres + num
     - the start of the inorder is unchanged. It ends at
       rootIdx-1, before the index of the root.
  */

  root->left = _buildTree(preS + 1, preS + num, inS, rootIdx - 1, preorder, inorder, map);
  /* for the right child
     - the preorder starts after you count those that belong to the left child. So it
       starts at preS + num + 1
  */
  root->right = _buildTree(preS + num + 1, preE, rootIdx + 1, inE, preorder, inorder, map);

  return root;
}
