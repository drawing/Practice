/**
 * https://oj.leetcode.com/problems/rotate-image/
 *
 * You are given an n x n 2D matrix representing an image.
 *
 * Rotate the image by 90 degrees (clockwise).
 *
 * Follow up:
 * Could you do this in-place?
 */

#include <vector>

using namespace std;

class Solution {
public:
	void rotate(vector<vector<int> > &matrix) {
		int size = matrix.size();
		int row = size / 2;
		int col = row + size % 2;
		size --;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				int temp = matrix[i][j];
				matrix[i][j] = matrix[size-j][i];
				matrix[size-j][i] = matrix[size-i][size-j];
				matrix[size-i][size-j] = matrix[j][size-i];
				matrix[j][size-i] = temp;
			}
		}
	}
};


