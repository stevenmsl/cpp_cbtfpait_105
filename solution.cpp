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
  - example preorder=[3,9,20,15,7] inorder=[9,3,15,20,7]
    - so the basic idea is locating the root in the
      preorder array first and then go back to the
      inorder array to find its left child
    - for example from preorder, we know 3 is the root.
    - you then look at inorder and know [9] is its left
      child, which only has one number:
      (indx of 3) - 0 = 1 - 0 = 1
    - we now go back to preorder and know that the next
      one number will be its left child as well
    - the rest should be all for the right child
    - pre [3,9,20,15,7] -> [9] & [20,15,7]
    - in [9,3,15,20,7] -> [9] & [15,20,7]
    - so we can continue building left child with [9] and [9]
      and right child with [20,15,7] and [15,20,7]

  - Time complexity: O(n)

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

  /* there is 'num' numbers before rootIdx
     - inorder[inS...rootIdx-1]
     - rootIdx-1 - inS + 1 = rootIdx - ins
  */
  auto num = rootIdx - inS;

  auto root = new Node(preorder[preS]);
  /* break preorder and inorder into two groups
 for left and right child */

  /* for the left child
     - in the preorder, the nodes in this range preorder[preS+1...preS+num]
       is in the root's left child
     - the start of the inorder is unchanged. It ends at
       rootIdx-1, before the index of the root.
     - you count num toward the right in preorder and num toward the left
       in the inorder
  */

  root->left = _buildTree(preS + 1, preS + num, inS, rootIdx - 1, preorder, inorder, map);
  /* for the right child
     - the preorder starts after you count those that belong to the left child. So it
       starts at preS + num + 1
  */
  root->right = _buildTree(preS + num + 1, preE, rootIdx + 1, inE, preorder, inorder, map);

  return root;
}
