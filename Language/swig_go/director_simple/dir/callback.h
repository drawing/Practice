
#ifndef CALLBACK_H
#define CALLBACK_H

#include <string>

class ICallback
{
public:
	virtual ~ICallback() {}
	virtual void Do(const std::string & data) = 0;
};

class GoThread
{
public:
	void RunLoop();

	void SetCallback(ICallback * cb);
private:
	ICallback * cb_;
};

#endif // CALLBACK_H
