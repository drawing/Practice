/**
 * https://oj.leetcode.com/problems/4sum/
 *
 * Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.
 *
 * Note:
 *
 *     Elements in a quadruplet (a,b,c,d) must be in non-descending order. (ie, a ≤ b ≤ c ≤ d)
 *     The solution set must not contain duplicate quadruplets.
 *
 *     For example, given array S = {1 0 -1 0 -2 2}, and target = 0.
 *
 *     A solution set is:
 *     (-1,  0, 0, 1)
 *     (-2, -1, 1, 2)
 *     (-2,  0, 0, 2)
 */

class Solution {
public:
    vector<vector<int> > fourSum(vector<int> &num, int target) {
    	vector<vector<int> > result;

    	if (num.size() < 4) {
    		return result;
    	}
    	
    	sort(num.begin(), num.end());

    	vector<int> one(4);

    	int last_one = num[0];
    	map<int, set<int> > repeat;

    	for (int i = 0; i < num.size(); i++) {
    		for (int j = i+1; j < num.size(); j++) {
    			int m = j + 1;
    			int n = num.size() - 1;

    			if (last_one != num[i]) {
    				repeat.clear();
    			}
    			last_one = num[i];

    			while (m < n) {
					int total = num[i] + num[j] + num[m] + num[n];
					if (total == target) {
						one[0] = num[i];
						one[1] = num[j];
						one[2] = num[m];
						one[3] = num[n];
						m ++;
						n --;

						if (repeat[num[j]].find(one[2]) != repeat[num[j]].end()) {
	    					continue;
	    				}
	    				repeat[num[j]].insert(one[2]);
	    				result.push_back(one);
					}
					else if (total < target) {
						m ++;
					}
					else {
						n --;
					}
				}
    		}
    	}
    	return result;
    }
};
