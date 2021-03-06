/**
 * https://oj.leetcode.com/problems/reverse-linked-list-ii/
 *
 *  Reverse a linked list from position m to n. Do it in-place and in one-pass.
 *
 *  For example:
 *  Given 1->2->3->4->5->NULL, m = 2 and n = 4,
 *
 *  return 1->4->3->2->5->NULL.
 *
 *  Note:
 *  Given m, n satisfy the following condition:
 *  1 ≤ m ≤ n ≤ length of list. 
 *
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include <iostream>

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
	ListNode *reverseBetween(ListNode *head, int m, int n) {
		if (head == NULL) {
			return head;
		}

		ListNode ** pp = &head;
		for (int i = 0; i < m-1; i++) {
			pp = &(*pp)->next;
		}

		ListNode * begin = NULL;
		ListNode ** tail = NULL;
		ListNode * org = *pp;
		for (int i = m-1; i < n; i++) {
			if (tail == NULL) {
				tail = &org->next;
			}
			ListNode * temp = org->next;
			org->next = begin;
			begin = org;
			org = temp;
		}
		if (tail) {
			*tail = org;
		}

		if (begin) {
			*pp = begin;
		}
		
		return head;
	}
};

int main()
{
	ListNode * node = new ListNode(3);
	node->next = new ListNode(5);
	ListNode * res = Solution().reverseBetween(node, 1, 2);
	while (res) {
		std::cout << res->val << std::endl;
		res = res->next;
	}
	return 0;
}