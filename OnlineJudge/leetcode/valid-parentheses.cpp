/**
 * https://oj.leetcode.com/problems/valid-parentheses/
 *
 * Given a string containing just the characters '(', ')', '{', '}', '[' and ']'
 * determine if the input string is valid.
 *
 * The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.
 *
 */

class Solution {
public:
    bool isValid(string s) {
    	stack<char> q;
    	for (int i = 0; i < s.size(); i++) {
    		if (s[i] == '(') {
    			q.push(')');
    		} else if (s[i] == '[') {
    			q.push(']');
    		} else if (s[i] == '{') {
    			q.push('}');
    		} else {
    			if (q.empty() || q.top() != s[i]) {
    				return false;
    			}
    			q.pop();
    		}
    	}
    	return q.empty();
    }
};
