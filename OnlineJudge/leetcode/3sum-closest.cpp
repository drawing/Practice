/**
 * https://oj.leetcode.com/problems/3sum-closest/
 *
 * Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target.
 * Return the sum of the three integers. You may assume that each input would have exactly one solution.
 *
 *     For example, given array S = {-1 2 1 -4}, and target = 1.
 *
 *     The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
 */

class Solution {
public:
    int threeSumClosest(vector<int> &num, int target) {
    	sort(num.begin(), num.end());

    	int min_gap = -1;
    	int closest = 0;

    	for (int i = 0; i < num.size(); i++) {
    		int j = i + 1;
    		int k = num.size() - 1;

    		while (j < k) {
				int total = num[i] + num[j] + num[k];
				int gap = abs(total - target);
				if (min_gap == -1 || gap < min_gap) {
					min_gap = gap;
					closest = total;
				}

				if (total == target) {
					return target;
				}
    			else if (total < target) {
    				j ++;
    			} else {
    				k --;
    			}
    		}
    	}

    	return closest;
    }
};
