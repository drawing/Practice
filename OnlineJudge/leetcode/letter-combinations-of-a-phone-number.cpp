/**
 * https://oj.leetcode.com/problems/letter-combinations-of-a-phone-number/
 *
 * Given a digit string, return all possible letter combinations that the number could represent.
 *
 * A mapping of digit to letters (just like on the telephone buttons) is given below.
 *
 * Input:Digit string "23"
 * Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
 *
 * Note:
 * Although the above answer is in lexicographical order, your answer could be in any order you want. 
 */

string letters[] = {
	"abc",
	"def",
	"ghi",
	"jkl",
	"mno",
	"pqrs",
	"tuv",
	"wxyz"
};

class Solution {
public:
	void construct(vector<string> & result, string & digits, int di, string & one) {
		while (di < digits.size() && (digits[di] == '0' || digits[di] == '1')) {
			di ++;
		}

		if (digits.size() == di) {
			result.push_back(one);
			return;
		}

		int index = digits[di] - '2';
		const string & let = letters[index];
		for (int j = 0; j < let.size(); j++) {
			one.push_back(let[j]);
			construct(result, digits, di+1, one);
			one.pop_back();
		}
	}

    vector<string> letterCombinations(string digits) {
    	vector<string> result;

    	string one;
    	construct(result, digits, 0, one);
    	return result;
    }
};

