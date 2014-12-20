/**
 * https://oj.leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
 *
 * Given inorder and postorder traversal of a tree, construct the binary tree.
 *
 * Note:
 * You may assume that duplicates do not exist in the tree. 
 *
 */


/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
	TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder, int i, int j, int size) {
		if (size == 0) {
			return NULL;
		}
		int val = postorder[j+size-1];

		TreeNode * node = new TreeNode(val);

		int offset = 0;
		while (inorder[i+offset] != val) offset ++;

		node->left = buildTree(inorder, postorder, i, j, offset);
		node->right = buildTree(inorder, postorder, i+offset+1, j+offset, size-offset-1);
		return node;
	}
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
    	return buildTree(inorder, postorder, 0, 0, inorder.size());
    }
};
