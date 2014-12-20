/**
 * https://oj.leetcode.com/problems/generate-parentheses/
 *
 *  Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
 *
 *  For example, given n = 3, a solution set is:
 *
 *  "((()))", "(()())", "(())()", "()(())", "()()()" 
 */

class Solution {
public:
	void generate(vector<string> & result, string & one, int left, int right, int limit) {
		if (left == limit && right == limit) {
			result.push_back(one);
		}
		if (left < limit) {
			one.push_back('(');
			generate(result, one, left+1, right, limit);
			one.pop_back();
		}
		if (right < left) {
			one.push_back(')');
			generate(result, one, left, right+1, limit);
			one.pop_back();
		}
	}
    vector<string> generateParenthesis(int n) {
    	vector<string> result;
    	string one;
    	generate(result, one, 0, 0, n);
    	return result;
    }
};

