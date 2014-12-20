/**
 * https://oj.leetcode.com/problems/3sum/
 *
 * Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.
 *
 * Note:
 *
 *     Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ≤ b ≤ c)
 *     The solution set must not contain duplicate triplets.
 *
 *     For example, given array S = {-1 0 1 2 -1 -4},
 *
 *     A solution set is:
 *     (-1, 0, 1)
 *     (-1, -1, 2)
 */

class Solution {
public:
    vector<vector<int> > threeSum(vector<int> &num) {
    	vector<vector<int> > result;

    	if (num.size() == 0) {
    		return result;
    	}
    	
    	sort(num.begin(), num.end());

    	vector<int> one(3);

    	int last_one = num[0];
    	set<int> repeat;

    	for (int i = 0; i < num.size(); i++) {
    		if (num[i] > 0) {
    			break;
    		}

    		if (last_one != num[i]) {
    			repeat.clear();
    		}
    		last_one = num[i];

    		int j = i + 1;
    		int k = num.size() - 1;

    		while (j < k && num[k] >= 0) {
				int total = num[i] + num[j] + num[k];
    			if (total < 0) {
    				j ++;
    			} else if (total > 0) {
    				k --;
    			} else {
    				if (repeat.find(num[j]) != repeat.end()) {
    					j ++;
    					k --;
    					continue;
    				}
    				repeat.insert(num[j]);
    				one[0] = num[i];
    				one[1] = num[j];
    				one[2] = num[k];

    				if (result.size() > 0) {
    					const vector<int> & last = result.back();
    					if (last[0] != one[0] ||
    						last[1] != one[1] ||
    						last[2] != one[2])
    					{
	    					result.push_back(one);
	    				}
    				}
    				else {
    					result.push_back(one);
    				}
    				j ++;
    				k --;
    			}
    		}
    	}

    	return result;
    }
};

