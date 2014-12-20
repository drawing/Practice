/**
 * https://oj.leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
 *
 * Given preorder and inorder traversal of a tree, construct the binary tree.
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
	TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder, int i, int j, int size) {
		if (size == 0) {
			return NULL;
		}

		int val = preorder[i];
		TreeNode * node = new TreeNode(val);

		int offset = 0;
		while (inorder[j + offset] != val) {
			offset ++;
		}

		node->left = buildTree(preorder, inorder, i+1, j, offset);
		node->right = buildTree(preorder, inorder, i+offset+1, j+1+offset, size-offset-1);
		return node;
	}

    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        return buildTree(preorder, inorder, 0, 0, preorder.size());
    }
};
