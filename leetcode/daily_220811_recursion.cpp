/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool did_first_check = false;
    int last_val;
    
    bool isValidBST(TreeNode* root) {
        bool result = true;
        if (root->left != nullptr) {
            result = result && isValidBST(root->left);
        }
        if (!did_first_check) {
            did_first_check = true;
        } else if (root->val <= last_val) {
            return false;
        }
        last_val = root->val;
        if (root->right != nullptr) {
            result = result && isValidBST(root->right);
        }
        return result;
    }
};
