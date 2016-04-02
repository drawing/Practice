
#include <vector>

int PrintList(const std::vector<int> & list) {
	for (std::vector<int>::const_iterator it = list.begin(); it != list.end(); it++) {
		printf("-- %d\n", *it);
	}
}
