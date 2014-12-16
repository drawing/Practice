/**
 * https://oj.leetcode.com/problems/lru-cache/
 *
 *  Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and set.
 *
 *  get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
 *  set(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item. 
 *
 */

#include <map>
#include <iostream>

using namespace std;

class LRUCache {

private:
	struct Node {
		int key;
		int val;
		Node * next;
		Node * pre;
	};
public:
	LRUCache(int capacity) {
		_capacity = capacity;
		_head = NULL;
		_tail = NULL;
	}

	int get(int key) {
		if (_data.find(key) == _data.end()) {
			return -1;
		}

		Node * node = _data[key];

		remove(node);
		add(node);
		
		return node->val;
	}

	void set(int key, int value) {

		if (_data.find(key) == _data.end()) {

			Node * node = NULL;
			if (_data.size() >= _capacity) {
				node = last();
				
				_data.erase(node->key);
				remove(node);
			}
			else {
				node = new Node();
			}

			node->key = key;
			node->val = value;
			_data[key] = node;
			add(node);
		} else {
			Node * node = _data[key];
			node->val = value;
			remove(node);
			add(node);
		}
	}

private:
	void remove(Node * node) {
		if (node->next) {
			node->next->pre = node->pre;
		}
		if (node->pre) {
			node->pre->next = node->next;
		}
		if (node == _head) {
			_head = node->next;
		}
		if (node == _tail) {
			_tail = node->pre;
		}
	}

	void add(Node * node) {
		node->pre = NULL;
		node->next = _head;

		if (_head) {
			_head->pre = node;
		}

		_head = node;

		if (_tail == NULL) {
			_tail = node;
		}
	}

	void print() {
		Node * node = _head;
		cout << "Print: ";
		for (; node; node = node->next) {
			cout << node->key << " ";
		}
		cout << endl;
	}

	Node * last() {
		return _tail;
	}

private:
	int _capacity;

	Node * _head;
	Node * _tail;

	map<int, Node *> _data;
};


int main()
{
	LRUCache cache(2);
	cache.set(2, 1);
	cache.set(1, 1);
	cout << cache.get(2) << endl;
	cache.set(4, 1);
	cout << cache.get(1) << endl;
	cout << cache.get(2) << endl;
	return 0;
}