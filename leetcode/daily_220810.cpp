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
    /// @detail segment indicate a integer set "[left, right)" 
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        std::queue<std::tuple<TreeNode*, int, int>> parent_and_segment_queue;
        TreeNode* root = new TreeNode(nums[nums.size() / 2]);
        parent_and_segment_queue.push(std::make_tuple(root, 0, nums.size() / 2));
        parent_and_segment_queue.push(std::make_tuple(root, nums.size() / 2 + 1, nums.size()));
        
        while(!parent_and_segment_queue.empty()) {
            auto parent_and_segment = parent_and_segment_queue.front();
            parent_and_segment_queue.pop();
            int left = std::get<1>(parent_and_segment);
            int right = std::get<2>(parent_and_segment);
            if (left >= right) {
                continue;
            }
            int mid = (left + right) / 2;
            TreeNode* parent = std::get<0>(parent_and_segment);
            TreeNode* current_node = new TreeNode(nums[mid]);
            if (parent->val > current_node->val) {
                parent->left = current_node;
            } else {
                parent->right = current_node;
            }
            parent_and_segment_queue.push(std::make_tuple(current_node, left, mid));
            parent_and_segment_queue.push(std::make_tuple(current_node, mid + 1, right));
        }
        return root;
    }
};
