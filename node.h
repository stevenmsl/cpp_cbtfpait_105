#ifndef NODE_H
#define NODE_H

#include <vector>
#include <cinttypes>
using namespace std;

namespace sol105
{
    struct Node
    {
        int val;
        Node *left;
        Node *right;
        Node(int val) : val(val), left(nullptr), right(nullptr){};
    };
}
#endif