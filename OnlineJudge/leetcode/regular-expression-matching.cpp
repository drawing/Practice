/**
 * https://oj.leetcode.com/problems/regular-expression-matching/
 *
 * Implement regular expression matching with support for '.' and '*'.
 *
 * '.' Matches any single character.
 * '*' Matches zero or more of the preceding element.
 *
 * The matching should cover the entire input string (not partial).
 *
 * The function prototype should be:
 * bool isMatch(const char *s, const char *p)
 *
 * Some examples:
 * isMatch("aa","a") → false
 * isMatch("aa","aa") → true
 * isMatch("aaa","aa") → false
 * isMatch("aa", "a*") → true
 * isMatch("aa", ".*") → true
 * isMatch("ab", ".*") → true
 * isMatch("aab", "c*a*b") → true
 *
 */

#include <iostream>

using namespace std;


class Solution {
public:
	bool isMatch(char s, char p) {
		if ((s == p) || (s != 0 && p == '.')) {
			return true;
		}
		return false;
	}
	bool isMatch(const char *s, const char *p) {
		if (*s == 0 && *p == 0) {
			return true;
		} else if (*p == 0) {
			return false;
		} else if (*s == 0 && p[1] != '*') {
			return false;
		}
		
		if (*p != 0 && *(p+1) == '*') {
			bool match = isMatch(s, p+2);
			if (match) {
				return true;
			}
			for (int i = 1; isMatch(s[i-1], *p); i++) {
				bool match = isMatch(s+i, p+2);
				if (match) {
					return true;
				}
			}
			return false;
		}
		else {
			if (*s == 0) {
				return false;
			}
			if (!isMatch(*s, *p)) {
				return false;
			}
			return isMatch(s+1, p+1);
		}
	}
};

int main()
{
	cout << Solution().isMatch("acaabbaccbbacaabbbb", "a*.*b*.*a*aa*a*") << endl;
}
