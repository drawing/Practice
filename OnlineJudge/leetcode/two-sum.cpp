/**
 * https://oj.leetcode.com/problems/two-sum/
 *
 * Given an array of integers, find two numbers such that they add up to a specific target number.
 *
 * The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.
 *
 * You may assume that each input would have exactly one solution.
 *
 * Input: numbers={2, 7, 11, 15}, target=9
 * Output: index1=1, index2=2 
 *
 */

#include <map>
#include <vector>

using namespace std;

class Solution {
public:
	vector<int> twoSum(vector<int> &numbers, int target) {
		vector<int> result;
		map<int, int> elem;
		for (size_t i = 0; i < numbers.size(); i++) {
			int tmp = target - numbers[i];
			if (elem.find(tmp) != elem.end()) {
				if (tmp > numbers[i]) {
					result.push_back(i);
					result.push_back(elem[tmp]);
				}
				else {
					result.push_back(elem[tmp]);
					result.push_back(i);
				}
				break;
			}
			elem[numbers[i]] = i;
		}
		return result;
	}
};
