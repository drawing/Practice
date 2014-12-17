/**
 * https://oj.leetcode.com/problems/reverse-integer/
 *
 * Reverse digits of an integer.
 *
 * Example1: x = 123, return 321
 * Example2: x = -123, return -321 
 *
 */

#include <iostream>
using namespace std;

class Solution {
public:
	int reverse(int x) {
		if (x < 0 && -x < 0) {
			return 0;
		}
		if (x < 0) {
			return -reverse(-x);
		}

		unsigned long long result = 0;
		while (x > 0) {
			int p1 = x % 10;
			x /= 10;
			result *= 10;
			result += p1;
		}

		if (result > 0x7FFFFFFF) {
			return 0;
		}

		return result;
	}
};

int main()
{
	cout << Solution().reverse(1234567899) << endl;
	return 0;
}
