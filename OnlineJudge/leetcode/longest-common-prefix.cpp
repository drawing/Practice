/**
 * https://oj.leetcode.com/problems/longest-common-prefix/
 *
 * Write a function to find the longest common prefix string amongst an array of strings. 
 *
 */

class Solution {
public:
    string longestCommonPrefix(vector<string> &strs) {
    	if (strs.size() == 0) {
    		return "";
    	}
    	const string & rule = strs[0];
    	int i = 0;
    	bool finish = false;
    	for (i = 0; i < rule.size(); i++) {
    		for (int j = 1; j < strs.size(); j++) {
    			if (strs[j].size() <= i || strs[j][i] != rule[i]) {
    				finish = true;
    				break;
    			}
    		}
    		if (finish) {
    			break;
    		}
    	}
    	return rule.substr(0, i);
    }
};

