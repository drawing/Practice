/**
 * https://oj.leetcode.com/problems/merge-k-sorted-lists/
 *
 *  Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity. 
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

#include <vector>
#include <map>
#include <string.h>

struct ListNode {
int val;
     ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
  };

using namespace std;


class Solution {
public:
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        ListNode * head = NULL;
        ListNode * tail = NULL;

        multimap<int, int> heap;
        for (int i = 0; i < lists.size(); i++) {
        	if (lists[i]) {
    			heap.insert(pair<int, int>(lists[i]->val, i));
    		}
        }

        while (!heap.empty()) {
        	multimap<int, int>::iterator i = heap.begin();
        	int index = i->second;
    		if (tail == NULL) {
    			head = lists[index];
    			tail = head;
    		}
    		else {
    			tail->next = lists[index];
    			tail = tail->next;
    		}
    		
    		lists[index] = tail->next;
    		heap.erase(i);
    		if (lists[index]) {
    			heap.insert(pair<int, int>(lists[index]->val, index));
    		}

    		tail->next = NULL;
    	}

        return head;
    }
};

