
#include "callback.h"
#include <unistd.h>

void GoThread::RunLoop() {
	while (true) {
		sleep(1);
		cb_->Do("testok");
	}
}

void GoThread::SetCallback(ICallback * cb)
{
	cb_ = cb;
}

