
/**
 * Hash Implement
 *
 * std::unordered_set
 * std::unordered_map
 * std::unordered_multiset
 * std::unordered_multimap
 *
 * template<
 * 	class Key,
 * 	class Hash = std::hash<Key>,
 * 	class KeyEqual = std::equal_to<Key>,
 * 	class Allocator = std::allocator<Key>
 * > class unordered_set;
 */

#include <unordered_set>

using namespace std;

int main()
{
	unordered_set<int> set;
	set.insert(1);
	set.insert(2);
	set.insert(3);

	return 0;
}

