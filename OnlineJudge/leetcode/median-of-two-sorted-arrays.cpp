/**
 * https://oj.leetcode.com/problems/median-of-two-sorted-arrays/
 *
 * There are two sorted arrays A and B of size m and n respectively. Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
 */

 #include <iostream>

 using namespace std;

class Solution {
public:
	double findMedianSortedArrays(int A[], int m, int B[], int n) {
		int s1 = 0;
		int s2 = 0;

		int last_min = 0;
		int last_max = 0;

		while (1) {
			int start = 0;
			int end = 0;
			if (m > s1 && n > s2) {
				last_min = A[s1];
				last_max = A[m-1];

				if (A[s1] > B[s2]) {
					start = 1;
					last_min = B[s2];
				}
				if (A[m-1] < B[n-1]) {
					end = 1;
					last_max = B[n-1];
				}
			}
			else if (m <= s1 && n <= s2) {
				return (last_min + last_max) / 2.0;
			}
			else if (m <= s1) {
				if (n - s2 == 1) {
					return B[s2];
				}
				start = 1;
				end = 1;
				last_min = B[s2];
				last_max = B[n-1];
			}
			else {
				if (m - s1 == 1) {
					return A[s1];
				}
				last_min = A[s1];
				last_max = A[m-1];
			}

			if (start == 0) {
				s1 ++;
			}
			else {
				s2 ++;
			}

			if (end == 0) {
				m --;
			}
			else {
				n --;
			}
		}
		return 0;
	}
};

int main()
{
	int A[] = {};
	int B[] = {1};
	cout << Solution().findMedianSortedArrays(A, 0, B, 1) << endl;
}