/**
 * http://en.cppreference.com/w/cpp/thread
 * http://www.cnblogs.com/haippy/p/3284540.html
 */

#include <thread>
#include <iostream>

using namespace std;

void thread_task() {
	cout << "one task begin." << endl;
	std::chrono::milliseconds dura(3000);
	std::this_thread::sleep_for(dura);
	cout << "one task end." << endl;
}

int main() {
	std::thread t(thread_task);
	t.join();
	return 0;
}

