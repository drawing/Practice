/**
 * https://oj.leetcode.com/problems/reverse-words-in-a-string/
 *
 *  Given an input string, reverse the string word by word.
 *
 *  For example,
 *  Given s = "the sky is blue",
 *  return "blue is sky the". 
 *
 */

#include <string>
#include <iostream>

using namespace std;


class Solution {
public:
	void reverseWords(string &s) {
		if (s.empty()) {
			return;
		}
		string result;
		int begin = s.size() - 1;
		int end = s.size() - 1;
		bool last_space = true;
		for (int i = s.size() - 1; i >= 0; i--) {
			if (!isspace(s[i])) {
				begin = i-1;
				last_space = false;
			}
			else if (last_space) {
				begin = i-1;
				end = i-1;
			}
			else {
				last_space = true;
				if (!result.empty()) {
					result.push_back(' ');
				}
				for (int j = begin + 1; j <= end; j++) {
					result.push_back(s[j]);
				}
				begin = i-1;
				end = i-1;
			}
		}
		if (!last_space) {
			if (!result.empty()) {
				result.push_back(' ');
			}
			for (int j = begin + 1; j <= end; j++) {
				result.push_back(s[j]);
			}
		}
		s = result;
	}
};

int main()
{
	string s = "abc kkj ";
	Solution().reverseWords(s);
	cout << s << "|" << endl;
	return 0;
}