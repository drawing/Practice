/**
 * https://oj.leetcode.com/problems/longest-substring-without-repeating-characters/
 *
 * Given a string, find the length of the longest substring without repeating characters. For example, the longest substring without repeating letters for "abcabcbb" is "abc", which the length is 3. For "bbbbb" the longest substring is "b", with the length of 1.
 *
 */

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		char flags[255] = {};

		size_t j = 0;
		int maxlen = 0;
		int curlen = 0;
		for (size_t i = 0; i < s.size(); i++) {
			while (flags[(int)s[i]] == 1) {
				flags[(int)s[j]] = 0;
				j++;
				curlen --;
			}

			curlen ++;
			flags[(int)s[i]] = 1;

			if (curlen > maxlen) {
				maxlen = curlen;
			}
		}
		return maxlen;
	}
};

int main() {
	cout << Solution().lengthOfLongestSubstring("abcaefhjka") << endl;
	return 0;
}

