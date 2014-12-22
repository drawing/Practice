
#include <unordered_set>
#include <string>

using namespace std;

struct Shape {
	string name;
};

namespace std
{
	template<>
	struct hash<Shape>
	{
		size_t operator() (Shape const & s) const{
			return std::hash<std::string>()(s.name);
		}
	};
	template<>
	struct equal_to<Shape>
	{
		bool operator() (const Shape & s1, const Shape & s2) {
			return s1.name == s2.name;
		}
	};
}

int main()
{
	unordered_set<Shape> set;

	Shape s;
	s.name = "s1";
	set.insert(s);

	s.name = "s2";
	set.insert(s);

	return 0;
}

