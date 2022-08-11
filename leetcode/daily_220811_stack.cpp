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
    enum VisitCount {
        kFirstVisit = 0,
        kSecondVisit = 1
    };
    
    bool isValidBST(TreeNode* root) {
        std::stack<std::pair<TreeNode*, VisitCount>> stack;
        stack.push(std::make_pair(root, kFirstVisit));
        
        bool did_succeed = true;
        bool did_get_first_val = false;
        int last_val;
        while(!stack.empty()) {
            std::pair<TreeNode*, VisitCount> current_state = stack.top();
            stack.pop();
            TreeNode* node = current_state.first;
            VisitCount visit_count = current_state.second;
            
            if (visit_count == kFirstVisit) {
                if (node->right != nullptr) {
                    stack.push(std::make_pair(node->right, kFirstVisit));
                }
                stack.push(std::make_pair(node, kSecondVisit));
                if (node->left != nullptr) {
                    stack.push(std::make_pair(node->left, kFirstVisit));
                }
            } else {
                if (!did_get_first_val) {
                    did_get_first_val = true;
                } else if (node->val <= last_val) {
                    did_succeed = false;
                    break;
                }
                last_val = node->val;
            }
        }
        return did_succeed;
    }
};
